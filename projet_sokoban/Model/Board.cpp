#include "Board.hpp"

Board::Board(string filename) : filename{filename} {
    initBoard(filename);
}

void Board::initBoard(string filename) {
    string line;
    ifstream file(filename);

    while(getline(file,line)){
        vector<int> v = {};
        for(char c:line){
            v.push_back(c - '0');
        }
        board.push_back(v);
    }
}

void Board::modifyBoard(Point posInit, Point nextPos, int typePosInit, int typeNextPos){
    board[posInit.y][posInit.x] = typePosInit;
    board[nextPos.y][nextPos.x] = typeNextPos;
}

bool Board::verifyWin(){
    int x = 0;
    while(x < getSizeRow()){
        int y = 0;
        while(y < getSizeColumn()){
            if(board[y][x] == Target || board[y][x] == PlayerOnTarget){
                return false;
            }
            y++;
        }
        x++;
    }
    return true;
}