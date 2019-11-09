# /* as it is going to be library */
QT -= gui
# /* add modules of sql */
QT += core sql
# C++ standard
CONFIG += c++11
#/* using as lib */
TEMPLATE = lib
#path to place binary or library

DEFINES += BUILD_TESTS
DESTDIR = $$PWD/../shared/lib

INCLUDEPATH += $$PWD/include

HEADERS += \
    include/ConnectionManager.h \
    include/Executor.h \
    include/Processor.h \
    include/Selector.h \
    include/dbtypes.h

SOURCES += \
    src/ConnectionManager.cpp \
    src/Executor.cpp \
    src/Processor.cpp \
    src/Selector.cpp
