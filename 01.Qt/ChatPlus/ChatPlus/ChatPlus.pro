# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app

QT += core qml quick sql
CONFIG += c++11

TARGET = ChatPlus
#DESTDIR = ../x64/Debug

LIBS += -L"."
DEPENDPATH += .
MOC_DIR += GeneratedFiles/$(ConfigurationName)
#OBJECTS_DIR += debug
UI_DIR += GeneratedFiles
RCC_DIR += .

include(ChatPlus.pri)
