// gameplay.c

#include <gbdk/platform.h>
#include <gb/gbdecompress.h>

#include <stdint.h>
#include <stdbool.h>
#include <rand.h>

#include "common.h"
#include "input.h"
#include "gfx_common.h"
#include "gameboy_color.h"

#include "board.h"

// Run once on startup to prepare gameplay board graphics
void splash_init_maps(void) {

    gb_decompress(intro_dialog_map, map_decomp_buf);
    set_bkg_based_tiles(0,31, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, map_decomp_buf, BG_TILES_INTRO_DIALOG_START);

    // Set up Board Letter map in VRAM
    // (direct addressable for rewriting letters via changing tile contents)
    board_map_fill();
    // set_bkg_based_tiles(BOARD_TILE_X_START, BOARD_TILE_Y_START,
    //                     BOARD_GRID_TILE_W, BOARD_GRID_TILE_H,
    //                     board_map,
    //                     BG_TILES_BOARD_LETTERS_START);

    board_redraw_clean();

    if (IS_CGB)
        splash_initgfx_cgb();

    print_gotoxy((DEVICE_SCREEN_WIDTH - 11u) / 2u,DEVICE_SCREEN_HEIGHT - 4u, PRINT_BKG);
    print_str("PRESS START");

    // TODO:
    // print_gotoxy(1u,DEVICE_SCREEN_HEIGHT - 2u, PRINT_BKG);
    // print_str("BBBBBR : ARPRUSS\nSTACKSMASHING\n");
}

#define CHR_NUM(c) (c - 'A')

// "GAMEBOY WORDYL";
const uint8_t splash_text[] = {
        CHR_NUM('G'),
        CHR_NUM('A'),
        CHR_NUM('M'),
        CHR_NUM('E'),
        CHR_NUM('B'),
        CHR_NUM('O'),
        CHR_NUM('Y'),
        BOARD_LETTERS_SPACE_CHAR,
        CHR_NUM('W'),
        CHR_NUM('O'),
        CHR_NUM('R'),
        CHR_NUM('D'),
        BOARD_LETTERS_SPACE_CHAR,
        BOARD_LETTERS_SPACE_CHAR,
        BOARD_LETTERS_SPACE_CHAR,
        CHR_NUM('Y'),
        CHR_NUM('L'),};

const uint8_t splash_text_color[] = {
    CGB_PAL_GREEN, // GAME
    CGB_PAL_GREEN,
    CGB_PAL_GREEN,
    CGB_PAL_GREEN,
    CGB_PAL_GREEN, // BOY
    CGB_PAL_GREEN,
    CGB_PAL_GREEN,

    CGB_PAL_WHITE, // SPACE

    CGB_PAL_BLUE, // WORD
    CGB_PAL_BLUE,
    CGB_PAL_BLUE,
    CGB_PAL_BLUE,

    CGB_PAL_WHITE, // SPACE
    CGB_PAL_WHITE, // SPACE
    CGB_PAL_WHITE, // SPACE

    CGB_PAL_BLUE,  // YL
    CGB_PAL_BLUE};


void splash_animate_title(void) {

    // memcpy(word, "GAME", sizeof("GAME"));
    // board_draw_word(0, word, BOARD_HIGHLIGHT_YES);
    // board_draw_word(0, "BOY", BOARD_HIGHLIGHT_YES);

    uint8_t row = 0;
    uint8_t col = 0;
    bool skip_anim = false;

    // BOARD_SET_FLIP_SPEED(BOARD_TILE_FLIP_FAST);
    BOARD_SET_FLIP_SPEED(BOARD_TILE_FLIP_SLOW);

    for (uint8_t c = 0; c < ARRAY_LEN(splash_text); c++) {

        // Allow user to slip through animation
        UPDATE_KEYS();
        if (KEY_PRESSED(J_ANY_KEY))
            skip_anim = true;

        // Don't show letter flip animation for space chars
        // and don't change their board tile color
        if (splash_text[c] != BOARD_LETTERS_SPACE_CHAR) {
            if (!skip_anim) board_draw_tile_flip_anim(row, col);
            SET_BOARD_COLOR_MATCHED;
        }
        else
            SET_BOARD_COLOR_NORMAL;

        if (IS_CGB)
            board_fill_letter_cgb_pal(row, col, splash_text_color[c]);

        board_draw_letter_bits(row, col, splash_text[c]);
        row++;
        if (row = BOARD_GRID_W) {
            row = 0;
            col++;
        }
    }

}
