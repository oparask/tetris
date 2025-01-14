#ifndef GAME_H
#define GAME_H

#include "BrickBag.h"
#include "Board.h"
#include "Score.h"
#include "Level.h"
#include "Enums.h"
#include "../util/Observable.h"

class Game : public Observable {
    GameState gameState;
    Board gameBoard;
    BrickBag gameBrickBag;
    Score gameScore;
    Level gameLevel;
    const int duration = 10; // The duration of the game in minutes

    void updateGame(int dropDistance);
    void setCurrentBrick();
    bool checkVictory(); // Conditions to win

public:
    Game(int width = 10, int height = 20, bool emptyBoard = true);
    void resetGame(int width = 10, int height = 20, bool emptyBoard = true);
    void start();
    void moveCurrentBrick(Direction direction);
    void rotateCurrentBrick(Rotation rotation);
    void dropCurrentBrick();
    bool isGameOver();
    const GameState& getGameState() const;
    const Board& getGameBoard() const;
    const Level& getGameLevel() const;
    const Score& getGameScore() const;
    void setState(GameState);
    const int getDuration() const;
};

#endif // GAME_H
