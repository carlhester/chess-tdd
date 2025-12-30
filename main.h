#pragma once
#include <stdbool.h>

#define MAX_UNITS 32
#define MAX_MOVES 100
#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8


typedef struct {
    int x;
    int y;
    bool valid;
} Location;

typedef enum {
    WHITE = 100,
    BLACK = 101
} UnitColor;

typedef enum {
    PAWN = 100,
    ROOK = 101,
    BISHOP = 102,
    KNIGHT = 103,
    KING = 104,
    QUEEN = 105
} UnitType;

typedef struct {
    UnitColor color;
    UnitType unittype;
    bool first_turn;
} Piece;

typedef struct {
    Piece *piece;
    Location location;
} Move;

typedef struct {
    Piece *board[BOARD_WIDTH][BOARD_HEIGHT];
    Piece pieces[MAX_UNITS];
    UnitColor active_player;
    Move moveQueue[100];
    int piece_count;
} Game;

int add(int, int);
Game create_game();
bool process_moves(Game *);
bool add_move_to_queue(Game *, Move);
Piece *get_piece_at(Game *, Location);
Piece *create_piece_at(Game *, UnitColor, UnitType, Location);
bool move_piece(Game *, Piece *, Location);
void get_location_for_piece(Game *, Piece *, Location *);
UnitColor get_active_player(Game *);
void create_standard_setup(Game *);
bool player_move(Game *, Location, Location);
