#-------------------------------------------------
#
# Project created by QtCreator 2015-08-26T16:47:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoveTrailingNewLines
TEMPLATE = app


SOURCES += main.cpp\
        main_window.cpp \
    utils.cpp \
    edit_files_error.cpp

HEADERS  += main_window.hpp \
    utils.hpp \
    edit_files_error.hpp

CONFIG += c++11

LIBS += -lboost_filesystem -lboost_system
