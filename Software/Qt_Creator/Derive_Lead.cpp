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
 * @file Derive_Lead.cpp
 */

#include <Derive_Lead.h>

/*!
 * @brief Derive_Lead Constructor
 *
 * Takes the multiplicative gain for the each lead and if you want to subtract b from a and if you want to return the negative value
 *
 * @param new_a_gain Sets the input gain for the a_input
 * @param new_b_gain Sets the input gain for the b_input
 * @param new_subtract If true intermediate_output = (a - b) else (a + b)
 * @param new_negative If true output = -(intermediate_output) else (intermediate_output)
 */
Derive_Lead::Derive_Lead(double new_a_gain, double new_b_gain, bool new_subtract, bool new_negative)
{
    a_gain = new_a_gain;
    b_gain = new_b_gain;
    subtract = new_subtract;
    negative = new_negative;
}

/*!
 * @brief Takes the two input leads and outputs the derive lead
 *
 * @param a_input Positive input
 * @param b_input Negative input
 *
 * @return Derived lead
 */
double Derive_Lead::derive(double a_input, double b_input)
{
  if(subtract) {
    if (negative) {
      return -((a_gain*a_input) - (b_gain*b_input));
    } else {
      return ((a_gain*a_input) - (b_gain*b_input));
    }
  } else {
    if (negative) {
      return -((a_gain*a_input) + (b_gain*b_input));
    } else {
      return ((a_gain*a_input) + (b_gain*b_input));
    }
  }
}
