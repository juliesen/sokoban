#ifndef __LISTENER_HPP__
#define __LISTENER_HPP__

#include "utils/imports.hpp"

class Listener {

    public:
        virtual void handleEvent(const char *buttonLabel)=0;
};

class ListenerGame{

    public:
        virtual void handleEvent(const char* key)=0;

};

class ListenerEndGame{
    
    public:
        virtual void handleEvent(const char* key)=0;
};

#endif