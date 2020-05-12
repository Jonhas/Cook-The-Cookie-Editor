#include <unistd.h>

#include "../include/output_functions.h"

void editor_draw_rows()
{
    for (int i = 0; i < 24; i++)
    {
        write(STDOUT_FILENO, "~\r\n", 3); 
    }
}

void editor_refresh_screen()
{
    write(STDOUT_FILENO, "\x1b[2j", 4);
    write(STDOUT_FILENO, "\x1b[H", 3); 
    
    editor_draw_rows(); 

    write(STDOUT_FILENO, "\x1b[H",3); 
}
