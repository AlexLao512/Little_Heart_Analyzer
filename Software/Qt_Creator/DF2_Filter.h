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
 * @file DF2_Filter.h
 */

#ifndef DF2_FILTER_H
#define DF2_FILTER_H

class DF2_Filter
{
private:
    //      51.33Hz 70Hz
    //__________    __________________________
    //          \  /
    //           \/
    //          60 Hz

    /*!
     * @brief Filter numerator coefficients
     *
     * Fs = 1000 Hz,
     * Bandstop (51.33Hz to 70Hz Reject, notch centered at 60Hz (-50dB))
     *
     */
    const double NUM[3][3] = {
		{
         0.9445360067304,                 0,                 0
		},
		{
                       1,   -1.859658381304,                 1
		},
		{
					   1,                 0,                 0
		}
	};

    /*!
     * @brief Filter denominator coefficients
     *
     * Fs = 1000 Hz,
     * Bandstop (51.33Hz to 70Hz Reject, notch centered at 60Hz (-50dB))
     */
    const double DEN[3][3] = {
		{
					   1,                 0,                 0
		},
		{
                       1,   -1.756514301359,   0.8890720134608
		},
		{
					   1,                 0,                 0
		}
	};


    double input_gain = NUM[0][0];
    double output_gain = NUM[2][0];

    double b_0 = NUM[1][0];
    double b_1 = NUM[1][1];
    double b_2 = NUM[1][2];

    double a_0 = DEN[1][0];
    double a_1 = DEN[1][1];
    double a_2 = DEN[1][2];

    double m1;
    double m2;

public:
    DF2_Filter();
    double update(double new_value);
};

#endif // DF2_FILTER_H
