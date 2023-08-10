#include "MainWindowController.hpp"

MainWindowController ::MainWindowController(){
    mainView = new MainWindowView();
    mainView->addListener(this);
    mainView->show();
    Fl::run();
}

/**
MainWindowController :: ~MainWindowController(){
    //mainView->removeListener(this);
}*/

void MainWindowController::handleEvent(const char *buttonLabel) {
    if(strcmp(buttonLabel,"Level1") == 0){
        mainView->hide();
        new GameController("resource/boards/board1.txt");
    }
    else if (strcmp(buttonLabel,"Level2") == 0){
        mainView->hide();
        new GameController("resource/boards/board2.txt");
    }
    else if (strcmp(buttonLabel,"Level3") == 0){
        mainView->hide();
        new GameController("resource/boards/board3.txt");
    }
    else{
        cout<<"Error wrong button label !\n";
    }
} 