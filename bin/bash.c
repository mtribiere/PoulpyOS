#include "bash.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../libc/mem.h"
#include "../cpu/types.h"
#include "../libc/string.h"

void printCLI(const char *cmd){

    //Clear the current line
    clearLastLine();

    //Print the command
    changeCurrentColor(MAGENTA);
    pprint("\r$>");
    changeCurrentColor(WHITE);
    pprint(cmd);
}

void computeChar(char *cmd, char toInsert, uint8_t *runCommandFlag){

    //If this is an error
    if(toInsert == '\0' || toInsert == 0x01)
        return;

    //If this is a backapce
    if(toInsert == '\b'){

        //If the cmd is already empty
        if(strlen(cmd) <= 0) return;

        //Remove the last char
        *(cmd+strlen(cmd)-1) = '\0';

    }else if(toInsert == '\r'){ //If this is enter 
        
        *runCommandFlag = 1;
        
    }else{//Add the char to the string

        cmd[strlen(cmd)] = (uint8_t) toInsert;
    }

    //Print the new line
    printCLI(cmd);
}

void printTree(){

    //Top
    int star = 1;
    for(int i = 0;i<15;i++){
        changeCurrentColor(i%2 ? WHITE : MAGENTA);
        for(int j = 15-i;j>0;j--){
            pprint(" ");
        }
        for(int j = 0;j<star;j++){
            pprint("*");
        }
        star += 2;
        pprint("\r\n");
    }

    //Bottom
    for(int i = 0;i<3;i++){

        for(int j = 0;j<14;j++)
            pprintChar(' ');
        for(int j = 0;j<3;j++)
            pprintChar('*');

        pprint("\r\n");
        
    }

}

void printLyricText(char *text){

    //While lyrics are not over
    while(*text){

        //Set the correct color
        if(*text == 'A')
            changeCurrentColor(YELLOW);
        else
            changeCurrentColor(WHITE);

        //Print a line
        while((*text) != '\n'){
            pprintChar(*text);
            text++;
        }

        pprintChar(*(text++));
        
        //Wait for enter input
        char c = 0;
        while(c != '\r')
            getKey(&c);

    }
}

void runCommand(char *cmd){

    pprint("\r\n");

    if(strlen(cmd) == 0)
        return;

    if(strcmp(cmd,"hello"))    
        pprint("Welcome to Poulpy-OS !!\r\n");

    else if(strcmp(cmd,"tree")){
        printTree();

    }else if(strcmp(cmd,"Johnny")){
        printLyricText(lyrics);

    }else if(strcmp(cmd,"help")){
        pprint("Supported command : \r\n - tree \r\n - hello \r\n - Johnny \r\n - help \r\n");

    }else{
        pprint("No such command\r\n");
    }
}

void bash(){

   
    while (1)
    {   
        //Init
        char cmd[MAX_COMMAND_SIZE];
        memset(cmd,0,MAX_COMMAND_SIZE);
        
        char c = 0;
        uint8_t runCommandFlag = 0;

        //Print the shell
        printCLI(cmd);
        
        while(!runCommandFlag){

            //Wait for the next char
            while(getKey(&c) == -1);

            //Compute the next char
            computeChar(cmd,c,&runCommandFlag);
        }

        runCommand(cmd);

    }
    

}