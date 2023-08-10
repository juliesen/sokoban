#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "../utils/imports.hpp"

class Board {
private:

    string filename;
    vector<vector<int>> board;
    int bestScore;
    int limit;

public:

    Board(string filename);
    void initBoard(string filename);
    vector<vector<int>> getBoard(){return board;};
    int getSizeColumn(){return (int)board.size();};
    int getSizeRow(){return (int)board[0].size();};
    void modifyBoard(Point posInit, Point nextPos, int typePosInit, int typeNextPos);
    bool verifyWin();


};

#endif