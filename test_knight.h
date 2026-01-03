#include "game.h"
#include "test_assert.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int test_can_move_a_knight_forward_two_and_right_one() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KNIGHT, loc);

    Location targetloc = { 1, 2, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "should be able to move a knight forward two and right one");
    return 0;
};

static int test_can_move_a_knight_forward_one_and_right_two() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KNIGHT, loc);

    Location targetloc = { 2, 1, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "should be able to move a knight forward one and right two");
    return 0;
};

static int test_can_move_a_knight_forward_two_and_left_one() {
    Game g = create_game();
    Location loc = { 2, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KNIGHT, loc);

    Location targetloc = { 1, 2, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "should be able to move a knight forward two and left one");
    return 0;
};

static int test_can_move_a_knight_forward_one_and_left_two() {
    Game g = create_game();
    Location loc = { 2, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KNIGHT, loc);

    Location targetloc = { 0, 1, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "should be able to move a knight forward one and left two");
    return 0;
};

static int test_can_move_a_knight_backward_one_and_right_one() {
    Game g = create_game();
    Location loc = { 0, 2, true };
    Piece *a = create_piece_at(&g, WHITE, KNIGHT, loc);

    Location targetloc = { 1, 0, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "should be able to move a knight -2x1");
    return 0;
};

static int test_can_move_a_knight_backward_two_and_left_one() {
    Game g = create_game();
    Location loc = { 1, 2, true };
    Piece *a = create_piece_at(&g, WHITE, KNIGHT, loc);

    Location targetloc = { 0, 0, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "should be able to move a knight -2x-1");
    return 0;
};

static int test_can_move_a_knight_backward_one_and_right_two() {
    Game g = create_game();
    Location loc = { 0, 1, true };
    Piece *a = create_piece_at(&g, WHITE, KNIGHT, loc);

    Location targetloc = { 2, 0, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "should be able to move a knight -1x2");
    return 0;
};

static int test_can_move_a_knight_backward_one_and_left_two() {
    Game g = create_game();
    Location loc = { 2, 2, true };
    Piece *a = create_piece_at(&g, WHITE, KNIGHT, loc);

    Location targetloc = { 0, 1, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "should be able to move a knight x-2 y-1");
    return 0;
};

static int test_cannot_move_a_knight_more_than_two_vertically() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KNIGHT, loc);

    Location targetloc = { 0, 3, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "knight should not be able to move 3 forward");
    return 0;
};

static int test_cannot_move_a_knight_more_than_two_horizontally() {
    Game g = create_game();
    Location loc = { 3, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KNIGHT, loc);

    Location targetloc = { 0, 0, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "knight should not be able to move 3 left");
    return 0;
};

static int test_cannot_move_a_knight_two_vert_and_two_horizontally() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KNIGHT, loc);

    Location targetloc = { 2, 2, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "knight cannot move 2x2");
    return 0;
};

static int test_knight_can_jump_over_pieces() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, KNIGHT, loc);

    Location loc2 = { 0, 1, true };
    create_piece_at(&g, WHITE, PAWN, loc2);

    Location targetloc = { 1, 2, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "knight can jump over a piece");
    return 0;
};

static int test_knight_movement() {
    test_can_move_a_knight_forward_two_and_right_one();
    test_can_move_a_knight_forward_two_and_left_one();
    test_can_move_a_knight_forward_one_and_right_two();
    test_can_move_a_knight_forward_one_and_left_two();
    test_can_move_a_knight_backward_one_and_right_one();
    test_can_move_a_knight_backward_two_and_left_one();
    test_can_move_a_knight_backward_one_and_right_two();
    test_can_move_a_knight_backward_one_and_left_two();
    test_cannot_move_a_knight_more_than_two_vertically();
    test_cannot_move_a_knight_more_than_two_horizontally();
    test_cannot_move_a_knight_two_vert_and_two_horizontally();
    test_knight_can_jump_over_pieces();
    return 0;
};
