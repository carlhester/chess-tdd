#include "main.h"
#include "test_assert.h"
#include "test_bishop.h"
#include "test_king.h"
#include "test_knight.h"
#include "test_pawn.h"
#include "test_queen.h"
#include "test_rook.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tests_run = 0;
int tests_passed = 0;

static int test_add() {
    int result = add(2, 6);
    ASSERT(result == 8, "2+6 = 8");
    return 0;
}

static int test_create_game() {
    create_game();
    return 0;
};

static int test_new_game_has_no_pieces() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *p = get_piece_at(&g, loc);
    ASSERT(p == NULL, "new game board is empty");
    return 0;
};

static int test_can_add_a_piece() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *created = create_piece_at(&g, WHITE, PAWN, loc);

    Piece *p = get_piece_at(&g, loc);

    ASSERT(p == created, "Putting a piece should result in a piece being put");
    return 0;
};

static int test_can_add_a_WHITE_PAWN_to_0_0() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *created = create_piece_at(&g, WHITE, PAWN, loc);
    Piece *got = get_piece_at(&g, loc);

    ASSERT(pieces_match(created, got), "Expected White PAWN");
    return 0;
};

static int test_can_add_a_row_of_white_pawns() {
    Game g = create_game();
    Location loc0 = { 0, 0, true };
    Location loc1 = { 1, 0, true };
    Location loc2 = { 2, 0, true };
    Location loc3 = { 3, 0, true };
    Location loc4 = { 4, 0, true };
    Location loc5 = { 5, 0, true };
    Location loc6 = { 6, 0, true };
    Location loc7 = { 7, 0, true };

    create_piece_at(&g, WHITE, PAWN, loc0);
    create_piece_at(&g, WHITE, PAWN, loc1);
    create_piece_at(&g, WHITE, PAWN, loc2);
    create_piece_at(&g, WHITE, PAWN, loc3);
    create_piece_at(&g, WHITE, PAWN, loc4);
    create_piece_at(&g, WHITE, PAWN, loc5);
    create_piece_at(&g, WHITE, PAWN, loc6);
    create_piece_at(&g, WHITE, PAWN, loc7);

    Piece *got0 = get_piece_at(&g, loc5);
    ASSERT(got0->unittype = PAWN, "Expected White PAWN");
    Piece *got1 = get_piece_at(&g, loc5);
    ASSERT(got1->unittype = PAWN, "Expected White PAWN");
    Piece *got2 = get_piece_at(&g, loc5);
    ASSERT(got2->unittype = PAWN, "Expected White PAWN");
    Piece *got3 = get_piece_at(&g, loc5);
    ASSERT(got3->unittype = PAWN, "Expected White PAWN");
    Piece *got4 = get_piece_at(&g, loc5);
    ASSERT(got4->unittype = PAWN, "Expected White PAWN");
    Piece *got5 = get_piece_at(&g, loc5);
    ASSERT(got5->unittype = PAWN, "Expected White PAWN");
    Piece *got6 = get_piece_at(&g, loc5);
    ASSERT(got6->unittype = PAWN, "Expected White PAWN");
    Piece *got7 = get_piece_at(&g, loc5);
    ASSERT(got7->unittype = PAWN, "Expected White PAWN");
    return 0;
};

static int test_can_add_a_WHITE_KNIGHT_to_1_0() {
    UnitColor c = WHITE;
    UnitType t = KNIGHT;

    Game g = create_game();
    Location loc = { 0, 1, true };
    create_piece_at(&g, WHITE, KNIGHT, loc);

    Piece *got = get_piece_at(&g, loc);
    Piece expected = { .color = c, .unittype = t };
    ASSERT(pieces_match(got, &expected), "Expected White PAWN");
    return 0;
};

static int test_can_add_a_BLACK_PAWN_to_0_0() {
    UnitColor c = BLACK;
    UnitType t = PAWN;

    Game g = create_game();
    Location loc = { 0, 0, true };
    create_piece_at(&g, BLACK, PAWN, loc);

    Piece *got = get_piece_at(&g, loc);
    Piece expected = { .color = c, .unittype = t };
    ASSERT(pieces_match(got, &expected), "Expected BLACK PAWN");
    return 0;
};

