#include "keyboard.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/mem.h"

//The input buffer
__volatile__ char inputBuffer[MAX_INPUT_BUFFER];

//The index of the next index to insert a key 
__volatile__ char inputBufferIndex = 0;

static void keyboard_callback(registers_t regs) {

    //Read the scan code
    u8 scancode = read_port_byte(0x60);

    //Add the key to the buffer if not an up event
    if(scancode < 0x80)
        addKeyToBuffer(scancode);

}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}

void addKeyToBuffer(u8 scancode){

    //Check if enough space is available in the buffer
    if(inputBufferIndex>=MAX_INPUT_BUFFER)
        return;

    //Add it to the buffer
    inputBuffer[inputBufferIndex] = sc_ascii[(int)scancode];
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