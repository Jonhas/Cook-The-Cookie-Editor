#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include "../include/input_functions.h"
#include "../include/cook.h"

/*
 * A function designed to call for an error. Once the error is raised, 
 * we will output to stdout the error message and then exit. 
 */
void error(const char *c)
{
    write(STDOUT_FILENO, "\x1b[2J", 4); 
    write(STDOUT_FILENO, "\x1b[H", 3); 

    perror(c); 
    exit(1); 
}

/*
 * A method to restore the terminal's original abilities before the execution 
 * of the program. 
 */ 
void disable_raw_mode()
{
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &editor.orig_terminal)==-1)
        error("tcsetattr failed, cannot establish canonical mode"); 
}

/*
 * A method to get rid of canonical mode of the terminal, and instead, goto
 * raw mode. 
 */
void enable_raw_mode()
{
    if(tcgetattr(STDIN_FILENO, &editor.orig_terminal)==-1)
        error("tcgetattr failed, cannot disable canonical mode");
    
    atexit(disable_raw_mode);
    
    termios raw = editor.orig_terminal; 

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON); 
    raw.c_oflag &= ~(OPOST); 
    raw.c_cflag *= ~(CS8); 
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN| ISIG); 
    raw.c_cc[VMIN]=0; 
    raw.c_cc[VTIME]=1;
    
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw)==-1)
        error("tcsetattr failed, cannot apply modifications to termios"); 
}

/*
 * Waiting for a single key press, and then returning it. 
 */
char editor_read_key()
{
    char c;
    int read_status = 0; 
    while(( read_status==read(STDIN_FILENO, &c, 1) )!=1)
    {
        if(read_status == -1 && errno != EAGAIN)
            error("read failed"); 
    }
    return c; 
}
