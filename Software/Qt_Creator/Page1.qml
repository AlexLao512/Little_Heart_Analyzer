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

import QtQuick 2.7
import QtCharts 2.1
import ECG_Data_Provider 1.0
import ECG_DSP 1.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Page1Form {

    // button1.onClicked: {
    //console.log("Button Pressed. Entered text: " + textField1.text);
    //}

    //ECG_Data_Provider {
    //    id: ecg
    //}
    ECG_DSP {
        id: ecg_dsp
    }
    RowLayout {
        id: buttonrow
        height: 60
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.topMargin: 8
        anchors.top: parent.top
        //anchors.bottom:graphrow1.top
        Layout.fillHeight: true

        TextField {
            id: textField1
            text: "Serial Port"
            Layout.fillHeight: false
            Layout.columnSpan: 1
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignLeft
            Layout.rowSpan: 1
            placeholderText: qsTr("Text Field")
        }

        Button {
            id: button1
            //x: 550
            //height: 60
            text: qsTr("Connect")
            spacing: 0
        }
        Switch {
            id: switch1
            text: qsTr("60Hz filter ON/OFF")
        }
        TextField {
            id: heartRateText
            text: qsTr("HR")
            font.wordSpacing: 2
            font.pointSize: 25
            horizontalAlignment: Text.AlignHCenter
        }
    }
    ColumnLayout {
        id: leftcolumn
        anchors.right: parent.horizontalCenter
        anchors.left: parent.left
        anchors.top: buttonrow.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        anchors.topMargin: -10
        anchors.rightMargin: -20
        anchors.bottomMargin: -20

        RowLayout {
            id: toprowleft
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            Layout.fillHeight: true
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.rightMargin: 0
            anchors.bottomMargin: 0

            ChartView {
                id: ecgPlot_L1
                legend.visible: false
                anchors.right: parent.horizontalCenter
                anchors.left: parent.left
                anchors.top: parent.top
                width: 307
                height: 207
                Layout.fillHeight: true
                margins.right: 0
                margins.left: 0
                margins.top: 0
                margins.bottom: 0
                anchors.rightMargin: -20

                title: "Lead I"
                antialiasing: true

                ValueAxis {
                    id: valueAxisX0
                    min: 0
                    max: 2048
                    labelsVisible: false
                }

                ValueAxis {
                    id: valueAxisY0
                    min: -17000
                    max: 17000
                    titleText: "Voltage"
                }

                LineSeries {
                    id: ecgData_L1
                    name: "Lead I"

                    axisX: valueAxisX0
                    axisY: valueAxisY0

                    useOpenGL: true
                }
            }
            ChartView {
                id: ecgPlot_aVR
                legend.visible: false
                title: "aVR"
                anchors.right: parent.right
                anchors.left: parent.horizontalCenter
                anchors.top: parent.top
                Layout.fillHeight: true
                margins.right: 0
                margins.left: 0
                margins.top: 0
                margins.bottom: 0
                anchors.leftMargin: -20

                width: 307
                height: 207

                antialiasing: true

                ValueAxis {
                    id: valueAxisX1
                    min: 0
                    max: 2048
                    labelsVisible: false
                }

                ValueAxis {
                    id: valueAxisY1
                    min: -17000
                    max: 17000
                    labelsVisible: false
                }

                LineSeries {
                    id: ecgData_aVR
                    name: "aVR"

                    axisX: valueAxisX1
                    axisY: valueAxisY1

                    useOpenGL: true
                }
            }
        }
        RowLayout {
            id: secondrowleft
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.top: toprowleft.bottom
            Layout.fillHeight: true
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.rightMargin: 0
            anchors.bottomMargin: 0

            ChartView {
                id: ecgPlot_L2

                anchors.right: parent.horizontalCenter
                anchors.left: parent.left
                anchors.top: parent.top
                Layout.fillHeight: true
                legend.visible: false
                title: "Lead II"
                margins.right: 0
                margins.left: 0
                margins.top: 0
                margins.bottom: 0
                anchors.rightMargin: -20

                width: 307
                height: 207
                antialiasing: true

                ValueAxis {
                    id: valueAxisX4
                    min: 0
                    max: 2048
                    labelsVisible: false
                }

                ValueAxis {
                    id: valueAxisY4
                    min: -17000
                    max: 17000
                    titleText: "Voltage"
                }

                LineSeries {
                    id: ecgData_L2
                    name: "Lead II"

                    axisX: valueAxisX4
                    axisY: valueAxisY4

                    useOpenGL: true
                }
            }
            ChartView {
                id: ecgPlot_aVL

                anchors.right: parent.right
                anchors.left: parent.horizontalCenter
                anchors.top: parent.top
                Layout.fillHeight: true
                legend.visible: false
                title: "aVL"
                margins.right: 0
                margins.left: 0
                margins.top: 0
                margins.bottom: 0
                anchors.leftMargin: -20

                width: 307
                height: 207

                antialiasing: true

                ValueAxis {
                    id: valueAxisX5
                    min: 0
                    max: 2048
                    labelsVisible: false
                }

                ValueAxis {
                    id: valueAxisY5
                    min: -17000
                    max: 17000
                    labelsVisible: false
                }

                LineSeries {
                    id: ecgData_aVL
                    name: "aVL"

                    axisX: valueAxisX5
                    axisY: valueAxisY5

                    useOpenGL: true
                }
            }
        }
        RowLayout {
            id: thirdleft
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: secondrowleft.bottom
            anchors.bottom: parent.bottom
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.rightMargin: 0
            anchors.bottomMargin: 0

            ChartView {
                id: ecgPlot_L3

                anchors.right: parent.horizontalCenter
                anchors.left: parent.left
                anchors.top: parent.top
                Layout.fillHeight: true
                legend.visible: false
                title: "Lead III"
                margins.right: 0
                margins.left: 0
                margins.top: 0
                margins.bottom: -5
                anchors.rightMargin: -20

                width: 307
                height: 207

                antialiasing: true

                ValueAxis {
                    id: valueAxisX8
                    min: 0
                    max: 2048
                    labelsVisible: false
                }

                ValueAxis {
                    id: valueAxisY8
                    min: -17000
                    max: 17000
                    titleText: "Voltage"
                }

                LineSeries {
                    id: ecgData_L3
                    name: "Lead III"

                    axisX: valueAxisX8
                    axisY: valueAxisY8

                    useOpenGL: true
                }
            }
            ChartView {
                id: ecgPlot_aVF

                anchors.right: parent.right
                anchors.left: parent.horizontalCenter
                anchors.top: parent.top
                Layout.fillHeight: true
                legend.visible: false
                title: "aVF"
                margins.right: 0
                margins.left: 0
                margins.top: 0
                margins.bottom: -5
                anchors.leftMargin: -20

                width: 307
                height: 207

                antialiasing: true

                ValueAxis {
                    id: valueAxisX9
                    min: 0
                    max: 2048
                    labelsVisible: false
                }

                ValueAxis {
                    id: valueAxisY9
                    min: -17000
                    max: 17000
                    labelsVisible: false
                }

                LineSeries {
                    id: ecgData_aVF
                    name: "aVF"

                    axisX: valueAxisX9
                    axisY: valueAxisY9

                    useOpenGL: true
                }
            }
        }
    }
    ColumnLayout {
        id: rightcolumn
        anchors.right: parent.right
        anchors.left: parent.horizontalCenter
        anchors.top: buttonrow.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        anchors.topMargin: -10
        anchors.rightMargin: 0
        anchors.bottomMargin: -20

        RowLayout {
            id: toprowright
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            Layout.fillHeight: true

            ChartView {
                id: ecgPlot_V1

                anchors.right: parent.horizontalCenter
                anchors.left: parent.left
                anchors.top: parent.top
                Layout.fillHeight: true
                margins.right: 0
                margins.left: 0
                margins.top: 0
                margins.bottom: 0
                anchors.rightMargin: -30

                width: 307
                height: 207
                legend.visible: false
                title: "V1"

                antialiasing: true

                ValueAxis {
                    id: valueAxisX2
                    min: 0
                    max: 2048
                    labelsVisible: false
                }

                ValueAxis {
                    id: valueAxisY2
                    min: -17000
                    max: 17000
                    labelsVisible: false
                }

                LineSeries {
                    id: ecgData_V1
                    name: "V1"

                    axisX: valueAxisX2
                    axisY: valueAxisY2

                    useOpenGL: true
                }
            }
            ChartView {
                id: ecgPlot_V4

                anchors.right: parent.right
                anchors.left: parent.horizontalCenter
                anchors.top: parent.top
                Layout.fillHeight: true
                margins.right: 0
                margins.left: 0
                margins.top: 0
                margins.bottom: 0
                anchors.leftMargin: -30

                width: 307
                height: 207
                legend.visible: false
                title: "V4"
                antialiasing: true

                ValueAxis {
                    id: valueAxisX3
                    min: 0
                    max: 2048
                    labelsVisible: false
                }

                ValueAxis {
                    id: valueAxisY3
                    min: -17000
                    max: 17000
                    labelsVisible: false
                }

                LineSeries {
                    id: ecgData_V4
                    name: "V4"

                    axisX: valueAxisX3
                    axisY: valueAxisY3

                    useOpenGL: true
                }
            }
        }
        RowLayout {
            id: secondrowright
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.top: toprowright.bottom
            Layout.fillHeight: true

            ChartView {
                id: ecgPlot_V2

                anchors.right: parent.horizontalCenter
                anchors.left: parent.left
                anchors.top: parent.top
                Layout.fillHeight: true
                margins.right: 0
                margins.left: 0
                margins.top: 0
                margins.bottom: 0
                anchors.rightMargin: -20

                //anchors.bottomMargin: -40
                width: 307
                height: 207
                legend.visible: false
                title: "V2"
                antialiasing: true

                ValueAxis {
                    id: valueAxisX6
                    min: 0
                    max: 2048
                    labelsVisible: false
                }

                ValueAxis {
                    id: valueAxisY6
                    min: -17000
                    max: 17000
                    labelsVisible: false
                }

                LineSeries {
                    id: ecgData_V2
                    name: "V2"

                    axisX: valueAxisX6
                    axisY: valueAxisY6

                    useOpenGL: true
                }
            }
            ChartView {
                id: ecgPlot_V5

                anchors.right: parent.right
                anchors.left: parent.horizontalCenter
                anchors.top: parent.top
                Layout.fillHeight: true
                margins.right: 0
                margins.left: 0
                margins.top: 0
                margins.bottom: 0
                anchors.leftMargin: -20

                //anchors.bottomMargin: -40
                width: 307
                height: 207
                legend.visible: false
                title: "V5"

                antialiasing: true

                ValueAxis {
                    id: valueAxisX7
                    min: 0
                    max: 2048
                    labelsVisible: false
                }

                ValueAxis {
                    id: valueAxisY7
                    min: -17000
                    max: 17000
                    labelsVisible: false
                }

                LineSeries {
                    id: ecgData_V5
                    name: "V5"

                    axisX: valueAxisX7
                    axisY: valueAxisY7

                    useOpenGL: true
                }
            }
        }
        RowLayout {
            id: thirdright
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: secondrowright.bottom
            anchors.bottom: parent.bottom
            Layout.fillHeight: true

            ChartView {
                id: ecgPlot_V3

                anchors.right: parent.horizontalCenter
                anchors.left: parent.left
                anchors.top: parent.top
                Layout.fillHeight: true
                margins.right: 0
                margins.left: 0
                margins.top: 0
                margins.bottom: -5
                anchors.rightMargin: -20

                width: 307
                height: 207
                legend.visible: false
                title: "V3"

                antialiasing: true

                ValueAxis {
                    id: valueAxisX10
                    min: 0
                    max: 2048
                    labelsVisible: false
                }

                ValueAxis {
                    id: valueAxisY10
                    min: -17000
                    max: 17000
                    labelsVisible: false
                }

                LineSeries {
                    id: ecgData_V3
                    name: "V3"

                    axisX: valueAxisX10
                    axisY: valueAxisY10

                    useOpenGL: true
                }
            }
            ChartView {
                id: ecgPlot_V6

                anchors.right: parent.right
                anchors.left: parent.horizontalCenter
                anchors.top: parent.top
                Layout.fillHeight: true
                margins.right: 0
                margins.left: 0
                margins.top: 0
                margins.bottom: -5
                anchors.leftMargin: -20

                width: 307
                height: 207
                legend.visible: false
                title: "V6"

                antialiasing: true

                ValueAxis {
                    id: valueAxisX11
                    min: 0
                    max: 2048
                    labelsVisible: false
                }

                ValueAxis {
                    id: valueAxisY11
                    min: -17000
                    max: 17000
                    labelsVisible: false
                }

                LineSeries {
                    id: ecgData_V6
                    name: "V6"

                    axisX: valueAxisX11
                    axisY: valueAxisY11

                    useOpenGL: true
                }
            }
        }
    }
    Timer {
        id: ecgRefreshTimer
        interval: 1 / 30 * 1000 // 30 Hz
        running: true
        repeat: true
        onTriggered: {
            ecg_dsp.update(ecgPlot_V1.series(0), 0)
            ecg_dsp.update(ecgPlot_V6.series(0), 1)
            ecg_dsp.update(ecgPlot_V5.series(0), 2)
            ecg_dsp.update(ecgPlot_V4.series(0), 3)
            ecg_dsp.update(ecgPlot_V3.series(0), 4)
            ecg_dsp.update(ecgPlot_V2.series(0), 5)
            ecg_dsp.update(ecgPlot_L2.series(0), 6)
            ecg_dsp.update(ecgPlot_L1.series(0), 7)
            ecg_dsp.update(ecgPlot_L3.series(0), 8)
            ecg_dsp.update(ecgPlot_aVR.series(0), 9)
            ecg_dsp.update(ecgPlot_aVL.series(0), 10)
            ecg_dsp.update(ecgPlot_aVF.series(0), 11)

            heartRateText.text = ecg_dsp.qmlHeartRate()
        }
    }
}
