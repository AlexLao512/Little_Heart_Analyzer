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
 * @file ECG_Data_Provider.h
 */

#ifndef ECG_DATA_PROVIDER_H
#define ECG_DATA_PROVIDER_H

#include <QObject>

#include <QtCore>

#include <QTextStream>
#include <QtSerialPort/QSerialPort>

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>

#include <QElapsedTimer>

#include <DF2_Filter.h>
#include <Derive_Lead.h>
//#include <ECG_DSP.h>
#define COMMAND_BYTE_CODE 'c'
#define LEASE_RENEWAL_TOKEN COMMAND_BYTE_CODE
#define DC_OFFSET_BYTE_CODE 'd'

#include <QFile>

QT_CHARTS_USE_NAMESPACE

class ECG_Data_Provider : public QObject
{
    Q_OBJECT

    private:
        QFile file;
        QTextStream fileStream;

        /*!
         * @enum serialState_T
         *
         * @brief States the serial incomingData() slot can be in
         */
        typedef enum {
            //! Finding 0xFF
            SYNC1,
            //! Finding 0xFF
            SYNC2,
            //! Finding 0xDA or 0xCD
            HEADER,
            //! Handle incoming DATA
            DATA,
            //! Handle incoming CMD
            CMD
        } serialState_T;

        //! Stores the state of the serial port
        serialState_T serialState = SYNC1;
        //! Windows COMxy Port or Linux /dev/ttyACMx
        QSerialPort *serialPort = new QSerialPort;

        //! Storage for ECG data, filled by incomingData(), emptied by update()
        QVector <short int> ecg_raw_data[8];

        QElapsedTimer timer;
        QTimer * leaseTimer;
    private slots:
        void incomingData();
        void renewLease();

    public:
        explicit ECG_Data_Provider(QObject *parent = 0);
        //ECG_DSP ecgDSP;
        void setDCControl( int channel, int enable);
    signals:
        void outgoingData(QVector <short int> ecg_raw_data[8]);
};

#endif // ECG_DATA_PROVIDER_H
