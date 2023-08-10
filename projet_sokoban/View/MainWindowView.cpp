#include "MainWindowView.hpp"

MainWindowView :: MainWindowView(): Fl_Window(500, 200, WIDTH_WINDOW, HEIGHT_WINDOW, "Menu") {
    initButtons();
    //initWelcomeMessage();
}

//void MainWindowView :: initWelcomeMessage(){
  //  WelcomeMessage->box(FL_UP_BOX);
    //WelcomeMessage->color(FL_WHITE);
    //WelcomeMessage->labelsize(35);
    //this->add(WelcomeMessage);
//}

void MainWindowView::initButtons(){
    this->add(button1);
    this->add(button2);
    this->add(button3);

    button1->when(FL_WHEN_CHANGED);
    button1->callback(pushButton,this);

    button2->when(FL_WHEN_CHANGED);
    button2->callback(pushButton,this);

    button3->when(FL_WHEN_CHANGED);
    button3->callback(pushButton, this);
}


void MainWindowView:: addListener(void *listener){
    Listener* l = (Listener*) listener;
    listeners.push_back(l);
}

void MainWindowView::notify(const char *buttonLabel){
    listeners[0]->handleEvent(buttonLabel);
}


void MainWindowView :: pushButton(Fl_Widget* w, void * data){
    MainWindowView *mwv = static_cast <MainWindowView*>(data); 
    if (((Fl_Button*)w)->value()){
        mwv->notify(w->label());
    }
}

void MainWindowView :: draw(){
    Fl_Window :: draw();

}
