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
 * @file Dummy_Algorithm.cpp
 */

#include <Dummy_Algorithm.h>

/*!
 * @brief Dummy_Algorithm Constructor
 *
 */
Dummy_Algorithm::Dummy_Algorithm()
{
    return;
}

/*!
 * @brief
 *
 *
 */
void Dummy_Algorithm::process(QVector <double> lead1)
{
    unsigned int sum = 0;
    int size = lead1.size();

    //Do a bunch of fake work
    for(int j = 0; j < 10000; j++) {
        for(int i = 0; i<size; i++) {
            sum = sum + lead1.at(i);
        }
    }

    emit processingComplete(sum);
}
