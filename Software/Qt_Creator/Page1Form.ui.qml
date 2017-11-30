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

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
//this page needs to be deleted but it crashed when I erased everything on it
Item {
    id: item1



    RowLayout {
    id: graphrow1
    //height:60
    anchors.rightMargin: 10
    anchors.leftMargin: 10
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.topMargin: 8
    anchors.top: buttonrow.bottom
    anchors.bottom:graphrow2.top
    //Layout.fillHeight: true

    }
    RowLayout {
    //height:60
    id: graphrow2
    anchors.rightMargin: 10
    anchors.leftMargin: 10
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.topMargin: 8
    //anchors.top: graphrow1.bottom
    anchors.bottom:graphrow3.top
    //Layout.fillHeight: true
    }
    RowLayout {
    //height: 60
    id: graphrow3
    anchors.rightMargin: 10
    anchors.leftMargin: 10
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.topMargin: 8
    //anchors.top: graphrow2.bottom
    anchors.bottom:parent.bottom
    //Layout.fillHeight: true

    }



}
