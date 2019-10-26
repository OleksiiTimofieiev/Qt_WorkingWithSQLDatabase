# /* as it is going to be library */
QT -= gui
# /* add modules of sql */
QT += core sql
# C++ standard
CONFIG += c++11
#/* using as lib */
TEMPLATE = lib
#path to place binary or library
DESTDIR = $$PWD/../shared/lib

INCLUDEPATH += $$PWD/include

HEADERS += \
    include/ConnectionManager.h \
    include/dbtypes.h

SOURCES += \
    src/ConnectionManager.cpp
