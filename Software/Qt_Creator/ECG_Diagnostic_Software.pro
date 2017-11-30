QT += qml quick charts
QT += serialport

CONFIG += c++11

SOURCES += main.cpp \
    ECG_Data_Provider.cpp \
    DF2_Filter.cpp \
    Derive_Lead.cpp \
    ECG_DSP.cpp \
    Dummy_Algorithm.cpp \
    Heartrate.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ECG_Data_Provider.h \
    DF2_Filter.h \
    Derive_Lead.h \
    ECG_DSP.h \
    Global.h \
    Dummy_Algorithm.h \
    Heartrate.h
