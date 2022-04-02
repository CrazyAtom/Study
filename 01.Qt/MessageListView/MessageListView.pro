QT += quick sql

HEADERS += \
    DbManager.h \
    MessageItem.h \
    Provider.h \
    QObjectListModel.h

SOURCES += \
        DbManager.cpp \
        MessageItem.cpp \
        Provider.cpp \
        main.cpp

resources.files += \
                main.qml \
                StringItemDelegate.qml \
                resource/send_over.svg \
                resource/send_normal.svg \
                resource/delete_normal.svg \
                resource/delete_over.svg

resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    StringItemDelegate.qml


