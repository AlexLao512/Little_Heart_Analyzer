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
 * @file Heartrate.cpp
 */
#include "Heartrate.h"

/*!
 * @brief Heartrate Constructor
 *
 * @param new_low_threshold Falling Edge Threshold
 * @param new_high_threshold Rising Edge Threshold
 */

//Heartrate::Heartrate(double new_low_threshold, double new_high_threshold)
Heartrate::Heartrate()

{

//    low_threshold = new_low_threshold;
//    high_threshold = new_high_threshold;
    since_last_fall = 0;
}

/*!
 * @brief Takes input data and returns the heartrate
 *
 * @param input Input Lead
 */
void Heartrate::process(QVector<double> input)
{
    for(int i=0; i<input.size(); i++){
        switch(edge_detector_state)
        {
            case(FIND_RISING):
                if(input.at(i) > high_threshold) {
                    edge_detector_state = FIND_FALLING;
                }
                break;
            case(FIND_FALLING):
                if(input.at(i) < low_threshold) {
                    emit newHeartrate((1000/((double)since_last_fall))*60 );
                    QTextStream(stdout) << since_last_fall << endl;
                    since_last_fall = 0;
                    edge_detector_state = FIND_RISING;
                }
                break;
        }
        since_last_fall = since_last_fall + 1;
    }
    emit processingComplete();
}


