#ifndef _HW_msg_h_
#define _HW_msg_h_

// command codes
#define HW_NOOP_CC           0
#define HW_RESET_COUNTERS_CC 1
#define HW_DRIVE_FORWARD_CC  2
#define HW_DRIVE_REVERSE_CC  3
#define HW_DRIVE_CW_CC       4
#define HW_DRIVE_CCW_CC      5

// commands that don’t have any arguments/parameters 
typedef struct {
    // SB command header - defined by the CFE and must be included
    CFE_MSG_CommandHeader_t CmdHeader;
} HW_NoArgsCmd_t;

// commands that don’t have any arguments/parameters 
typedef HW_NoArgsCmd_t HW_NoopCmd_t;
typedef HW_NoArgsCmd_t HW_ResetCountersCmd_t;

// commands that have a drive time
typedef struct {
    CFE_MSG_CommandHeader_t CmdHeader;
    int32 TimeMS;
} HW_DriveCmd_t;

typedef HW_DriveCmd_t HW_DriveForwardCmd_t;
typedef HW_DriveCmd_t HW_DriveReverseCmd_t;
typedef HW_DriveCmd_t HW_DriveCWCmd_t;
typedef HW_DriveCmd_t HW_DriveCCWCmd_t;

// HK telemetry structure
typedef struct {
    // SB telemetry header - defined by the CFE and must be included
    CFE_MSG_TelemetryHeader_t  TlmHeader;

    uint8 CommandCounter; // successful commands
    uint8 CommandErrorCounter; // unsuccessful commands
    uint8 Spare[2]; // add extra bytes - make multiple of 4
} HW_HkTlm_t;

#endif
