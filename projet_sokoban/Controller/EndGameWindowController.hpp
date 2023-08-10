#ifndef __ENDGAMEWINDOWCONTROLLER_HPP__
#define __ENDGAMEWINDOWCONTROLLER_HPP__

#include "../utils/imports.hpp"
#include "../Listener.hpp"
#include "../View/EndGameWindowView.hpp"


class EndGameWindowController : public ListenerEndGame{

    EndGameWindowView *endGameView;

public:

    EndGameWindowController(int gameResult);
    void handleEvent(const char* var) override;

};


#endif