static int test_can_add_a_BLACK_QUEEN_to_5_0() {
    UnitColor c = BLACK;
    UnitType t = QUEEN;

    Game g = create_game();
    Location loc = { 5, 0, true };
    create_piece_at(&g, BLACK, QUEEN, loc);

    Piece *got = get_piece_at(&g, loc);
    Piece expected = { .color = c, .unittype = t };
    ASSERT(pieces_match(got, &expected), "Expected BLACK QUEEN");
    return 0;
};

static int test_cannot_create_a_piece_where_one_already_exists() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    create_piece_at(&g, WHITE, PAWN, loc);
    Piece *a = create_piece_at(&g, WHITE, ROOK, loc);
    ASSERT(a == NULL, "cannot create a piece on top of another one");
    return 0;
};

static int test_can_populate_board_standard_setup() {
    Game g = create_game();
    create_standard_setup(&g);

    for (int x = 0; x < BOARD_WIDTH; x++) {
        Location loc = { x, 1, true };
        Piece *p = get_piece_at(&g, loc);
        ASSERT(p != NULL, "Expected a piece at x,1");
    }

    for (int x = 0; x < BOARD_WIDTH; x++) {
        Location loc = { x, 0, true };
        Piece *p = get_piece_at(&g, loc);
        ASSERT(p != NULL, "Expected a piece at x,0");
    }

    for (int x = 0; x < BOARD_WIDTH; x++) {
        Location loc = { x, 6, true };
        Piece *p = get_piece_at(&g, loc);
        ASSERT(p != NULL, "Expected a piece at x,6");
    }

    for (int x = 0; x < BOARD_WIDTH; x++) {
        Location loc = { x, 6, true };
        Piece *p = get_piece_at(&g, loc);
        ASSERT(p != NULL, "Expected a piece at x,7");
    }
    return 0;
};

static int test_cannot_move_a_piece_on_top_of_the_same_color() {
    Game g = create_game();
    Location loc1 = { 0, 0, true };
    create_piece_at(&g, WHITE, QUEEN, loc1);

    Location loc2 = { 1, 1, true };
    Piece *a = create_piece_at(&g, WHITE, QUEEN, loc2);

    bool success = move_piece(&g, a, loc1);

    ASSERT(success == false, "cannot move a piece on top of same color");
    return 0;
};

static int test_can_move_a_piece_on_top_of_the_other_color() {
    Game g = create_game();
    Location loc1 = { 0, 0, true };
    create_piece_at(&g, BLACK, QUEEN, loc1);

    Location loc2 = { 1, 1, true };
    Piece *a = create_piece_at(&g, WHITE, QUEEN, loc2);

    bool success = move_piece(&g, a, loc1);
    ASSERT(success == true, "can move a piece on top of other color");
    return 0;
};

static int test_after_moving_piece_is_no_longer_at_old_location() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, PAWN, loc);

    Location targetloc = { 0, 1, true };
    move_piece(&g, a, targetloc);
    Piece *got = get_piece_at(&g, loc);

    ASSERT(got == NULL, "Expected no piece to be at 0,0");
    return 0;
};

static int test_a_piece_cannot_move_to_the_same_place_it_started() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, PAWN, loc);

    Location targetloc = { 0, 0, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "cannot move to the same place it started");

    return 0;
};

static int test_white_cannot_move_black_piece() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, BLACK, QUEEN, loc);
    Location targetloc = { 0, 1, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "whites turn, cannot move black piece");
    return 0;
};

static int test_black_cannot_move_white_piece() {
    Game g = create_game();
    Location w_loc = { 0, 0, true };
    Piece *w = create_piece_at(&g, WHITE, QUEEN, w_loc);
    Location w_targetloc = { 0, 1, true };
    move_piece(&g, w, w_targetloc);

    Location b_loc = { 5, 5, true };
    Piece *b = create_piece_at(&g, WHITE, QUEEN, b_loc);
    Location b_targetloc = { 6, 6, true };

    bool success = move_piece(&g, b, b_targetloc);

    ASSERT(success == false, "blacks turn, cannot move black piece");
    return 0;
};

static int test_white_can_move_white_piece() {
    // start of game is whites turn
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, QUEEN, loc);
    Location targetloc = { 0, 1, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == true, "whites turn, can move white piece");
    return 0;
};

