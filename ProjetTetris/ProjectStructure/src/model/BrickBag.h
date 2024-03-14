#ifndef BRICKBAG_H
#define BRICKBAG_H

#include "Brick.h"
#include "Position.h"
#include "Enums.h"
#include <vector>
#include <random>

class BrickBag {
private:
    const Position startPosition;
    std::vector<Brick> bricks;
    std::mt19937 randomEngine;  // Random engine
    int currentBrickIndex;  // Index to track the current position in the bricks vector

    void shuffleBricks();

public:
    BrickBag(Position start = Position(4, 1));

    Brick getNextBrick();
};

#endif // BRICKBAG_H