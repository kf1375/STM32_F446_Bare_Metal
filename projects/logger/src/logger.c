#include "logger.h"
#include "uart.h"
#include "systick.h"

LogEntry infoLogBuffer[LOG_MAX_ENTRIES];
LogEntry warningLogBuffer[LOG_MAX_ENTRIES];
LogEntry errorLogBuffer[LOG_MAX_ENTRIES];
LogEntry criticalLogBuffer[LOG_MAX_ENTRIES];

uint8_t infoLogIndex = 0;
uint8_t warningLogIndex = 0;
uint8_t errorLogIndex = 0;
uint8_t criticalLogIndex = 0;

char logOutput[LOG_OUTPUT_LENGHT];

void logger(LogLevel level, uint32_t logID, const char *message)
{
    LogEntry entry;
    memset(&logOutput, '\0', LOG_OUTPUT_LENGHT);

    entry.timestamp = get_tick();
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
    
    // Stream the log over UART2
    sprintf(logOutput, "Timestamp: %lu | Log Level: %s | Log ID: %lu | Message: %s\n",
                        entry.timestamp, LogLevelTags[entry.level], entry.logID, entry.message);
                        
    UART_Transmit_String(logOutput);

    *logIndex = (uint8_t) (*logIndex + 1) % LOG_MAX_ENTRIES;
}
