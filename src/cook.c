#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include "../include/cook.h"

termios orig_terminal;

/*
 * A method to restore the terminal's original abilities 
 * before the execution of the program. 
 */
void disable_raw_mode()
{
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH,&orig_terminal)==-1)
        error("tcsetattr failed, cannot enable canonical mode"); 
}

void error(const char *c)
{
    perror(c); 
    exit(1); 
}

/*
 * A method to get rid of canonical mode of the terminal, and instead,
 * goto raw mode. Now, whatever is type, will not be echoed. 
 */
void enable_raw_mode()
{
    if(tcgetattr(STDIN_FILENO, &orig_terminal)==-1)
        error("tcgetattr failed, cannot disable canonical mode"); 
    
    atexit(disable_raw_mode); 
    
    termios raw = orig_terminal; 
    
    //FOllowing are used to turn off certain input flags. Such as turning off 
    //IXON to disable Ctrl-S and Ctrl-Q. We can also read in Ctrl+M through 
    //turning off ICRNL flag.This is done by negating the bits of the flag, 
    //thus,disabling it. 
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); 
    
    //Following are used to turn off certain output flags. We can turn off all output 
    //processing through disabling OPOST
    raw.c_oflag &= ~(OPOST); 
    
    raw.c_cflag &= ~(CS8); 

    //The following are disabling modes through the use of local mode flags 
    //Echo mode used to turn off the echo ability, and ICANON allows us to read byte by byte 
    //instead of line by line. Additionally, ICANON turns off canonical mode
    //We also turn off ISIG, to disable Ctrl-C and Ctrl-Z. We can also disable 
    //Ctrl-V through IEXTEN
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN]=0;
    raw.c_cc[VTIME]=1; 

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw)==-1)
        error("tcsetattr failed, cannot apply modifications to termios"); 
}


int main(int argc, char** argv)
{
    enable_raw_mode(); 
    while(1)
    {
        char character_to_be_read = '\0';
        if(read(STDIN_FILENO, &character_to_be_read, 1)==-1 && errno != EAGAIN)
            error("reading from stdin buffer failed"); 
        if(iscntrl(character_to_be_read))
            printf("%d\n", character_to_be_read); 
        else
            printf("%d ('%c')\r\n", character_to_be_read, character_to_be_read);

        if(character_to_be_read=='q') break; 
    }

    return 0; 
}
