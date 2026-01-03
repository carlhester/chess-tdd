#include "game.h"

int main() {
    Game g = create_game();
    create_standard_setup(&g);

    // Move white pawn
    Location l = { 1, 1, true };
    Piece *p = get_piece_at(&g, l);
    Location l2 = { 1, 2, true };
    move_piece(&g, p, l2);


    // Move black pawn
    Location lb1 = { 4, 6, true };
    Piece *b = get_piece_at(&g, lb1);
    Location lb2 = { 4, 4, true };
    move_piece(&g, b, lb2);

    draw(&g);
};
