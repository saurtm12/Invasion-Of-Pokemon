QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_statistics.cc \
    ../Game/statistics.cc \
    ../Course/CourseLib/errors/gameerror.cc \
    ../Course/CourseLib/errors/initerror.cc

HEADERS += ../Game/statistics.hh \
    ../Course/CourseLib/errors/gameerror.hh \
    ../Course/CourseLib/errors/initerror.hh

INCLUDEPATH += ../Game/
