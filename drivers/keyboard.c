#include "keyboard.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/mem.h"

//The input buffer
__volatile__ unsigned char inputBuffer[MAX_INPUT_BUFFER];

//The index of the next index to insert a key 
__volatile__ char inputBufferIndex = 0;

//Current keyboard state 
/***
* Bit 2 : Is cap locked
***/
__volatile__ u8 keyBoardState = 0x00;

const char *currentKeyboard = sc_ascii_lower;

static void keyboard_callback(registers_t regs) {

    //Read the scan code
    u8 scancode = read_port_byte(0x60);

    //Add the key to the buffer if not an up event
    if(scancode > 0x80)
       return;

    //If Caps lock
    if(scancode == 0x3A){
        
        //Flip the keyboard state
        keyBoardState ^= 0x04;

        //Set keyboard state
        write_port_byte(0x60,keyBoardState);
        write_port_byte(0x64,0xED);

        //Set keymap
        currentKeyboard = (keyBoardState & 0x04) ? sc_ascii : sc_ascii_lower;
        

    }else{
        addKeyToBuffer(scancode);
    }
    

}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}

void addKeyToBuffer(u8 scancode){

    //Check if enough space is available in the buffer
    if(inputBufferIndex>=MAX_INPUT_BUFFER)
        return;

    //Add it to the buffer
    inputBuffer[inputBufferIndex] = (unsigned char) currentKeyboard[(int)scancode];
    inputBufferIndex++;

}

s8 getKey(char *c){

    //If no key if the buffer
    if(inputBufferIndex <= 0)
        return -1;


    //Put the char in ptr
    *c = inputBuffer[0];

    //Slide all char to the left
    memcpy((char *)inputBuffer,(char *)(inputBuffer+1),inputBufferIndex-1);
    inputBufferIndex--;


    return 0;
}