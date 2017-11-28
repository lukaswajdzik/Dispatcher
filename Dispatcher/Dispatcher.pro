TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    messages.h \
    idispatcher.hpp \
    autodistatcher.h

macx {
    _BOOST_PATH = /usr/local/Cellar/boost/1.65.1
    INCLUDEPATH += "$${_BOOST_PATH}/include/"
    LIBS += -L$${_BOOST_PATH}/lib
    ## Use only one of these:
    LIBS += -lboost_chrono-mt # using dynamic lib (not sure if you need that "-mt" at the end or not)
    #LIBS += $${_BOOST_PATH}/lib/libboost_chrono-mt.a # using static lib
}
