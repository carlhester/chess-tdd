#include "main.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// int unit_index = 0;

int add(int a, int b) {
    return a + b;
};

Game create_game() {
    Game g = { 0 };
    g.active_player = WHITE;
    return g;
};

Piece *get_piece_at(Game *g, Location loc) {
    return g->board[loc.x][loc.y];
};

void switch_active_player(Game *g) {
    if (g->active_player == WHITE) {
        g->active_player = BLACK;
        return;
    };

    g->active_player = WHITE;
};

Location get_location_for_piece(Game *g, Piece *p) {
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            if (g->board[x][y] == p) {
                Location found = { .x = x, .y = y, .valid = true };
                return found;
            };
        };
    };
    Location l = { .x = -1, .y = -1, .valid = false };
    return l;
};

Piece *create_piece_at(Game *g, UnitColor c, UnitType u, Location loc) {
    if (g->board[loc.x][loc.y] != NULL) {
        return NULL;
    }
    Piece *p = &g->pieces[g->piece_count];
    p->color = c;
    p->unittype = u;
    p->first_turn = true;
    g->piece_count++;

    g->board[loc.x][loc.y] = p;
    return p;

    return NULL;
};

bool is_first_turn(Piece *p) {
    if (p->first_turn == false) {
        return false;
    };
    return true;
};

bool is_valid_pawn_move(Piece *p, int sx, int sy, int dx, int dy) {
    if (abs(sx - dx) > 1) {
        return false;
    };

    int try_y = abs(sy - dy);
    if (try_y > 1) {
        if (try_y == 2) {
            if (is_first_turn(p) == false) {
                return false;
            };
        };
    };
    return true;
};

bool is_valid_knight_move(int sx, int sy, int dx, int dy) {
    int abs_x = abs(sx - dx);
    int abs_y = abs(sy - dy);

    if (abs_x > 2) {
        return false;
    };

    if (abs_y > 2) {
        return false;
    };

    // Make sure we're moving 1x2 (or 2x1)
    if (abs_y == 1) {
        if (abs_x != 2) {
            return false;
        };
    };

    // Make sure we're moving 2x1 (or 1x2)
    if (abs_y == 2) {
        if (abs_x != 1) {
            return false;
        };
    };

    return true;
};

bool is_valid_rook_move(int sx, int sy, int dx, int dy) {
    if (sx != dx) {
        if (sy != dy) {
            return false;
        };
    };

    return true;
};

bool is_valid_bishop_move(int sx, int sy, int dx, int dy) {
    int abs_x = abs(sx - dx);
    int abs_y = abs(sy - dy);

    if (abs_x > 0) {
        if (abs_y > 0) {
            return true;
        };
    };

    if (abs_y > 0) {
        if (abs_x > 0) {
            return true;
        };
    };

    return false;
};

bool is_valid_queen_move(int sx, int sy, int dx, int dy) {
    int abs_x = abs(sx - dx);
    int abs_y = abs(sy - dy);

    if (abs_x > 0) {
        if (abs_y > 0) {
            if (abs_x != abs_y) {
                return false;
            };
        };
    };

    return true;
};

bool is_valid_king_move(int sx, int sy, int dx, int dy) {
    int abs_x = abs(sx - dx);
    int abs_y = abs(sy - dy);

    if (abs_x > 1) {
        return false;
    }
    if (abs_y > 1) {
        return false;
    };

    return true;
};

bool target_is_on_board(Location dest) {
    if (dest.x >= BOARD_WIDTH || dest.x < 0) {
        return false;
    };

    if (dest.y >= BOARD_HEIGHT || dest.y < 0) {
        return false;
    };
    return true;
};

