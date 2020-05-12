#ifndef TERMINAL_FUNCTIONS_H
#define TERMINAL_FUNCTIONS_H

void error(const char *c);
void disable_raw_mode(); 
void enable_raw_mode(); 
char editor_read_key(); 
int get_window_size(int *rows, int *columns); 

#endif 
