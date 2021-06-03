#include "timer.h"
#include "../drivers/screen.h"
#include "../drivers/ports.h"
#include "isr.h"

u8 tick = 0;

static void timer_callback(registers_t regs) {
    tick++;

    if(tick >= 20){
        pprint("Tick");
        pprint("\n\r");
        tick = 0;
    }
}

void init_timer(u32 freq) {

    //Check arguments
    if(freq == 0){
        pprint("Error: The frequency cannot be 0");
        return;
    }

    //Install the callback as the ISR for IRQ0
    register_interrupt_handler(IRQ0, timer_callback);
    
    //Get the correct divisor value
    u16 startValue = 0; 
    if(freq <= 18){
         startValue = HARDWARE_TIMER_FREQUENCY/freq;
    }
   

    //Split the divisor
    u8 low  = (u8)(startValue & 0xFF);
    u8 high = (u8)((startValue >> 8) & 0xFF);

    
    write_port_byte(0x43, 0x36); //Set the timer : Timer Channel0, Acces mode in low/high style, square wave generator, 16-bits binary 
    
    //Send the reload value
    write_port_byte(0x40, low);
    for(u32 i = 0;i<1000;i++) __asm__ __volatile__("nop");
    write_port_byte(0x40, high);
}