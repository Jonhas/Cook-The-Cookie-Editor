#ifndef COOK_H
#define COOK_H

#include <termios.h>

typedef struct termios termios;
typedef struct editor_config editor_config; 

struct editor_config{
    termios orig_terminal;     
}; 

editor_config editor; 

#endif
