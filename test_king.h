#include "main.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int test_can_move_a_king_by_one_vertically() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KING, loc);

    Location targetloc = { 0, 1, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "king can move vertically");
    return 0;
};

static int test_can_move_a_king_by_one_horizontally() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KING, loc);

    Location targetloc = { 1, 0, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "king can move horizontally");
    return 0;
};

static int test_can_move_a_king_diagonally() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, QUEEN, loc);

    Location targetloc = { 1, 1, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "king can move diagonally");
    return 0;
};

static int test_cannot_move_a_king_more_than_1_space_horizontally() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KING, loc);

    Location targetloc = { 2, 0, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "king cannot move >1 horizontally");

    return 0;
};

static int test_cannot_move_a_king_more_than_1_space_vertically() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KING, loc);

    Location targetloc = { 0, 3, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "king cannot move >1 vertically");

    return 0;
};

static int test_cannot_move_a_king_more_than_1_space_diagonally() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KING, loc);

    Location targetloc = { 3, 3, true };

    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "king cannot move >1 diagonally");

    return 0;
};

static int test_king_movement() {
    test_can_move_a_king_by_one_vertically();
    test_can_move_a_king_by_one_horizontally();
    test_can_move_a_king_diagonally();
    test_cannot_move_a_king_more_than_1_space_horizontally();
    test_cannot_move_a_king_more_than_1_space_vertically();
    test_cannot_move_a_king_more_than_1_space_diagonally();
    return 0;
};
