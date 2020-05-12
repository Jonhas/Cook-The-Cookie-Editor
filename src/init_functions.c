#include <sys/ioctl.h>

#include "../include/init_functions.h"
#include "../include/cook.h"
#include "../include/terminal_functions.h"

void init_editor()
{
    if (get_window_size(&editor.screen_rows, &editor.screen_columns)==-1)
        error("Get window size of the terminal failed. Terminating...");
}
