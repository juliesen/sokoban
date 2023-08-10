#include "GameController.hpp"

GameController::GameController(string filename) : filename{filename},board{make_shared<Board>(filename)} {
    gameView = new GameView(board->getBoard());
    initPlayerPosition();
    gameView->show();
    gameView->addListener(this);
    Fl::run();
}

void GameController::initPlayerPosition(){
    for(int y = 0; y < board->getSizeColumn();y++){
        for(int x = 0; x < board->getSizeRow();x++){
            if(board->getBoard()[y][x] == 4){
                playerPosition.x = x;
                playerPosition.y = y;
                return;
            }
        }
    }
}

void GameController::handleEvent(const char* key){

    if(strcmp("right",key)==0){
        mouvementManager({1,0});
    }

    else if(strcmp("left",key)==0){
        mouvementManager({-1,0});
    }

    else if(strcmp("up",key)==0){ 
        mouvementManager({0,-1});
    }

    else if(strcmp("down",key)==0){   
        mouvementManager({0,1});
    }

    else if(strcmp("restart",key)==0){
        gameView->hide();
        new GameController(filename);
    }

    else{
        cout<<"Error key"<<endl;
    }

    stepNumber ++;
        
    if(board->verifyWin()){
        gameView->hide();
        new EndGameWindowController(1);
    }
    
}

void GameController::mouvementManager(Point move){
    if(board->getBoard()[playerPosition.y + move.y][playerPosition.x + move.x] == Empty){
        moveOnEmpty(move);
    }
    else if(board->getBoard()[playerPosition.y + move.y][playerPosition.x + move.x] == Crate){
        isCrateBlocked(move);
    }
    else if(board->getBoard()[playerPosition.y + move.y][playerPosition.x + move.x] == LightCrate){
        isLightCrateBlocked(move);
    }
    else if(board->getBoard()[playerPosition.y + move.y][playerPosition.x + move.x] == Target){
        moveOnTarget(move);
    }
    else if(board->getBoard()[playerPosition.y + move.y][playerPosition.x + move.x] == CrateOnTarget){
        moveCrateOnTarget(move);
    }
    else if(board->getBoard()[playerPosition.y + move.y][playerPosition.x + move.x] == LightCrateOnTarget){
        moveLightCrateOnTarget(move);
    }
}

void GameController::moveOnEmpty(Point move){
    replaceTarget(move);
    playerPosition.x += move.x;
    playerPosition.y += move.y;
    gameView->updateBoard(board->getBoard());
    gameView->draw();
}

void GameController::isCrateBlocked(Point move){
    if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Empty){
        moveCrate(move, Crate);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Target){
        moveCrate(move, CrateOnTarget);
    }
}
void GameController::isLightCrateBlocked(Point move){
    if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Empty){
        moveLightCrate(move, LightCrate, -1);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Target){
        moveLightCrate(move, LightCrateOnTarget, -1);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == LightCrate && board->getBoard()[playerPosition.y + (move.y*3)][playerPosition.x + (move.x*3)] == Empty){
        moveLightCrate(move, LightCrate, LightCrate);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == LightCrate && board->getBoard()[playerPosition.y + (move.y*3)][playerPosition.x + (move.x*3)] == Target){
        moveLightCrate(move, LightCrate, LightCrateOnTarget);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == LightCrateOnTarget && board->getBoard()[playerPosition.y + (move.y*3)][playerPosition.x + (move.x*3)] == Empty){
        moveLightCrate(move, LightCrateOnTarget, LightCrate);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == LightCrateOnTarget && board->getBoard()[playerPosition.y + (move.y*3)][playerPosition.x + (move.x*3)] == Target){
        moveLightCrate(move, LightCrateOnTarget, LightCrateOnTarget);
    }
}

void GameController::moveCrate(Point move, int type){
    replaceTarget(move);
    playerPosition.x += move.x;
    playerPosition.y += move.y;
    board->modifyBoard({playerPosition.x, playerPosition.y},{playerPosition.x + move.x, playerPosition.y + move.y},Player,type);
    gameView->updateBoard(board->getBoard());
    gameView->draw();
}

void GameController::moveLightCrate(Point move, int type1, int type2){
    replaceTarget(move);
    playerPosition.x += move.x;
    playerPosition.y += move.y;
    board->modifyBoard({playerPosition.x, playerPosition.y},{playerPosition.x + move.x, playerPosition.y + move.y}, Player, type1);
    if(type2 > -1){
        board->modifyBoard({playerPosition.x + move.x, playerPosition.y + move.y},{playerPosition.x + move.x*2, playerPosition.y + move.y*2},type1, type2); 
    }
    gameView->updateBoard(board->getBoard());
    gameView->draw(); 
}

void GameController::moveOnTarget(Point move){
    if(board->getBoard()[playerPosition.y][playerPosition.x]==PlayerOnTarget){
        board->modifyBoard(playerPosition,{playerPosition.x + move.x, playerPosition.y + move.y},Target, PlayerOnTarget);
    }
    else{
        board->modifyBoard(playerPosition,{playerPosition.x + move.x, playerPosition.y + move.y},Empty, PlayerOnTarget);    
    }
    playerPosition.x += move.x;
    playerPosition.y += move.y;
    gameView->updateBoard(board->getBoard());
    gameView->draw();
}

void GameController::moveCrateOnTarget(Point move){
    if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Empty || board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Target ){
        isCrateBlocked(move);
        moveOnTarget({0,0});
    }
}
void GameController::moveLightCrateOnTarget(Point move){
    if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] != Wall && board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] != Crate 
        &&  board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] != CrateOnTarget){
        isLightCrateBlocked(move);
        moveOnTarget({0,0});
    }
}

void GameController::replaceTarget(Point move){
    if(board->getBoard()[playerPosition.y][playerPosition.x]==PlayerOnTarget){
        board->modifyBoard(playerPosition,{playerPosition.x + move.x, playerPosition.y + move.y},Target, Player);    
    }
    else{
        board->modifyBoard(playerPosition,{playerPosition.x + move.x, playerPosition.y + move.y},Empty, Player);
    }
}