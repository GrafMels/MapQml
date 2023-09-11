QT += quick quickwidgets positioning core

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
CONFIG += c++17

SOURCES += \
        line_f_list.cpp \
        logic.cpp \
        main.cpp \
        restricted_area.cpp \
        restricted_area_list.cpp \
        way_point.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    line_f_list.h \
    logic.h \
    restricted_area.h \
    restricted_area_list.h \
    way_point.h

DISTFILES += \
    RestrictedArea.qml

