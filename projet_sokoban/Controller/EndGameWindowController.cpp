#include "EndGameWindowController.hpp"

EndGameWindowController::EndGameWindowController(int gameResult){
    endGameView = new EndGameWindowView(gameResult);
    endGameView->show();
    endGameView->addListener(this);
    Fl::run();
}

void EndGameWindowController::handleEvent(const char* var){
    if(strcmp(var,"Quit the game")==0){
        endGameView->hide();
        exit(0);
    }
    else{
        cout<<"Error label"<<endl;
    }
}