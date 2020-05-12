#include "../include/cook.h"
#include "../include/input_functions.h"
#include "../include/terminal_functions.h"
#include "../include/output_functions.h"
#include "../include/init_functions.h"

int main()
{
    enable_raw_mode(); 
    init_editor(); 

    while(1)
    {
        editor_refresh_screen();     
        editor_process_keypress(); 
    }
    return 0; 
}