static int test_black_can_move_black_piece() {
    // start of game is whites turn
    Game g = create_game();
    // Whites turn
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, QUEEN, loc);
    Location targetloc = { 0, 1, true };
    move_piece(&g, a, targetloc);

    // black turn
    Location b_loc = { 0, 0, true };
    Piece *b = create_piece_at(&g, BLACK, QUEEN, b_loc);
    Location b_targetloc = { 0, 1, true };
    bool success = move_piece(&g, b, b_targetloc);
    ASSERT(success == true, "black turn, can move black piece");
    return 0;
};

static int test_player_move() {
    Game g = create_game();
    create_standard_setup(&g);

    Location start = { 1, 1, true };
    Location end = { 1, 2, true };

    bool success = player_move(&g, start, end);
    ASSERT(success == true, "expected player to make legitimate move");

    Piece *r = get_piece_at(&g, end);
    ASSERT(r->unittype == PAWN, "expected this piece to be a pawn");

    Piece *s = get_piece_at(&g, start);
    ASSERT(s == NULL, "expected this location to be empty");

    return 0;
};

static int test_cannot_move_a_piece_outside_of_board_width() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, PAWN, loc);

    Location targetloc = { BOARD_WIDTH + 1, 0, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "Should not success when moving outside boundaries");
    return 0;
};

static int test_cannot_move_a_piece_outside_of_board_width_less_than_zero() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, PAWN, loc);

    Location targetloc = { -1, 0, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "Should not success when moving outside boundaries");
    return 0;
};

static int test_cannot_move_a_piece_outside_of_board_height() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, PAWN, loc);

    Location targetloc = { 0, BOARD_HEIGHT + 1, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "Should not success when moving outside boundaries");
    return 0;
};

static int test_cannot_move_a_piece_outside_of_board_height_less_than_zero() {
    Game g = create_game();
    Location loc = { 0, 0, true };
    Piece *a = create_piece_at(&g, WHITE, PAWN, loc);

    Location targetloc = { 0, -1, true };
    bool success = move_piece(&g, a, targetloc);
    ASSERT(success == false, "Should not success when moving outside boundaries");
    return 0;
};

// ====== RULE CHECKS =====
static int test_white_player_goes_first() {
    Game g = create_game();
    UnitColor c = get_active_player(&g);

    ASSERT(c == WHITE, "white player goes first");
    return 0;
};

static int test_black_turn_is_after_white_turn() {
    Game g = create_game();
    Location loc = { 0, 0, true };

    Piece *a = create_piece_at(&g, WHITE, QUEEN, loc);
    Location targetloc = { 1, 1, true };
    move_piece(&g, a, targetloc);

    UnitColor c = get_active_player(&g);
    ASSERT(c == BLACK, "after white turn is black turn");

    return 0;
};

static int test_white_turn_after_black_turn() {
    Game g = create_game();
    Location wloc = { 0, 0, true };
    Piece *w = create_piece_at(&g, WHITE, QUEEN, wloc);

    Location bloc = { 7, 7, true };
    Piece *b = create_piece_at(&g, BLACK, QUEEN, bloc);

    Location w_targetloc = { 1, 1, true };
    move_piece(&g, w, w_targetloc);

    Location b_targetloc = { 6, 6, true };
    move_piece(&g, b, b_targetloc);

    UnitColor c = get_active_player(&g);

    ASSERT(c == WHITE, "after black turn is white turn");

    return 0;
};

static int test_attacking_other_color_captures_piece() {
    Game g = create_game();
    Location wloc = { 0, 0, true };
    Piece *w = create_piece_at(&g, WHITE, QUEEN, wloc);

    Location bloc = { 1, 1, true };
    create_piece_at(&g, BLACK, QUEEN, bloc);

    move_piece(&g, w, bloc);

    Piece *result = get_piece_at(&g, bloc);
    ASSERT(result == w, "the result should be the white piece at location bloc");
    return 0;
};

static int test_game_can_add_a_move_to_queue() {
    Game g = create_game();
    Location start = { 0, 0, true };
    Location end = { 6, 6, true };
    Piece *w = create_piece_at(&g, WHITE, QUEEN, start);

    Move m = { .piece = w, .location = end };

    bool res = add_move_to_queue(&g, m);
    ASSERT(res = true, "Can add a move to queue");
    return 0;
};

