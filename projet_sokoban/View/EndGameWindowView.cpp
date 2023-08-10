#include "EndGameWindowView.hpp"

EndGameWindowView::EndGameWindowView(int gameResult): Fl_Window(500, 200, WIDTH_WINDOW, HEIGHT_WINDOW, "Game Over") {
    initMessage(gameResult);

    this->add(button);

    button->when(FL_WHEN_CHANGED);
    button->callback(pushButton,this);
}

void EndGameWindowView:: addListener(void *listener){
    Listener* l = (Listener*) listener;
    listeners.push_back(l);
}

void EndGameWindowView::notify(const char *buttonLabel){
    listeners[0]->handleEvent(buttonLabel);
}

void EndGameWindowView ::pushButton(Fl_Widget* w, void* data){
    EndGameWindowView *egwv = static_cast <EndGameWindowView*>(data); 
    if (((Fl_Button*)w)->value()){
        egwv->notify(w->label());
    }
}

void EndGameWindowView::initMessage(int gameResult){
    this->add(message);
    message->labelsize(35);
    if(gameResult){
        message->label("You Win !");
    }
    else{
        message->label("You Lose :(");
    }
}