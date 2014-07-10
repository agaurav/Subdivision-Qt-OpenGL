HEADERS       = glwidget.h \
                window.h \
    ofVec3f.h \
    vertex.h \
    mainwindow.h \
    model.h \
    mesh.h \
    wing.h \
    triangle.h
SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
    vertex.cpp \
    mainwindow.cpp \
    model.cpp \
    mesh.cpp \
    wing.cpp \
    triangle.cpp
RESOURCES     = textures.qrc
QT           += opengl
LIBS += -lGL -lglut -lGLU -lGLEW

LIBS += -L/usr/lib/
# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/textures
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS textures.pro images
sources.path = $$[QT_INSTALL_EXAMPLES]/opengl/textures
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)

symbian: warning(This example might not fully work on Symbian platform)
simulator: warning(This example might not fully work on Simulator platform)

FORMS += \
    mainwindow.ui

OTHER_FILES += \
    torus_tri.obj
