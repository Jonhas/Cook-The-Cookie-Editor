#include <stdlib.h>
#include <unistd.h>
#include "../include/input_functions.h"
#include "../include/terminal_functions.h"

/*
 * Used to process a single key press. The read key function is called
 * within the function to assure the keypress is read. 
 */
void editor_process_keypress(){
    char read_char = editor_read_key(); 
    switch(read_char)
    {
        case CTRL_KEY('x'):
            {
                write(STDOUT_FILENO, "\x1b[2J", 4); 
                write(STDOUT_FILENO, "\x1b[H", 3); 

               exit(0); 
               break; 
            }
    }
}
