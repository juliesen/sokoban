#ifndef __GAMEVIEW_HPP__
#define __GAMEVIEW_HPP__

#include "../utils/imports.hpp"
#include "../Subject.hpp"
#include "widgets/Cell.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>

class GameView : public Fl_Window, Subject {

    vector<vector<int>> board;
    vector<Cell> cells;
    ListenerGame *lg;
    Fl_Box *stepNumber = new Fl_Box(0,0,200,200,"0");

public:

    GameView(vector<vector<int>> board);
    void draw() override;
    void updateBoard(vector<vector<int>> b){board = b;};
    int handle(int event) override;
    void notify(const char* key)override;
    void addListener(void* Listener)override;
    static void Timer_CB(void *userdata);
    void updateStepNumber(const char* value);

};

#endif