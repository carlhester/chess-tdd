#include "game.h"
#include "test_assert.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int test_can_move_a_bishop_diagonally() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, BISHOP, loc);

    Location targetloc = { 4, 4, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "bishop can move diagonally");
    return 0;
};

static int test_cannot_move_a_bishop_vertically() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, BISHOP, loc);

    Location targetloc = { 5, 0, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "bishop cannot move vertically");
    return 0;
};

static int test_cannot_move_a_bishop_horizontally() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, BISHOP, loc);

    Location targetloc = { 0, 5, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "bishop cannot move horizontally");
    return 0;
};

static int test_bishop_cannot_move_diagonally_past_another_unit() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, BISHOP, loc);

    Location blocker = { 3, 3, true };
    create_piece_at(&g, WHITE, PAWN, blocker);

    Location targetloc = { 5, 5, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "bishop cannot move diagonally past another piece");
    return 0;
};

static int test_bishop_movement() {
    test_can_move_a_bishop_diagonally();
    test_cannot_move_a_bishop_vertically();
    test_cannot_move_a_bishop_horizontally();
    test_bishop_cannot_move_diagonally_past_another_unit();
    return 0;
};
