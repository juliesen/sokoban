#include "../utils/imports.hpp"
#include "../Listener.hpp"
#include "../View/GameView.hpp"
#include "../Model/Board.hpp"
#include "EndGameWindowController.hpp"

class GameController : public ListenerGame {

    string filename;
    GameView *gameView;
    shared_ptr<Board> board;
    Point playerPosition ;
    int stepNumber = 0;

public:

    GameController(string filename);
    void initPlayerPosition();
    void handleEvent(const char* key) override;

    void mouvementManager(Point move);
    void moveOnEmpty(Point move);
    void moveCrate(Point move, int type);
    void moveLightCrate(Point move, int type1, int type2);
    void isCrateBlocked(Point move);
    void isLightCrateBlocked(Point move);
    void moveOnTarget(Point move);
    void moveCrateOnTarget(Point move);
    void moveLightCrateOnTarget(Point move);
    void replaceTarget(Point move);
};
