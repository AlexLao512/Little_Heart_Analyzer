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
 * @file Heartrate.h
 */

#ifndef HEARTRATE_H
#define HEARTRATE_H

#include <QObject>
#include <QVector>
#include <QtCore>

class Heartrate: public QObject
{
    Q_OBJECT

private:
    typedef enum {
        FIND_RISING,
        FIND_FALLING
    } edge_detector_state_T;

    edge_detector_state_T edge_detector_state = FIND_RISING;

    double low_threshold = 7300;
    double high_threshold = 8700;

    int since_last_fall;
public:
    Heartrate();
public slots:
    void process(QVector<double> input);
signals:
    void processingComplete();
    void newHeartrate(double heartrate);
};

#endif // HEARTRATE_H
