#-------------------------------------------------
#
# Project created by QtCreator 2014-02-01T18:55:34
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Easy_Invoice
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addcustomer.cpp \
    invoice.cpp \
    customer.cpp \
    allcompanyinvoices.cpp \
    databasemanager.cpp

HEADERS  += mainwindow.h \
    addcustomer.h \
    invoice.h \
    customer.h \
    allcompanyinvoices.h \
    databasemanager.h

FORMS    += mainwindow.ui \
    addcustomer.ui \
    allcompanyinvoices.ui

RESOURCES += \
    resources.qrc
