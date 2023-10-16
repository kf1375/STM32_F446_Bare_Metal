#ifndef __PARSER_H
#define __PARSER_H

#include <string.h>

#include "main.h"

#define MAX_INPUT_SIZE 128
#define MAX_ARGUMENTS 5

typedef struct {
    const char* command;
    uint16_t numArgs;
    void (*callback)(char** args, uint16_t numArgs);
} Command;

// Command callback functions
void set_callback(char** args, uint8_t numArgs);
void get_callback(char** args, uint8_t numArgs);
void write_callback(char** args, uint8_t numArgs);
// Add more command callback functions here

void process_command(char* command);

#endif