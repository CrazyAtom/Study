QT += core qml quick sql

HEADERS += \
            ./models/sqlcontactmodel.h \
            ./models/sqlconversationsmodel.h \
            ./models/sqlconversationmodel.h \

SOURCES += \
            ./main.cpp \
            ./models/sqlcontactmodel.cpp \
            ./models/sqlconversationsmodel.cpp \
            ./models/sqlconversationmodel.cpp \

resources.files += \

resources.prefix = /$${TARGET}
RESOURCES += resources \
            ./qml.qrc \
            ./images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
