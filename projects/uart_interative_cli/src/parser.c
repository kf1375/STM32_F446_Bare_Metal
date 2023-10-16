#include "parser.h"
#include "uart.h"

Command commandList[] = {
    {"set", 2, set_callback},
    {"get", 1, get_callback},
    {"write", 5, write_callback},
    // Add more commands here
};

void process_command(char* command)
{
    char* tokens[6]; // Assuming a maximum of 6 tokens (command + 5 arguments)
    uint16_t numTokens = 0;

    // Tokenize the command using a space as the separator
    char* token = strtok(command, " ");
    while (token != NULL && numTokens < 6) {
        tokens[numTokens] = token;
        token = strtok(NULL, " ");
        numTokens++;
    }

    // Find the command in the commandList
    for (uint16_t i = 0; i < sizeof(commandList) / sizeof(Command); i++) {
        if (strcmp(tokens[0], commandList[i].command) == 0) {
            // Check if the number of arguments matches the expected number
            if (numTokens - 1 == commandList[i].numArgs) {
                // Call the command callback function with arguments
                commandList[i].callback(tokens + 1, numTokens - 1);
                return;
            } else {
                // Handle argument count mismatch
                UART_Transmit_String("Argument count mismatch.\r\n");
                return;
            }
        }
    }

    // Command not found, send an error response
    UART_Transmit_String("Command not recognized.\r\n");
}

void set_callback(char** args, uint8_t numArgs)
{
    char response[128];
    snprintf(response, sizeof(response), "Setting %s to %s\r\n", args[0], args[1]);
    UART_Transmit_String(response);
}
void get_callback(char** args, uint8_t numArgs)
{
    char response[128];
    snprintf(response, sizeof(response), "Getting %s value\r\n", args[0]);
    UART_Transmit_String(response);
}

void write_callback(char** args, uint8_t numArgs)
{
    char response[128];
    snprintf(response, sizeof(response), "Writing values: %s, %s, %s, %s, %s\r\n", args[0], args[1], args[2], args[3], args[4]);
    UART_Transmit_String(response);
}