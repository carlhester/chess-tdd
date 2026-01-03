#include "game.h"
#include "test_assert.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int test_can_move_a_pawn_forward_two_squares_on_first_turn() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, PAWN, loc);
    Location targetloc = { 0, 2, true };
    int success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "Expected piece to land at 0,2");
    return 0;
};

static int test_can_move_a_pawn_forward_one_square() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, PAWN, loc);
    Location targetloc = { 0, 1, true };
    move_piece(&g, a, targetloc);
    Piece *got = get_piece_at(&g, targetloc);
    ASSERT(pieces_match(a, got), "Expected piece to be at 0,1");
    return 0;
};

static int test_can_move_a_pawn_backward_one_square() {
    Game g = create_game();
    Location loc = { 0, 1, true };
    Piece *a = create_piece_at(&g, WHITE, PAWN, loc);
    Location targetloc = { 0, 0, true };
    move_piece(&g, a, targetloc);

    Piece *got = get_piece_at(&g, targetloc);
    ASSERT(pieces_match(a, got), "Expected piece to be at 0,0 after moving from 0,1");
    return 0;
};

static int test_cannot_move_a_pawn_forward_two_squares_after_first_turn() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, PAWN, loc);
    Location first_move_loc = { 0, 1, true };
    move_piece(&g, a, first_move_loc);
    Location second_move_loc = { 0, 3, true };

    int success = move_piece(&g, a, second_move_loc);

    ASSERT(success == false, "A pawn moving 2 squares after first move is not allowed");
    return 0;
};

static int test_cannot_move_a_pawn_horizontally_two_squares() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, PAWN, loc);
    Location targetloc = { 2, 0, true };
    int success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "Expected piece to remain at 0,0");
    return 0;
};

static int test_pawn_cannot_attack_forward() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, PAWN, loc);
    Location targetloc = { 0, 1, true };
    create_piece_at(&g, BLACK, PAWN, targetloc);

    int success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "Pawn cannot attack forward");
    return 0;
};

static int test_pawn_can_attack_diagonally() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, PAWN, loc);

    Location targetloc = { 1, 1, true };
    create_piece_at(&g, BLACK, PAWN, targetloc);

    int success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "Pawn can attack diagonally");
    return 0;
};

static int test_pawn_movement() {
    test_can_move_a_pawn_forward_one_square();
    test_can_move_a_pawn_backward_one_square();
    test_can_move_a_pawn_forward_two_squares_on_first_turn();
    test_cannot_move_a_pawn_forward_two_squares_after_first_turn();
    test_cannot_move_a_pawn_horizontally_two_squares();
    test_pawn_cannot_attack_forward();
    test_pawn_can_attack_diagonally();
    return 0;
};
