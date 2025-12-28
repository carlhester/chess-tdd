#include "main.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// int unit_index = 0;

int add(int a, int b) {
    return a + b;
};

void empty_pieces(Game *g) {
    for (int i = 0; i < MAX_UNITS; i++) {
        Piece p = { 0 };
        g->pieces[i] = p;
    };
};

Game create_game() {
    Game g = { 0 };
    empty_pieces(&g);
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

void get_location_for_piece(Game *g, Piece *p, Location *l) {
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            if (g->board[x][y] == p) {
                l->x = x;
                l->y = y;
                l->valid = true;
                return;
            };
        };
    };

    l->x = -1;
    l->y = -1;
    l->valid = false;
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

bool is_valid_pawn_move(Game *g, Piece *p, int sx, int sy, int dx, int dy) {
    if (abs(sx - dx) > 1) {
        return false;
    };

    // Attacking
    if (abs(sx - dx) == 1) {
        if (abs(sy - dy) == 1) {
            Location l = { dx, dy, true };
            Piece *b = get_piece_at(g, l);
            if (b) {
                if (p->color != b->color) {
                    return true;
                };
            };
        };
    };

    int try_y = abs(sy - dy);
    if (try_y >= 1) {
        Location l = { dx, dy, true };
        Piece *b = get_piece_at(g, l);
        // If another piece is at the destination, don't move there
        if (b) {
            return false;
        };
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

bool is_valid_king_move(Game *g, int sx, int sy, int dx, int dy) {
    int abs_x = abs(sx - dx);
    int abs_y = abs(sy - dy);

    if (abs_x > 1) {
        return false;
    }
    if (abs_y > 1) {
        return false;
    };

    for (int i = 0; i < MAX_UNITS; i++) {
        Piece *p = &g->pieces[i];

        if (p->color != get_active_player(g)) {
            if (p->unittype == ROOK) {
                Location l = { 0 };
                get_location_for_piece(g, p, &l);
                if (is_valid_rook_move(l.x, l.y, dx, dy)) {
                    return false;
                }
            }
            if (p->unittype == BISHOP) {
                Location l = { 0 };
                get_location_for_piece(g, p, &l);
                if (is_valid_bishop_move(l.x, l.y, dx, dy)) {
                    return false;
                }
            }
            if (p->unittype == QUEEN) {
                Location l = { 0 };
                get_location_for_piece(g, p, &l);
                if (is_valid_queen_move(l.x, l.y, dx, dy)) {
                    return false;
                }
            }
            if (p->unittype == PAWN) {
                Location l = { 0 };
                get_location_for_piece(g, p, &l);
                if (is_valid_pawn_move(g, p, l.x, l.y, dx, dy)) {
                    return false;
                }
            }
            if (p->unittype == KNIGHT) {
                Location l = { 0 };
                get_location_for_piece(g, p, &l);
                if (is_valid_knight_move(l.x, l.y, dx, dy)) {
                    return false;
                }
            }
        }
    }

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

bool is_sliding_vertically_valid(Game *g, Location src, Location dest) {
    if (src.y > dest.y) {
        for (int i = src.y - 1; i > dest.y + 1; i--) {
            Location l = { src.x, i, true };
            Piece *b = get_piece_at(g, l);
            if (b) {
                return false;
            }
        }
    }

    if (src.y < dest.y) {
        for (int i = src.y + 1; i < dest.y - 1; i++) {
            Location l = { src.x, i, true };
            Piece *b = get_piece_at(g, l);
            if (b) {
                return false;
            }
        }
    }

    return true;
};

bool is_sliding_horizontally_valid(Game *g, Location src, Location dest) {
    if (src.x > dest.x) {
        for (int i = src.x - 1; i > dest.x + 1; i--) {
            Location l = { i, src.y, true };
            Piece *b = get_piece_at(g, l);
            if (b) {
                return false;
            }
        }
    }

    if (src.x < dest.x) {
        for (int i = src.x + 1; i < dest.x - 1; i++) {
            Location l = { i, src.y, true };
            Piece *b = get_piece_at(g, l);
            if (b) {
                return false;
            }
        }
    }

    return true;
};

bool is_sliding_diagonally_valid(Game *g, Location src, Location dest) {
    if (src.x > dest.x) {
        if (src.y > dest.y) {
            for (int i = src.x - 1; i > dest.x + 1; i--) {
                for (int ii = src.y - 1; ii > dest.y + 1; ii--) {
                    Location l = { i, ii, true };
                    Piece *b = get_piece_at(g, l);
                    if (b) {
                        return false;
                    }
                }
            }
        }
    }

    if (src.x > dest.x) {
        if (src.y < dest.y) {
            for (int i = src.x - 1; i > dest.x + 1; i--) {
                for (int ii = src.y + 1; ii < dest.y - 1; ii++) {
                    Location l = { i, ii, true };
                    Piece *b = get_piece_at(g, l);
                    if (b) {
                        return false;
                    }
                }
            }
        }
    }

    if (src.x < dest.x) {
        if (src.y < dest.y) {
            for (int i = src.x + 1; i < dest.x - 1; i++) {
                for (int ii = src.y + 1; ii < dest.y - 1; ii++) {
                    Location l = { i, ii, true };
                    Piece *b = get_piece_at(g, l);
                    if (b) {
                        return false;
                    }
                }
            }
        }
    }

    if (src.x > dest.x) {
        if (src.y > dest.y) {
            for (int i = src.x - 1; i > dest.x + 1; i--) {
                for (int ii = src.y - 1; ii > dest.y + 1; ii--) {
                    Location l = { i, ii, true };
                    Piece *b = get_piece_at(g, l);
                    if (b) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
};

bool is_sliding_valid(Game *g, Location src, Location dest) {
    if (src.x == dest.x) {
        return is_sliding_vertically_valid(g, src, dest);
    };

    if (src.y == dest.y) {
        return is_sliding_horizontally_valid(g, src, dest);
    };

    return is_sliding_diagonally_valid(g, src, dest);
};

bool is_valid_move(Game *g, Piece *p, Location src, Location dest) {
    if (src.x == dest.x) {
        if (src.y == dest.y) {
            return false;
        };
    };

    if (!target_is_on_board(dest)) {
        return false;
    }

    if (p->unittype == PAWN) {
        bool v = is_valid_pawn_move(g, p, src.x, src.y, dest.x, dest.y);
        if (v != true) {
            return false;
        };
    };

    if (p->unittype == KNIGHT) {
        bool v = is_valid_knight_move(src.x, src.y, dest.x, dest.y);
        if (v != true) {
            return false;
        };
    };

    if (p->unittype == ROOK) {
        bool v = is_valid_rook_move(src.x, src.y, dest.x, dest.y);
        if (!v) {
            return false;
        };

        bool s = is_sliding_vertically_valid(g, src, dest);
        if (!s) {
            return false;
        };

        bool h = is_sliding_horizontally_valid(g, src, dest);
        if (!h) {
            return false;
        };

        return true;
    };

    if (p->unittype == BISHOP) {
        bool v = is_valid_bishop_move(src.x, src.y, dest.x, dest.y);
        if (v != true) {
            return false;
        };
        bool s = is_sliding_diagonally_valid(g, src, dest);
        if (!s) {
            return false;
        };
    };

    if (p->unittype == QUEEN) {
        bool v = is_valid_queen_move(src.x, src.y, dest.x, dest.y);
        if (v != true) {
            return false;
        };
        bool s = is_sliding_valid(g, src, dest);
        if (!s) {
            return false;
        };
    };

    if (p->unittype == KING) {
        bool v = is_valid_king_move(g, src.x, src.y, dest.x, dest.y);
        if (v != true) {
            return false;
        };
    };

    return true;
};

bool move_piece(Game *g, Piece *p, Location target) {
    Location src = { 0 };
    get_location_for_piece(g, p, &src);
    if (src.valid == false) {
        return false;
    };

    UnitColor current_player_color = get_active_player(g);
    if (p->color != current_player_color) {
        return false;
    };

    bool valid_move = is_valid_move(g, p, src, target);
    if (!valid_move) {
        return false;
    };

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
