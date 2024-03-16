#include <catch2/catch_test_macros.hpp>
#define private public
#include "model/Board.h"


TEST_CASE("Board initialization", "[board]") {
    Board board; //width = 10, height = 20
    REQUIRE(board.getBoardArea()[0].size() == 10); // Check if the board width is initialized correctly
    REQUIRE(board.getBoardArea().size() == 20); // Check if the board height is initialized correctly

    //we make a test here because we use resize() in the Board constructor
    auto boardArea = board.getBoardArea();
    // Verify that all cells are initially empty (no shapes)
        for (const auto& row : boardArea) {
            for (const auto& cell : row) {
                REQUIRE_FALSE(cell.has_value());
            }
        }


}


TEST_CASE("Set current brick", "[board]") {

    Board board;
    Brick brick(TypeShape::L_SHAPE, Orientation::UP, Position(0, 1));
    REQUIRE(board.setCurrentBrick(brick) == true); // Check if the brick can be successfully set

    auto boardArea = board.getBoardArea();

    // Check if the brick is set correctly on the board
    REQUIRE(boardArea[0][0].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[1][0].value() == TypeShape::L_SHAPE); //Position(0,1) correspond to [1][0] in the boardArea
    REQUIRE(boardArea[2][0].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[2][1].value() == TypeShape::L_SHAPE);



}

//MOVE CURRENT BRICK OUT OF BOUNDS

TEST_CASE("Move current Brick left out of bounds", "[board]") {
    Board board;
    Brick brick(TypeShape::L_SHAPE, Orientation::UP, Position(0, 1));
    board.setCurrentBrick(brick);
    REQUIRE_FALSE(board.moveCurrentBrick(Direction::LEFT)); // Check that the brick cannot be translated to the bc out of bounds


    //check that the brick didn't move on the bordArea
    auto boardArea = board.getBoardArea();
    REQUIRE(boardArea[0][0].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[1][0].value() == TypeShape::L_SHAPE); //Position(0,1) correspond to [1][0] in the boardArea
    REQUIRE(boardArea[2][0].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[2][1].value() == TypeShape::L_SHAPE);

    //check the currentBrick's parameters, its board position isn't supposed to be changed
    REQUIRE(board.currentBrick.getBoardPosition() ==  Position(0,1));
}


//MOVE CURRENT BRICK OUT OF BOUNDS
TEST_CASE("Move current Brick right out of bounds", "[board]") {
    Board board;
    Brick brick(TypeShape::L_SHAPE, Orientation::UP, Position(8, 1));
    board.setCurrentBrick(brick);
    REQUIRE_FALSE(board.moveCurrentBrick(Direction::RIGHT)); // Check that the brick cannot be translated to the right bc out of bounds

    //check that the brick didn't move on the bordArea
    auto boardArea = board.getBoardArea();
    REQUIRE(boardArea[0][8].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[1][8].value() == TypeShape::L_SHAPE); //Position(1, 8) correspond to [1][8] in the boardArea
    REQUIRE(boardArea[2][8].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[2][9].value() == TypeShape::L_SHAPE);

    //check the currentBrick's parameters, its board position isn't supposed to be changed
    REQUIRE(board.currentBrick.getBoardPosition() ==  Position(8,1));
}


TEST_CASE("Move current Brick down out of bounds", "[board]") {
    Board board;
    Brick brick(TypeShape::L_SHAPE, Orientation::UP, Position(0, 18));
    board.setCurrentBrick(brick);
    REQUIRE_FALSE(board.moveCurrentBrick(Direction::DOWN)); // Check that the brick cannot be translated down bc out of bounds

    //check that the brick didn't move on the bordArea
    auto boardArea = board.getBoardArea();
    REQUIRE(boardArea[17][0].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[18][0].value() == TypeShape::L_SHAPE); //Position(0,18) correspond to [18][0] in the boardArea
    REQUIRE(boardArea[19][0].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[19][1].value() == TypeShape::L_SHAPE);

    //check the currentBrick's parameters, its board position isn't supposed to be changed
    REQUIRE(board.currentBrick.getBoardPosition() ==  Position(0,18));
}



