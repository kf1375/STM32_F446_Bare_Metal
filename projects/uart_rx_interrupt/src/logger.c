#include "logger.h"
#include "uart.h"

extern LogEntry infoLogBuffer[LOG_MAX_ENTRIES];
extern LogEntry warningLogBuffer[LOG_MAX_ENTRIES];
extern LogEntry errorLogBuffer[LOG_MAX_ENTRIES];
extern LogEntry criticalLogBuffer[LOG_MAX_ENTRIES];

extern uint8_t infoLogIndex;
extern uint8_t warningLogIndex;
extern uint8_t errorLogIndex;
extern uint8_t criticalLogIndex;

extern char logOutput[LOG_OUTPUT_LENGHT];

void logger(LogLevel level, uint32_t logID, const char *message) {
    LogEntry entry;
    memset(&logOutput, '\0', LOG_OUTPUT_LENGHT);

    entry.timestamp = 0; // Replace with your timestamp logic
    entry.level = level;
    entry.logID = logID;
    strncpy(entry.message, message, sizeof(entry.message));

    // Determine which log buffer to use
    LogEntry *logBuffer;
    uint8_t *logIndex;
    if (level == LOG_INFO) {
        logBuffer = infoLogBuffer;
        logIndex = &infoLogIndex;
    } else if (level == LOG_WARNING) {
        logBuffer = warningLogBuffer;
        logIndex = &warningLogIndex;
    } else if (level == LOG_ERROR) {
        logBuffer = errorLogBuffer;
        logIndex = &errorLogIndex;
    } else if (level == LOG_CRITICAL_ERROR) {
        logBuffer = criticalLogBuffer;
        logIndex = &criticalLogIndex;
    }

    // Store the log entry in the circular buffer
    logBuffer[*logIndex] = entry;
    sprintf(logOutput, "Timestamp: %lu | Log Level: %s | Log ID: %lu | Message: %s\n",
                        entry.timestamp, LogLevelTags[entry.level], entry.logID, entry.message);

    transmitString(logOutput);
    *logIndex = (*logIndex + 1) % LOG_MAX_ENTRIES;
}
