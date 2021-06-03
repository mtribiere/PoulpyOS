#pragma once

#include "../cpu/types.h"

#define MAX_INPUT_BUFFER 10

//Static definition of keybinding
const static char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '\b', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '\r', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

const static char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
"7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
"R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
"A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
"LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
"/", "RShift", "Keypad *", "LAlt", "Spacebar"};

//Add a scan code to the internal keybuffer
void addKeyToBuffer(u8 scancode);

//Read the last unread key for buffer (Destructive)
//Return 0 if the read was successful or -1
s8 getKey(char *c);

void init_keyboard();