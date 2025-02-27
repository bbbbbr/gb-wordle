// input.c

#include <gbdk/platform.h>
#include <stdbool.h>

#include "input.h"
#include "common.h"

#if (defined(MEGADUCK))
    #include "megaduck_laptop/megaduck_keyboard.h"
#endif

uint8_t keys = 0x00;
uint8_t previous_keys = 0x00;
uint8_t keys_ticked;
// uint8_t keys_changed = 0x00;
uint8_t key_repeat_count = 0x00;


// Reduce CPU usage by only checking once per frame
// Allows a loop control to be passed in
void waitpadreleased_lowcpu(uint8_t button_mask) {

    #if defined(MEGADUCK)
        do {
            UPDATE_KEYS();
            vsync();

            // Poll for keyboard keys every other frame
            // (Polling intervals below 20ms may cause keyboard lockup)
            if ((sys_time & 0x01u) && (megaduck_laptop_detected)) {
                if (megaduck_keyboard_poll_keys()) {
                    megaduck_keyboard_process_keys();

                    if ((!megaduck_key_pressed) &&
                        (!KEY_PRESSED(button_mask))) break;
                }
            }
        } while (KEY_PRESSED(button_mask));
    #else
        while (joypad() & button_mask) {
            vsync();
        }
    #endif

    UPDATE_KEYS_TICKED();
    UPDATE_KEYS();
}

// Reduce CPU usage by only checking once per frame
// Allows a loop control to be passed in
void waitpadticked_lowcpu(uint8_t button_mask) {

    bool keyboard_checked = false;
    uint8_t megaduck_key_pressed_last = 0u;

    while (1) {

        vsync(); // yield CPU
        UPDATE_KEYS();
        if (KEY_TICKED(button_mask)) {

            // Store key(s) ticked to exist this menu
            // in case they need to be retrieved
            UPDATE_KEYS_TICKED();

            // Prevent passing through any key ticked
            // event that may have just happened
            UPDATE_KEYS();

            return;
        }

        #if defined(MEGADUCK)
            // Poll for keyboard keys every other frame
            // (Polling intervals below 20ms may cause keyboard lockup)
            if ((sys_time & 0x01u) && (megaduck_laptop_detected)) {

                if (megaduck_keyboard_poll_keys()) {
                    megaduck_keyboard_process_keys();

                    // Prevent passing through any key press by flagging the press
                    // and then returning once no keys are pressed
                    if (keyboard_checked) {
                        if ((megaduck_key_pressed) && (!megaduck_key_pressed_last))
                            return;
                    }
`
                    // Only register a non-pressed key if key repeat is not active)
                    // (otherwise the gaps between repeated keys might look like non-keypresses
                    if (!(megaduck_key_flags & KEY_FLAG_KEY_REPEAT)) {
                        keyboard_checked = true;
                        megaduck_key_pressed_last = megaduck_key_pressed;
                    }
                }
            }
        #endif
    };
}
