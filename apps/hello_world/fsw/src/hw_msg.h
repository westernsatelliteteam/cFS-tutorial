#ifndef _HW_msg_h_
#define _HW_msg_h_

// command codes
#define HW_NOOP_CC           0
#define HW_RESET_COUNTERS_CC 1

// commands that don’t have any arguments/parameters 
typedef struct {
    // SB command header - defined by the CFE and must be included
    CFE_MSG_CommandHeader_t CmdHeader;
} HW_NoArgsCmd_t;

// commands that don’t have any arguments/parameters 
typedef HW_NoArgsCmd_t HW_NoopCmd_t;
typedef HW_NoArgsCmd_t HW_ResetCountersCmd_t;

// HK telemetry structure
typedef struct {
    // SB telemetry header - defined by the CFE and must be included
    CFE_MSG_TelemetryHeader_t  TlmHeader;

    uint8 CommandCounter; // successful commands
    uint8 CommandErrorCounter; // unsuccessful commands
    uint8 Spare[2]; // add extra bytes - make multiple of 4
} HW_HkTlm_t;

#endif
