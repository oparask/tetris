#ifndef BOARD_H
#define BOARD_H

#include "Enums.h"
#include "Position.h"
#include "Brick.h"
#include "ShapesRotation.h"
#include <vector>
#include <optional>

class Board {
private:
    int boardWidth;
    int boardHeight;
    std::vector<std::vector<std::optional<TypeShape>>> boardArea;
    Brick currentBrick;
    const ShapesRotation* shapesRotation;

    bool isCollision(const Brick& brick) const;
    void updateArea(bool addBrick);
    std::vector<Position> getBrickBoardPositions(const Brick& brick) const;
    bool handleBrickAdjustment(const Brick& newCurBrick);

public:
    Board(int width = 10, int height = 20); //=default constructors

    bool setCurrentBrick(const Brick& brick);
    bool moveCurrentBrick(Direction direction);
    bool rotateCurrentBrick(Rotation rotation);
    int dropCurrentBrick();
    bool isCurrentBrickFallen();
    int deletePossibleLines();
    const std::vector<std::vector<std::optional<TypeShape>>>& getBoardArea() const;
};


#endif // BOARD_H