//MOVE CURRENT BRICK IN THE BOUNDS BUT COLLISION

TEST_CASE("Move current Brick collision", "[board]") {
    Board board;

    std::vector<std::vector<std::optional<TypeShape>>> testBoardArea;
    // Initialize the testBoardArea vector with the same width and height as boardArea
    testBoardArea.resize(board.getBoardHeight());
    for (int i = 0; i < testBoardArea.size(); ++i) {
        testBoardArea[i].resize(board.getBoardWidth());
    }

    //we place a brick on the testBoardArea in order to check collisions
    testBoardArea[4][4] = TypeShape::L_SHAPE;

    board.setBoardArea(testBoardArea);

    //MOVE LEFT
    Brick brickLeft(TypeShape::L_SHAPE, Orientation::UP, Position(5, 4));
    board.setCurrentBrick(brickLeft);

    REQUIRE_FALSE(board.moveCurrentBrick(Direction::LEFT)); // Check that the brick cannot be translated to the left bc collision

    //check that the brick didn't move on the bordArea
    auto boardArea = board.getBoardArea();
    REQUIRE(boardArea[3][5].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[4][5].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[5][5].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[5][6].value() == TypeShape::L_SHAPE);

    //check the currentBrick's parameters, its board position isn't supposed to be changed
    REQUIRE(board.currentBrick.getBoardPosition() ==  Position(5,4));


    //MOVE RIGHT
    Brick brickRight(TypeShape::L_SHAPE, Orientation::UP, Position(3, 4));
    board.setCurrentBrick(brickRight);
    REQUIRE_FALSE(board.moveCurrentBrick(Direction::RIGHT)); // Check that the brick cannot be translated to the right bc collision

    //check that the brick didn't move on the bordArea
    boardArea = board.getBoardArea();
    REQUIRE(boardArea[3][3].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[4][3].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[5][3].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[5][4].value() == TypeShape::L_SHAPE);

    //check the currentBrick's parameters, its board position isn't supposed to be changed
    REQUIRE(board.currentBrick.getBoardPosition() ==  Position(3,4));


    //MOVE DOWN
    Brick brickDown(TypeShape::I_SHAPE, Orientation::UP, Position(4, 1));
    board.setCurrentBrick(brickDown);
    REQUIRE_FALSE(board.moveCurrentBrick(Direction::DOWN)); // Check that the brick cannot be translated down bc collision

    //check that the brick didn't move on the bordArea
    boardArea = board.getBoardArea();
    REQUIRE(boardArea[0][4].value() == TypeShape::I_SHAPE);
    REQUIRE(boardArea[1][4].value() == TypeShape::I_SHAPE);
    REQUIRE(boardArea[2][4].value() == TypeShape::I_SHAPE);
    REQUIRE(boardArea[3][4].value() == TypeShape::I_SHAPE);

    //check the currentBrick's parameters, its board position isn't supposed to be changed
    REQUIRE(board.currentBrick.getBoardPosition() ==  Position(4,1));

}



//ROTATE CURRENT BRICK OUT OF BOUNDS

TEST_CASE("Rotate current Brick out of left bound", "[board]") {
    Board board;
    Brick brick(TypeShape::L_SHAPE, Orientation::UP, Position(0, 1));
    board.setCurrentBrick(brick);

    // Check that the brick cannot be rotated bc out of bounds
    REQUIRE_FALSE(board.rotateCurrentBrick(Rotation::COUNTERCLOCKWISE));
    REQUIRE_FALSE(board.rotateCurrentBrick(Rotation::CLOCKWISE));


    //check that the brick didn't move on the bordArea
    auto boardArea = board.getBoardArea();
    REQUIRE(boardArea[0][0].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[1][0].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[2][0].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[2][1].value() == TypeShape::L_SHAPE);

    //check the currentBrick's parameters, its orientation isn't supposed to change
    REQUIRE(board.currentBrick.getOrientation() ==  Orientation::UP);

}


