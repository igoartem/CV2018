QT += core
QT += gui

CONFIG += c++14

TARGET = CV
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    cvimage.cpp

HEADERS += \
    cvimage.h
