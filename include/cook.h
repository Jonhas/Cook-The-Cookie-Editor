#ifndef COOK_H
#define COOK_H

typedef struct termios termios; 
void disable_raw_mode(); 
void enable_raw_mode(); 
void error(const char *c); 

#endif
