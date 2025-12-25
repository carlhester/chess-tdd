#include "main.h"
#include "test_assert.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int test_can_move_a_rook_vertically_multiple_spaces() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, ROOK, loc);

    Location targetloc = { 0, 7, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "rook can move x0 y7");
    return 0;
};

static int test_can_move_a_rook_horizontally_multiple_spaces() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, ROOK, loc);

    Location targetloc = { 5, 0, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "rook can move x5 y0");
    return 0;
};

static int test_cannot_move_a_rook_diagonally() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, ROOK, loc);

    Location targetloc = { 5, 5, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "rook cannot move diagonally 5x5");
    return 0;
};

static int test_rook_cannot_move_vertically_over_another_piece() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, ROOK, loc);

    Location blocker = { 0, 3, true };
    create_piece_at(&g, WHITE, PAWN, blocker);

    Location targetloc = { 0, 5, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "rook cannot move veritcally past another piece");
    return 0;
};

static int test_rook_cannot_move_horizontally_over_another_piece() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, ROOK, loc);

    Location blocker = { 3, 0, true };
    create_piece_at(&g, WHITE, PAWN, blocker);

    Location targetloc = { 5, 0, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "rook cannot move horizontally past another piece");
    return 0;
};

static int test_rook_movement() {
    test_can_move_a_rook_vertically_multiple_spaces();
    test_can_move_a_rook_horizontally_multiple_spaces();
    test_cannot_move_a_rook_diagonally();
    test_rook_cannot_move_vertically_over_another_piece();
    test_rook_cannot_move_horizontally_over_another_piece();
    return 0;
};
