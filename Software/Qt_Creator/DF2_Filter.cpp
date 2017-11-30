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
 * @file DF2_Filter.cpp
 */

#include <DF2_Filter.h>

/*!
 * @brief DF2_Filter Constructor
 *
 * Does nothing for now, this should take the filter constants and intialize the (variable) filter constant array
 */
DF2_Filter::DF2_Filter()
{
    return;
}

/*!
 * @brief Updates the filter with the next input and returns the next output
 *
 * Implements a direct form II second order, single section filter
 *
 * @param newValue Filter input
 *
 * @return Filter output
 */
double DF2_Filter::update(double new_value)
{

    double mid1  = input_gain*(a_0*new_value) + (-a_1*m1) + (-a_2*m2);
    double output = (b_0 * mid1) + (b_1 * m1) + (b_2 * m2);

    m2 = m1;
    m1 = mid1;

    return output;
}
