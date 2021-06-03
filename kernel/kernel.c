#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../bin/bash.h"

void fake_entrypoint() {
}

//Kernel entry point
void poulpy() {

    isr_install();
    
    clearScreen();

    changeCurrentColor(MAGENTA);
    pprint("===========================\r\n");
    pprint("=== Welcome to PoulpyOS ===\r\n");
    pprint("===========================\r\n");
    changeCurrentColor(WHITE);

    init_keyboard();
    bash();    
    
    /*
    int star = 1;
    for(int i = 0;i<15;i++){
        for(int j = 15-i;j>0;j--){
            pprint(" ");
        }
        for(int j = 0;j<star;j++){
            pprint("*");
        }
        star += 2;
        pprint("\r\n");
    }*/

    
   
   
}