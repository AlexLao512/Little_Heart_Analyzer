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
 * @file main.cpp
 */

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtCharts>

#include <QtCore>

#include <time.h>
#include <stdlib.h>

#include <ECG_DSP.h>
#include <ECG_Data_Provider.h>

using namespace QtCharts;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<ECG_Data_Provider>("ECG_Data_Provider", 1, 0, "ECG_Data_Provider");
    qmlRegisterType<ECG_DSP>("ECG_DSP", 1, 0, "ECG_DSP");

    qRegisterMetaType<QVector<double>>("QVector<double>");

    qRegisterMetaType<QVector<short int>>("QVector<short int>");

    //ECG_Data_Provider ecg;

    //QObject::connect(&ecg, SIGNAL(updatePlot(QAbstractSeries *series, int leadNumber)),
    //                 &ecg.ecgDSP, SIGNAL(update(QAbstractSeries series, int leadNumber)));

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
