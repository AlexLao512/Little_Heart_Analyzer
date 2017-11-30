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
 *          will be relayed to the original four team memebers. 
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
 * @file ECG_DSP.cpp
 */

#include "ECG_DSP.h"

/*!
 * @brief ECG_DSP Constructor
 *
 */
ECG_DSP::ECG_DSP(QObject *parent) : QObject(parent)
{
    QTextStream(stdout) << "ECG_DSP Constructor" << endl;
    QObject::connect(&ecg, &ECG_Data_Provider::outgoingData, this, &ECG_DSP::incomingData);

    //worker.moveToThread( &worker_thread );
    //QObject::connect( this, &ECG_DSP::processDummy, &worker, &Dummy_Algorithm::process );
    //QObject::connect( &worker, &Dummy_Algorithm::processingComplete, this, &ECG_DSP::doneDummy );
    //worker_thread.start();


    hrProcessor.moveToThread( &worker_thread );
    QObject::connect( this, &ECG_DSP::processHeartrate, &hrProcessor, &Heartrate::process );
    QObject::connect( &hrProcessor, &Heartrate::processingComplete, this, &ECG_DSP::doneHeartrate );
    QObject::connect( &hrProcessor, &Heartrate::newHeartrate, this, &ECG_DSP::newHeartrate );
    worker_thread.start();

    return;
}

/*!
 * @brief Updates a line series with new channel data
 *
 * Called by QML.
 * Updates the line series when given the pointer to the series and channel number to grab data from.
 *
 * @param series Pointer to the line series to be modified
 * @param leadNumber The line series ID
 */
void ECG_DSP::update(QAbstractSeries *series, int lead_number)
{
    //QTextStream(stdout) << "Plot Start " << timer.elapsed() << endl;
    static int count[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    static int updateIndex[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

    if (series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);

        if(count[lead_number] < 2048) { // Create initial set of points
            for(int i = 0; i < 2048; i++) {
                xySeries->append(count[lead_number], 0);
                count[lead_number]++;
            }
        }

        //QTextStream(stdout) << " Plotting: " << ecg_data[lead_number].size() << endl;
        for (int i = ecg_data[lead_number].size(); i > 0 ; i--) {
            if(count[lead_number] < 2048) { // Create initial set of points
                xySeries->append(count[lead_number], ecg_data[lead_number].at(0));
                count[lead_number]++;
            } else { // Overwrite old points from left to right
                //xySeries->replace(updateIndex[lead_number], updateIndex[lead_number], notchFilter[lead_number].update((double) ecg_data[lead_number].at(0)));
                xySeries->replace(updateIndex[lead_number], updateIndex[lead_number], ecg_data[lead_number].at(0));
                updateIndex[lead_number]++;
                if (updateIndex[lead_number] == 2048) {
                    updateIndex[lead_number] = 0;
                }
            }
            ecg_data[lead_number].pop_front(); //Remove 1 Data Point
        }
    }
    //QTextStream(stdout) << "Plot End " << timer.elapsed() << endl;
}

/*!
 * @brief Read data from data provider and performs DSP opperations on the data
 *
 * Extracts data from ecg_raw_data and places it into ecg_data after initial processing
 *
 * @param ecg_raw_data[8] Data input
 */
void ECG_DSP::incomingData(QVector <short int> ecg_raw_data[8])
{
    leads_T lead = V1;
    int size = 0;
    double tempFilteredLead1, tempFilteredLead2;

    //Preprocess incoming raw data, initial filtering and lead derivation
    for(int i = 0; i<7; i++) { //Loop through raw data except LEAD1 since that is handled in the LEAD2 case already due to lead derivation only
        lead = (leads_T) i;
        size = ecg_raw_data[lead].size();
        for(int j = 0; j<size; j++) {
            switch (lead) {
                case V1:
                case V2:
                case V3:
                case V4:
                case V5:
                case V6:
                    //QTextStream(stdout) << "ECG_V" << endl;
                    ecg_data[lead].append(notch_filter[lead].update((double) ecg_raw_data[lead].at(0)));
                    break;

                case LEAD1:
                case LEAD2:
                    //QTextStream(stdout) << "ECG_LEAD" << endl;
                    tempFilteredLead1 = notch_filter[LEAD1].update((double) ecg_raw_data[LEAD1].at(0));
                    tempFilteredLead2 = notch_filter[LEAD2].update((double) ecg_raw_data[LEAD2].at(0));
                    ecg_data[LEAD1].append(tempFilteredLead1);
                    ecg_data[LEAD2].append(tempFilteredLead2);

                    //derive leads
                    ecg_data[LEAD3].append(derive_lead_3.derive(tempFilteredLead2, tempFilteredLead1));
                    ecg_data[aVR].append(derive_aVR.derive(tempFilteredLead1, tempFilteredLead2));
                    ecg_data[aVL].append(derive_aVL.derive(tempFilteredLead1, tempFilteredLead2));
                    ecg_data[aVF].append(derive_aVF.derive(tempFilteredLead2, tempFilteredLead1));

                    //Dummy Algorithm Data
                    //dummy_lead1[dummy_algorithm_current_buffer].append(tempFilteredLead1);
                    heartrate_lead[heartrate_current_buffer].append(tempFilteredLead2);

                    ecg_raw_data[LEAD1].pop_front();
                    break;

                default:
                    break;
            }
            ecg_raw_data[lead].pop_front();
        }

        //Diagnostic algorithms, launch threads
        //if(dummy_complete == true) {
            //emit processDummy(dummy_lead1[dummy_algorithm_current_buffer]);
            //dummy_algorithm_current_buffer = !dummy_algorithm_current_buffer;
            //dummy_complete = false;
        //}
        if(heartrate_complete == true && heartrate_lead[heartrate_current_buffer].size() != 0) {
            emit processHeartrate(heartrate_lead[heartrate_current_buffer]);
            heartrate_current_buffer = !heartrate_current_buffer;
            heartrate_complete = false;
        }
    }
    return;
}

void ECG_DSP::doneDummy(unsigned int returnValue)
{
    //QTextStream(stdout) << "doneDummy returned " << returnValue << endl;
    //QTextStream(stdout) << "doneDummy size " << dummy_lead1[0].size() << endl;
    dummy_lead1[!dummy_algorithm_current_buffer].clear();

    dummy_complete = true;
}

/*
* @brief Take new heartrate value
*
* @param heartrate New heartrate value (Beats Per Minute)
*/
void ECG_DSP::newHeartrate(double heartrate)
{
    QTextStream(stdout) << "Heartrate returned " << heartrate << endl;
    localHeartRate = heartrate;
}

/*
* @brief Switch buffer being written to by ECG_DSP
*/
void ECG_DSP::doneHeartrate()
{
    heartrate_lead[!heartrate_current_buffer].clear();
    heartrate_complete = true;
}

int ECG_DSP::qmlHeartRate()
{
    if(localHeartRate <= 300 && localHeartRate > 20) {
        return(localHeartRate);
    }
    return(0);
}
