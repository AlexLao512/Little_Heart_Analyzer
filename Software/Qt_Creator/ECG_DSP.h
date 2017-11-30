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
 * @file ECG_DSP.h
 */

#ifndef ECG_DSP_H
#define ECG_DSP_H

#include <QThread>
#include <QObject>
#include <QtCore>
#include <QVector>
#include <QTextStream>

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>

#include <ECG_Data_Provider.h>
#include <Derive_Lead.h>
#include <DF2_Filter.h>
#include <Dummy_Algorithm.h>
#include <Heartrate.h>

#include <Global.h>

QT_CHARTS_USE_NAMESPACE

class ECG_DSP : public QObject
{
    Q_OBJECT

    private:
        ECG_Data_Provider ecg;

        QVector <double> ecg_data[12];

        //! 60Hz notch filters for each channel used by update()
        DF2_Filter notch_filter[8];

        Derive_Lead derive_lead_3      = Derive_Lead((double)1  ,(double)1  ,(bool)1,(bool)0); //   Lead_II - Lead_I
        Derive_Lead derive_aVR         = Derive_Lead((double)0.5,(double)0.5,(bool)1,(bool)1); // -(Lead_I  - (Lead_II)/2))
        Derive_Lead derive_aVL         = Derive_Lead((double)1  ,(double)0.5,(bool)1,(bool)0); //  (Lead_I  - (Lead_II/2))
        Derive_Lead derive_aVF         = Derive_Lead((double)1  ,(double)0.5,(bool)1,(bool)0); //  (Lead_II - (Lead_I /2))

        //Dummy_Algorithm Ping Pong Buffers
        int dummy_algorithm_current_buffer = 0;
        QVector <double> dummy_lead1[2];

        QThread worker_thread;
        Dummy_Algorithm worker;
        bool dummy_complete = true;

        Heartrate hrProcessor;
        QVector <double> heartrate_lead[2];
        int heartrate_current_buffer = 0;
        bool heartrate_complete = true;
        int localHeartRate;
    public:
        explicit ECG_DSP(QObject *parent = 0);
        Q_INVOKABLE void update(QAbstractSeries* series, int lead_number);
        Q_INVOKABLE int qmlHeartRate();
    signals:
        void processDummy(QVector <double> lead1);
        void processHeartrate(QVector <double> input);

    public slots:
        void incomingData(QVector <short int> ecg_raw_data[8]);
        void doneDummy(unsigned int returnValue);
        void doneHeartrate();
        void newHeartrate(double heartrate);
};

#endif // ECG_DSP_H
