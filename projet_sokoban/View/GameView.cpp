#include "GameView.hpp"

GameView::GameView(vector<vector<int>> board) : Fl_Window(300, 100, GAME_WIDTH_WINDOW, GAME_HEIGHT_WINDOW, "Game"), board{board}{
    this->add(stepNumber);
    stepNumber->labelsize(35);
    Fl::add_timeout(1.0 / 60, Timer_CB, this);
    resizable(this);
}

void GameView::draw(){
    Fl_Window::draw();
    cells.clear();
    int x = 70;
    int y = 200;
    Fl_Color color;
    for (int i = 0; i < (int)board.size(); i ++){
        for(int j = 0; j < (int)board[0].size(); j++){
            switch ((int)board[i][j]) {
            case Empty:
                color = FL_WHITE;
                break;

            case Wall:
                color = FL_GRAY;
                break;
           
            case Crate:
                color = FL_RED;
                break;

            case Target:
                color = FL_GREEN;
                break;

            case Player:
                color = FL_BLUE;
                break;

            case CrateOnTarget:
                color = FL_YELLOW;
                break;
            case PlayerOnTarget:
                color = FL_BLACK;
                break;
            case LightCrate:
                color = FL_MAGENTA;
                break;
            case LightCrateOnTarget:
                color = FL_YELLOW;
                break;
            default:
                color = FL_WHITE;
                break;
            }
            cells.push_back({{y, x}, WIDTH_BOX, HEIGHT_BOX, color});
            y += 70;
        }
        y = 200;
        x += 70;   
    }
    for(auto cell:cells){cell.draw();
    }
}

void GameView::updateStepNumber(const char* value){
    stepNumber->label(value);
}

int GameView::handle(int event) {
    if (event == FL_KEYDOWN) {

      switch (Fl::event_key()) {

        case FL_Right:
            notify("right");
            break;
        case FL_Left:
            notify("left");
            break;
        case FL_Up:
            notify("up");
            break;
        case FL_Down:
            notify("down");
            break;
        case 'r':
            notify("restart");
            break;
        default: {
          // nothing to do
        }
      }
    }

    return false;
}


void GameView::addListener(void* listener){
    ListenerGame* l = (ListenerGame*) listener;
    lg=l;
}



void GameView::notify(const char* key){
    lg->handleEvent(key);
}

void GameView::Timer_CB(void *userdata) {
    GameView *o = static_cast<GameView *>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0 / 60, Timer_CB, userdata);
  }