static int test_game_can_process_moves_queue() {
    Game g = create_game();
    Location start = { 0, 0, true };
    Location end = { 6, 6, true };
    Piece *w = create_piece_at(&g, WHITE, QUEEN, start);
    Move m = { .piece = w, .location = end };

    add_move_to_queue(&g, m);
    process_moves(&g);
    Piece *res = get_piece_at(&g, end);
    ASSERT(res != NULL, "got piece was null");
    ASSERT(res->unittype = QUEEN, "expected a queen to be at this location");
    return 0;
};

static int test_game_can_process_multiple_moves_from_queue() {
    Game g = create_game();
    Location w_start = { 0, 0, true };
    Piece *w = create_piece_at(&g, WHITE, QUEEN, w_start);

    Location w_move1 = { 1, 0, true };
    Move w_m1 = { .piece = w, .location = w_move1 };

    Location w_move2 = { 1, 1, true };
    Move w_m2 = { .piece = w, .location = w_move2 };

    Location b_start = { 7, 7, true };
    Piece *b = create_piece_at(&g, BLACK, QUEEN, b_start);

    Location b_move1 = { 7, 6, true };
    Move b_m1 = { .piece = b, .location = b_move1 };

    Location b_move2 = { 7, 5, true };
    Move b_m2 = { .piece = b, .location = b_move2 };

    add_move_to_queue(&g, w_m1);
    add_move_to_queue(&g, b_m1);
    add_move_to_queue(&g, w_m2);
    add_move_to_queue(&g, b_m2);
    process_moves(&g);

    Piece *p = get_piece_at(&g, b_move2);
    ASSERT(p != NULL, "p should be populated");
    ASSERT(p->color == BLACK, "Expected black piece here");

    return 0;
};

// Run all tests
static void run_all_tests() {
    printf("Running tests...\n");
    printf("================\n\n");
    // ===== CONTROL TEST =====
    test_add();

    // ===== GAME INITIALIZATION =====
    test_create_game();
    test_new_game_has_no_pieces();

    // ===== POPULATE BOARD =====
    test_can_add_a_piece();
    test_can_add_a_WHITE_PAWN_to_0_0();
    test_can_add_a_WHITE_KNIGHT_to_1_0();
    test_can_add_a_row_of_white_pawns();
    test_can_add_a_BLACK_PAWN_to_0_0();
    test_can_add_a_BLACK_QUEEN_to_5_0();
    test_cannot_create_a_piece_where_one_already_exists();
    test_can_populate_board_standard_setup();

    // ===== MOVEMENT =====
    test_cannot_move_a_piece_on_top_of_the_same_color();
    test_can_move_a_piece_on_top_of_the_other_color();
    test_after_moving_piece_is_no_longer_at_old_location();
    test_a_piece_cannot_move_to_the_same_place_it_started();
    test_white_cannot_move_black_piece();
    test_black_cannot_move_white_piece();
    test_white_can_move_white_piece();
    test_black_can_move_black_piece();
    test_player_move();
    test_cannot_move_a_piece_outside_of_board_width();
    test_cannot_move_a_piece_outside_of_board_width_less_than_zero();
    test_cannot_move_a_piece_outside_of_board_height();
    test_cannot_move_a_piece_outside_of_board_height_less_than_zero();

    // ==== UNIT SPECIFIC MOVEMENT =====
    test_pawn_movement();
    test_knight_movement();
    test_rook_movement();
    test_bishop_movement();
    test_queen_movement();
    test_king_movement();

    // ====== RULE CHECKS =====
    test_white_player_goes_first();
    test_black_turn_is_after_white_turn();
    test_white_turn_after_black_turn();
    test_attacking_other_color_captures_piece();

    // ===== GAMEPLAY =====
    test_game_can_add_a_move_to_queue();
    test_game_can_process_moves_queue();
    test_game_can_process_multiple_moves_from_queue();

    printf("\n================\n");
    printf("Tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);

    if (tests_run == tests_passed) {
        printf("\nAll tests passed!\n");
    }
}

int main() {
    run_all_tests();
    return (tests_run == tests_passed) ? 0 : 1;
}
