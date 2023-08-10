#ifndef __SUBJECT_HPP__
#define __SUBJECT_HPP__

#include "utils/imports.hpp"
#include "Listener.hpp"


class Subject{
    
    public:

        virtual void addListener(void* listener){
            Listener* l = (Listener*) listener;
            listeners.push_back(l);}
        void removeListener(Listener* listener){remove(listeners.begin(),listeners.end(),listener);}
        virtual void notify(const char* buttonLabel)=0;
    
    protected:
    
        vector <Listener*> listeners;

};

#endif