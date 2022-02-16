// input.h

#ifndef INPUT_H
#define INPUT_H

#define J_ANY_KEY           0xFFu
#define J_WAIT_ALL_RELEASED 0xFFu
#define J_WAIT_ANY_PRESSED  0x00u

#define UPDATE_KEYS() previous_keys = keys; keys = joypad(); keys_changed = (keys ^ previous_keys)
#define UPDATE_KEY_REPEAT(MASK) if (MASK & previous_keys & keys) { key_repeat_count++; } else { key_repeat_count=0; }
#define RESET_KEY_REPEAT(NEWVAL) key_repeat_count = NEWVAL

#define KEY_PRESSED(MASK)  (keys & (MASK))
#define KEY_TICKED(MASK)   ((keys & (MASK)) && !(previous_keys & (MASK)))
#define KEY_RELEASED(MASK) (!(keys & (MASK)) && (previous_keys & (MASK)))
//#define KEY_TICKED(MASK)   (keys & keys_changed & (MASK))
//#define KEY_RELEASED(MASK) (~keys & keys_changed & (MASK))


#define ANY_KEY_PRESSED (keys)

void waitpadticked_lowcpu(uint8_t button_mask, volatile uint8_t * loop_control);

extern uint8_t keys;
extern uint8_t previous_keys;
extern uint8_t keys_changed;
extern uint8_t key_repeat_count;

#endif // INPUT_H


