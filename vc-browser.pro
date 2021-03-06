QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vc-browser
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic
DEFINES += _GLIBCXX_USE_CXX11_ABI=0 # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66145

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += src/main.cpp \
	src/vcbrowser.cpp \
#	src/abstractitem.cpp \
	src/cbf.cpp \
	src/file.cpp \
	src/directory.cpp \
	src/abstractfile.cpp \
	src/txt.cpp \

HEADERS  += src/vcbrowser.h \
#	src/abstractitem.h \
	src/cbf.h \
	src/file.h \
	src/directory.h \
	src/abstractfile.h \
	src/txt.h \