bool is_valid_move(Piece *p, Location src, Location target) {
    if (src.x == target.x) {
        if (src.y == target.y) {
            return false;
        };
    };

    if (!target_is_on_board(target)) {
        return false;
    }

    if (p->unittype == PAWN) {
        bool v = is_valid_pawn_move(p, src.x, src.y, target.x, target.y);
        if (v != true) {
            return false;
        };
    };

    if (p->unittype == KNIGHT) {
        bool v = is_valid_knight_move(src.x, src.y, target.x, target.y);
        if (v != true) {
            return false;
        };
    };

    if (p->unittype == ROOK) {
        bool v = is_valid_rook_move(src.x, src.y, target.x, target.y);
        if (v != true) {
            return false;
        };
    };

    if (p->unittype == BISHOP) {
        bool v = is_valid_bishop_move(src.x, src.y, target.x, target.y);
        if (v != true) {
            return false;
        };
    };

    if (p->unittype == QUEEN) {
        bool v = is_valid_queen_move(src.x, src.y, target.x, target.y);
        if (v != true) {
            return false;
        };
    };

    if (p->unittype == KING) {
        bool v = is_valid_king_move(src.x, src.y, target.x, target.y);
        if (v != true) {
            return false;
        };
    };

    return true;
};

bool move_piece(Game *g, Piece *p, Location target) {
    Location src = get_location_for_piece(g, p);
    if (src.valid == false) {
        return false;
    };
    UnitColor current_player_color = get_active_player(g);

    if (p->color != current_player_color) {
        return false;
    };

    bool valid_move = is_valid_move(p, src, target);
    if (!valid_move) {
        return false;
    };

    // Piece *target_piece = g->board[target.x][target.y];
    Piece *target_piece = g->board[target.x][target.y];
    if (target_piece != NULL) {
        if (target_piece->color == current_player_color) {
            return false;
        };
    };

    if (p->first_turn == true) {
        p->first_turn = false;
    };

    g->board[src.x][src.y] = NULL;
    g->board[target.x][target.y] = p;
    switch_active_player(g);

    return true;
};

UnitColor get_active_player(Game *g) {
    return g->active_player;
};

void create_standard_setup(Game *g) {
    // WHITE SECOND (PAWN) ROW
    for (int x = 0; x < BOARD_WIDTH; x++) {
        Location w1loc = { x, 1, true };
        create_piece_at(g, WHITE, PAWN, w1loc);
    };

    // WHITE FIRST ROW
    Location p0loc = { 0, 0, true };
    create_piece_at(g, WHITE, ROOK, p0loc);
    Location p1loc = { 1, 0, true };
    create_piece_at(g, WHITE, KNIGHT, p1loc);
    Location p2loc = { 2, 0, true };
    create_piece_at(g, WHITE, BISHOP, p2loc);
    Location p3loc = { 3, 0, true };
    create_piece_at(g, WHITE, QUEEN, p3loc);
    Location p4loc = { 4, 0, true };
    create_piece_at(g, WHITE, KING, p4loc);
    Location p5loc = { 5, 0, true };
    create_piece_at(g, WHITE, BISHOP, p5loc);
    Location p6loc = { 6, 0, true };
    create_piece_at(g, WHITE, KNIGHT, p6loc);
    Location p7loc = { 7, 0, true };
    create_piece_at(g, WHITE, ROOK, p7loc);

    // BLACK SECOND (PAWN) ROW
    for (int x = 0; x < BOARD_WIDTH; x++) {
        Location w1loc = { x, 6, true };
        create_piece_at(g, BLACK, PAWN, w1loc);
    };

    // BLACK FIRST ROW
    Location p0loc_b = { 0, 0, true };
    create_piece_at(g, BLACK, ROOK, p0loc_b);
    Location p1loc_b = { 1, 0, true };
    create_piece_at(g, BLACK, KNIGHT, p1loc_b);
    Location p2loc_b = { 2, 0, true };
    create_piece_at(g, BLACK, BISHOP, p2loc_b);
    Location p3loc_b = { 3, 0, true };
    create_piece_at(g, BLACK, QUEEN, p3loc_b);
    Location p4loc_b = { 4, 0, true };
    create_piece_at(g, BLACK, KING, p4loc_b);
    Location p5loc_b = { 5, 0, true };
    create_piece_at(g, BLACK, BISHOP, p5loc_b);
    Location p6loc_b = { 6, 0, true };
    create_piece_at(g, BLACK, KNIGHT, p6loc_b);
    Location p7loc_b = { 7, 0, true };
    create_piece_at(g, BLACK, ROOK, p7loc_b);
};

bool player_move(Game *g, Location start, Location end) {
    Piece *p = get_piece_at(g, start);
    return move_piece(g, p, end);
};

// int main() {
//     Game g = create_game();
//     create_standard_board(&g);
//     print_pieces(&g);
// };
