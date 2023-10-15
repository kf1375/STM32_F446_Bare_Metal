#ifndef __LOGGER_H
#define __LOGGER_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "main.h"

#define LOG_MAX_ENTRIES 5
#define LOG_LEVELS 4
#define LOG_MSG_MAX_LENGTH 128

#define LOG_OUTPUT_LENGHT 256

// Log levels
typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL_ERROR
} LogLevel;

// Log level tags
static const char* LogLevelTags[] = {
    "INFO",
    "WARNING",
    "ERROR",
    "CRITICAL"
};

// Log structure
typedef struct {
    uint32_t timestamp;    // Timestamp in milliseconds
    LogLevel level;        // Log level
    uint32_t logID;        // Log ID
    char message[LOG_MSG_MAX_LENGTH];  // Log message
} LogEntry;

void logger(LogLevel level, uint32_t logID, const char *message);

#endif /* __LOGGER_H */