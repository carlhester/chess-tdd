#include "main.h"
#include "test_assert.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int test_can_move_a_queen_vertically() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, QUEEN, loc);

    Location targetloc = { 0, 5, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "queen can move vertically");
    return 0;
};

static int test_can_move_a_queen_horizontally() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, QUEEN, loc);

    Location targetloc = { 5, 0, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "queen can move horizontally");
    return 0;
};

static int test_can_move_a_queen_diagonally() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, QUEEN, loc);

    Location targetloc = { 4, 4, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "queen can move diagonally");
    return 0;
};

static int test_cannot_move_a_queen_2x4() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, QUEEN, loc);

    Location targetloc = { 2, 4, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "queen cannot move 2x4");

    return 0;
};

static int test_cannot_move_a_queen_4x6() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, QUEEN, loc);

    Location targetloc = { 4, 6, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "queen cannot move 4x6");

    return 0;
};

static int test_queen_movement() {
    test_can_move_a_queen_vertically();
    test_can_move_a_queen_horizontally();
    test_can_move_a_queen_diagonally();
    test_cannot_move_a_queen_2x4();
    test_cannot_move_a_queen_4x6();
    return 0;
};