TEST_CASE("Rotate current Brick out of right bound", "[board]") {
    Board board;
    Brick brick(TypeShape::L_SHAPE, Orientation::DOWN, Position(9, 1));
    board.setCurrentBrick(brick);

    // Check that the brick cannot be rotated bc out of bounds
    REQUIRE_FALSE(board.rotateCurrentBrick(Rotation::COUNTERCLOCKWISE));
    REQUIRE_FALSE(board.rotateCurrentBrick(Rotation::CLOCKWISE));

    //check that the brick didn't move on the bordArea
    auto boardArea = board.getBoardArea();
    REQUIRE(boardArea[0][8].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[0][9].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[1][9].value() == TypeShape::L_SHAPE);
    REQUIRE(boardArea[2][9].value() == TypeShape::L_SHAPE);


    //check the currentBrick's parameters, its orientation isn't supposed to change
    REQUIRE(board.currentBrick.getOrientation() ==  Orientation::DOWN);

}





/*
TEST_CASE("Move current brick", "[board]") {
    // Création d'un plateau de jeu rempli et une brique courante
    Board board;
    for(int i = 0; i<2; i++){
        for(int j = 0; j<board.getBoardWidth()-1; ++j){
            board.getBoardArea()[board.getBoardHeight()-i-1][j] = TypeShape::I_SHAPE;
        }
    }

    Brick brick(TypeShape::L_SHAPE, Orientation::DOWN, Position(9, 19));
    board.setCurrentBrick(brick);

    REQUIRE(board.moveCurrentBrick(Direction::LEFT) == false); // Check if the brick can be translated to the left


    REQUIRE_FALSE(cell.has_value());
    auto boardArea = board.getBoardArea();

    Brick initialBrick(TypeShape::L_SHAPE, Orientation::UP, Position(5, 0)); // Placer la brique initialement en (5, 0)
    board.setCurrentBrick(initialBrick);

    SECTION("Move right") {
        REQUIRE(board.moveCurrentBrick(Direction::RIGHT) == true); // Déplacer la brique vers la droite
        // Vérifier si la brique a été déplacée correctement vers la droite sur le plateau
        auto boardArea = board.getBoardArea();
        REQUIRE(boardArea[0][5].value() == TypeShape::L_SHAPE);
        REQUIRE(boardArea[1][5].value() == TypeShape::L_SHAPE);
        REQUIRE(boardArea[1][6].value() == TypeShape::L_SHAPE);
        REQUIRE(boardArea[1][7].value() == TypeShape::L_SHAPE);
    }

    SECTION("Move left") {
        REQUIRE(board.moveCurrentBrick(Direction::LEFT) == true); // Déplacer la brique vers la gauche
        // Vérifier si la brique a été déplacée correctement vers la gauche sur le plateau
        auto boardArea = board.getBoardArea();
        REQUIRE(boardArea[0][3].value() == TypeShape::L_SHAPE);
        REQUIRE(boardArea[1][3].value() == TypeShape::L_SHAPE);
        REQUIRE(boardArea[1][4].value() == TypeShape::L_SHAPE);
        REQUIRE(boardArea[1][5].value() == TypeShape::L_SHAPE);
    }

    SECTION("Move down") {
        REQUIRE(board.moveCurrentBrick(Direction::DOWN) == true); // Déplacer la brique vers le bas
        // Vérifier si la brique a été déplacée correctement vers le bas sur le plateau
        auto boardArea = board.getBoardArea();
        REQUIRE(boardArea[1][5].value() == TypeShape::L_SHAPE);
        REQUIRE(boardArea[2][5].value() == TypeShape::L_SHAPE);
        REQUIRE(boardArea[2][6].value() == TypeShape::L_SHAPE);
        REQUIRE(boardArea[2][7].value() == TypeShape::L_SHAPE);
    }

}
*/

