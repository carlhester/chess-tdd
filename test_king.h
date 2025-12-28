#include "main.h"
#include "test_assert.h"
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

static int test_king_cannot_move_into_rook_check() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KING, loc);

    Location rookloc = { 1, 5, true };
    create_piece_at(&g, BLACK, ROOK, rookloc);

    Location targetloc = { 1, 0, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "king cannot into check by a rook");

    return 0;
};

static int test_king_cannot_move_into_bishop_check() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KING, loc);

    Location rookloc = { 5, 5, true };
    create_piece_at(&g, BLACK, BISHOP, rookloc);

    Location targetloc = { 1, 1, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "king cannot into check by a bishop");

    return 0;
};
static int test_king_cannot_move_into_queen_check() {

    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KING, loc);

    Location rookloc = { 5, 5, true };
    create_piece_at(&g, BLACK, QUEEN, rookloc);

    Location targetloc = { 1, 1, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "king cannot into check by a queen");

    return 0;
};

static int test_king_cannot_move_into_pawn_check() {

    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KING, loc);

    Location rookloc = { 2, 2, true };
    create_piece_at(&g, BLACK, PAWN, rookloc);

    Location targetloc = { 1, 1, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "king cannot into check by a pawn");

    return 0;
};

static int test_king_cannot_move_into_knight_check() {

    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KING, loc);

    Location rookloc = { 2, 3, true };
    create_piece_at(&g, BLACK, KNIGHT, rookloc);

    Location targetloc = { 1, 1, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "king cannot into check by a knight");

    return 0;
};

// TODO
// static int test_king_cannot_move_into_king_check() {
//
//     Game g = create_game();
//     Location loc = { 0, 0, true };
//     Piece *a = create_piece_at(&g, WHITE, KING, loc);
//
//     Location rookloc = { 2, 2, true };
//     create_piece_at(&g, BLACK, KING, rookloc);
//
//     Location targetloc = { 1, 1, true };
//     bool success = move_piece(&g, a, targetloc);
//     ASSERT(success == false, "king cannot into check by a king");
//
//     return 0;
// };
static int test_king_movement() {
    test_can_move_a_king_by_one_vertically();
    test_can_move_a_king_by_one_horizontally();
    test_can_move_a_king_diagonally();
    test_cannot_move_a_king_more_than_1_space_horizontally();
    test_cannot_move_a_king_more_than_1_space_vertically();
    test_cannot_move_a_king_more_than_1_space_diagonally();
    test_king_cannot_move_into_rook_check();
    test_king_cannot_move_into_bishop_check();
    test_king_cannot_move_into_queen_check();
    test_king_cannot_move_into_pawn_check();
    test_king_cannot_move_into_knight_check();
    // TODO
    // test_king_cannot_move_into_king_check();
    return 0;
};
