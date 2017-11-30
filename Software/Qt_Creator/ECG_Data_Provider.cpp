/*  
 *  Little Heart Analyzer
 *  Copyright (C) 2017 Alex Lao, Christina Riczu, Thomas Phan, Emilie Corcoran
 *  
 *  Original project documentation at www.voltagedivide.com
 *  Original code repository at www.github.com/AlexLao512/Little_Heart_Analyzer
 *
 *  Notice: If you find this code useful please consider donating to,  
 *          or thanking the team that originally developed this project. 
 *          Do so by contacting lao.alex.512@gmail.com, donations or comments
 *          will be relayed to the original four team members. 
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
/*!
 * @file ECG_Data_Provider.cpp
 */

#include "ECG_Data_Provider.h"

/*!
 * @brief ECG_Data_Provider Constructor
 *
 * Creates the serial port object used to communicate with the hardware.
 * Connects the serial port object's readyRead signal to the ecg_raw_data_Provider readData slot.
 */
ECG_Data_Provider::ECG_Data_Provider(QObject *parent) : QObject(parent)
{
    QTextStream(stdout) << "ECG_Data_Provider Constructor" << endl;

    serialPort->setPortName("COM4");
    serialPort->setBaudRate(115200); //Ignored by USB UART and BT UARTs
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->open(QIODevice::ReadWrite);


    QObject::connect(serialPort, SIGNAL(readyRead()), this, SLOT(incomingData()));
    //QObject::connect(this, &ECG_Data_Provider::outgoingData, &ecgDSP, &ECG_DSP::incomingData);

    for(int i = 0; i<8; i++){
        ecg_raw_data[i].resize(1);
    }
    serialPort->clear(QSerialPort::AllDirections);
    timer.start();
    leaseTimer = new QTimer(this);
    connect(leaseTimer, SIGNAL(timeout()), this, SLOT(renewLease()));
    leaseTimer->start(100);
    //call renew lease so start the inital lease of the ECG board connection
    renewLease();

    //file.setFileName("Data.csv");
    //file.open(QIODevice::ReadWrite);

    //fileStream.setDevice(&file);
    //fileStream << "V1,V6,V5,V4,V3,V2,RA-LL,RA-LA," << endl;
}

/*!
 * @brief Read data available from serial port
 *
 * Reads one byte at a time when trying to find the sync word then switches to reading entire data packets and consumes the next header without looking at it.
 */
void ECG_Data_Provider::incomingData()
{
    //QTextStream(stdout) << "readData START" << endl;
    char serialData[515];

    //QTextStream(stdout) << " Buffer contains: " << serialPort->bytesAvailable() << endl;

    if(serialState != DATA) {
        serialPort->read(serialData, 1);
    } else {
        if(serialPort->bytesAvailable() < 515){
            return;
        }
        serialPort->read(serialData, 515); //Consume data and next header
    }

    //QTextStream(stdout) << (char) serialData[0] << endl;
    //QTextStream(stdout) << " Buffer contains: " << serialPort->bytesAvailable() << endl;

    int channel = 0;

    int processEventsCountdown = 100;

    switch (serialState) {
        case SYNC1:
            if (serialData[0] == (char) 0xFF){
                QTextStream(stdout) << "SYNC1" << endl;
                serialState = SYNC2;
            }
            break;

        case SYNC2:
            if (serialData[0] == (char) 0xFF){
                QTextStream(stdout) << "SYNC2" << endl;
                serialState = HEADER;
            } else {
                serialState = SYNC1;
            }
            break;

        case HEADER:
            if (serialData[0] == (char) 0xDA){
                QTextStream(stdout) << "HEADER" << endl;
                serialState = DATA;
            } else if (serialData[0] == (char) 0xC0){
                QTextStream(stdout) << "HEADER" << endl;
                serialState = CMD;
            } else {
                //TODO throw error
                serialState = SYNC1;
            }
            break;

        case DATA:
            if(serialData[512] != (char) 0xFF || serialData[513] != (char) 0xFF ||serialData[514] != (char) 0xDA)
            {
                QTextStream(stdout) << "ERROR: Sync Issue" << endl;
                serialState = SYNC1;
                //serialPort->clear(QSerialPort::AllDirections);

                while(serialPort->bytesAvailable() > 0 && serialState != DATA && serialState != CMD) {
                    renewLease();
                    /*processEventsCountdown -= 1;
                    if(processEventsCountdown == 0) {
                        //QCoreApplication::processEvents();
                        processEventsCountdown = 100;
                    }*/
                    if(serialPort->read(serialData, 1) != -1) {
                        switch (serialState) {
                            case SYNC1:
                                if (serialData[0] == (char) 0xFF){
                                    QTextStream(stdout) << "SYNC1" << endl;
                                    serialState = SYNC2;
                                }
                                break;

                            case SYNC2:
                                if (serialData[0] == (char) 0xFF){
                                    QTextStream(stdout) << "SYNC2" << endl;
                                    serialState = HEADER;
                                } else {
                                    serialState = SYNC1;
                                }
                                break;

                            case HEADER:
                                if (serialData[0] == (char) 0xDA){
                                    QTextStream(stdout) << "HEADER" << endl;
                                    serialState = DATA;
                                } else if (serialData[0] == (char) 0xC0){
                                    QTextStream(stdout) << "HEADER" << endl;
                                    serialState = CMD;
                                } else {
                                    //TODO throw error
                                    serialState = SYNC1;
                                }
                                break;
                        }
                    } else {
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i <512; i=i+2){
                    ecg_raw_data[channel%8].append(((short int) (serialData[i] & 0xFF) << 8) | (short int) (serialData[i+1] & 0xFF)); //Add 1 Data Point

                    //fileStream << (((short int) (serialData[i] & 0xFF) << 8) | (short int) (serialData[i+1] & 0xFF)) << ",";

                    if(channel%8 == 7) {
                        //fileStream << endl;
                    }

                    channel = channel + 1;
                }
                renewLease();
                //QCoreApplication::processEvents();
                emit outgoingData(ecg_raw_data); //Pass ecgDSP the pointer to the ecg_raw_data array of QVectors
                serialState = DATA;
            }
            break;

        case CMD:
            //TODO write code to handle command line instructions
            serialState = SYNC1;
            break;

        default:
            //TODO throw error
            serialState = SYNC1;
            break;
        }
    //QTextStream(stdout) << "readData END" << endl << endl;
}

void ECG_Data_Provider::renewLease()
{
    char send[2];
    send[0] = LEASE_RENEWAL_TOKEN;
    serialPort->write(send,1);
}
void ECG_Data_Provider::setDCControl(int channel, int enable)
{
    char send[5];
    send[0] = 'c';//command byte
    send[1] = 'd';
    send[2] = channel;
    send[3] = enable;
    serialPort->write(send,4);
}
