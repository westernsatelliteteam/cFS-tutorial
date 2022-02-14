#ifndef _hw_h_
#define _hw_h_

// required cFE API include 
#include "cfe.h"

// include require hello world defines
#include "hw_perfids.h"
#include "hw_msgids.h"
#include "hw_msg.h"


// the number of unprocessed commands our app can hold as long as we process commands quick enough, this should never fill up
#define HW_PIPE_DEPTH 32

// any data our application wishes to keep track of we put this in a struct so it can be created once at the start of our application. In embedded environments, always define variables early in the program life so your app will fail early if there's not enough memory
typedef struct {

    // counters
    uint8 CmdCounter;
    uint8 ErrCounter;

    // status of the app (cFE will modify this if things go bad)
    uint32 RunStatus;

    // spot to store the current telemetry packet
    HW_HkTlm_t HkTlm;

    // spot to store unprocessed incoming commands
    CFE_SB_PipeId_t CommandPipe;

    // metatdata for the command pipe
    char   PipeName[CFE_MISSION_MAX_API_LEN];
    uint16 PipeDepth;

    // array for metadata on all of our events
    CFE_EVS_BinFilter_t EventFilters[HW_EVENT_COUNTS];
} HW_Data_t;

// app main method that will be called by cFE upon startup
void  HW_Main(void);
int32 HW_Init(void);

// process incoming commands
void  HW_ProcessCommandPacket(CFE_SB_Buffer_t *SBBufPtr);

// process commands from the ground (NO-OP and reset)
void  HW_ProcessGroundCommand(CFE_SB_Buffer_t *SBBufPtr);

// functions to perform each action
int32 HW_ReportHousekeeping(const CFE_MSG_CommandHeader_t *Msg);
int32 HW_ResetCounters(const HW_ResetCountersCmd_t *Msg);
int32 HW_Noop(const HW_NoopCmd_t *Msg);
int32 HW_DriveForward(const HW_DriveForwardCmd_t *Msg);
int32 HW_DriveReverse(const HW_DriveReverseCmd_t *Msg);
int32 HW_DriveCW(const HW_DriveCWCmd_t *Msg);
int32 HW_DriveCCW(const HW_DriveCCWCmd_t *Msg);

// verifies that the incoming command matches the definition we made in hw_msgids.h
bool HW_VerifyCmdLength(CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength);

#endif
