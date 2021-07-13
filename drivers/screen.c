#include "screen.h"
#include "ports.h"
#include "../libc/mem.h"

enum ColorPallette currentColor = WHITE_ON_BLACK;

void setCursorAt(int x,int y){
    
    //Check if the position is valid
    if(x < 0 || x >= COLS_COUNT)
        return;
    
    if(y < 0 || y >= ROWS_COUNT)
        return;
    
    int offset = y * COLS_COUNT +  x;
    
    //High byte
    write_port_byte(REG_SCREEN_CTRL, 14);
    write_port_byte(REG_SCREEN_DATA, (unsigned char)(offset >> 8));

    //Low byte
    write_port_byte(REG_SCREEN_CTRL, 15);
    write_port_byte(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));

}

void setCursorOffset(int offset){

    //Check if the offset is valid
    if(offset < 0 || offset >= COLS_COUNT * ROWS_COUNT)
        return;
    
     //High byte
    write_port_byte(REG_SCREEN_CTRL, 14);
    write_port_byte(REG_SCREEN_DATA, (unsigned char)(offset >> 8));

    //Low byte
    write_port_byte(REG_SCREEN_CTRL, 15);
    write_port_byte(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));

}


int getCursorOffset() {

    //High byte
    write_port_byte(REG_SCREEN_CTRL, 14);
    int offset = read_port_byte(REG_SCREEN_DATA) << 8;

    //Low byte
    write_port_byte(REG_SCREEN_CTRL, 15);
    offset += read_port_byte(REG_SCREEN_DATA);

    return offset;
}

void clearLastLine(){

    //Init the print at the right position
    int offset = getCursorOffset();
    char* vga_memory = (char *) (VGA_ADDRESS + (((offset/COLS_COUNT) * COLS_COUNT) * 2));

    for(int i = 0;i<COLS_COUNT*2;i+=2){
        vga_memory[i] = ' ';
        vga_memory[i+1] = WHITE_ON_BLACK;
    }


}

void scrollUp(){
    
    //Move the fb up
    memcpy((char*)(VGA_ADDRESS), (char *)(VGA_ADDRESS+COLS_COUNT*2), COLS_COUNT*ROWS_COUNT*2 - COLS_COUNT*2);

    //Clear the last line
    char *vga_memory = (char*)(VGA_ADDRESS + (COLS_COUNT*ROWS_COUNT*2 - COLS_COUNT*2));
    for(int i = 0;i<COLS_COUNT;i++){
        *(vga_memory++) = ' ';
        *(vga_memory++) = WHITE_ON_BLACK;
    }
    
}

void pprintChar(char c){

    //Init the print at the right position
    int offset = getCursorOffset();
    char* vga_memory = (char *) VGA_ADDRESS;

        
    //Set the pointer to the rigth address
    vga_memory = (char *) (VGA_ADDRESS + (offset*2));

    //If the next char is CR
    if(c == '\r'){

        //Put offset at the beginning of the line
        offset = (int) (offset/COLS_COUNT) * COLS_COUNT;  

    }else if(c == '\n'){ //If the next char is LF

        if(offset + COLS_COUNT >= COLS_COUNT*ROWS_COUNT)
            scrollUp();
        else
            offset += COLS_COUNT;

    }else{ //If it's a normal char

        *(vga_memory) = c;
        *(vga_memory+1) = currentColor;

        if(offset + 1 >= COLS_COUNT*ROWS_COUNT){
            scrollUp();
                offset = (int) (offset/COLS_COUNT) * COLS_COUNT;  
        }else{
            offset++;
        }       
        
    }       
      
    //Set cursor position
    setCursorOffset(offset);

}

void pprint(const char *buf){

    //Init the print at the right position
    int offset = getCursorOffset();
    char* vga_memory =  (char *) VGA_ADDRESS;

    //Print the buffer
    while(*buf){
        
        //Set the pointer to the rigth address
        vga_memory = (char *) (VGA_ADDRESS + (offset*2));

        //If the next char is CR
        if(*buf == '\r'){

            //Put offset at the beginning of the line
            offset = (int) (offset/COLS_COUNT) * COLS_COUNT;  

        }else if(*buf == '\n'){ //If the next char is LF

            if(offset + COLS_COUNT >= COLS_COUNT*ROWS_COUNT)
                scrollUp();
            else
                offset += COLS_COUNT;

        }else{ //If it's a normal char

            *(vga_memory) = *buf;
            *(vga_memory+1) = currentColor;

            if(offset + 1 >= COLS_COUNT*ROWS_COUNT){
                scrollUp();
                 offset = (int) (offset/COLS_COUNT) * COLS_COUNT;  
            }else{
                offset++;
            }
                
            
        }       

        buf++;
    }    

    //Set cursor position
    setCursorOffset(offset);
    
}

void clearScreen(){

    char *vga_mem = (char *) VGA_ADDRESS;
    for(int i = 0;i<COLS_COUNT*ROWS_COUNT;i++){
        *(vga_mem++) = ' ';
        *(vga_mem++) = WHITE_ON_BLACK;
    }

    setCursorAt(0,0);

}

void changeCurrentColor(enum ColorPallette c){
    currentColor = c;
}