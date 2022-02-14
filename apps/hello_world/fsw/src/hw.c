#include "hw_events.h"
#include "hw_version.h"
#include "hw.h"

// Raspberry Pi library
#include "rpi_lib.h"

// declare all the global app data we need
HW_Data_t HW_Data;

// the name of this function must match the startup script
void HW_Main(void) {
    // most CFE and OS function calls return an int32 so we can check if it was successful
    // usually less than 0 is a fail and greater than 0 is success
    // you can also check if it does't equal OS_SUCCESS or CFE_SUCCESS too
    int32            Status;

    // a pointer to a buffer on the software bus
    // similar to a void pointer where it can be cast to any 
    // data structure depending on which message was received
    CFE_SB_Buffer_t *SBBufPtr;

    // register the app with Executive services
    CFE_ES_RegisterApp();

    // create the first Performance Log entry
    CFE_ES_PerfLogEntry(HW_PERF_ID);

    // perform application specific initialization. If it fails, set the RunStatus to CFE_ES_RunStatus_APP_ERROR and the app will not enter the run loop
    Status = HW_Init();
    if (Status != CFE_SUCCESS) {
        HW_Data.RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }

    // ES might "tell" our app to exit for many reasons
    // check on each interation of the while loop
    while (CFE_ES_RunLoop(&HW_Data.RunStatus) == true) {

        // pend forever until we receive a command packet
        Status = CFE_SB_ReceiveBuffer(&SBBufPtr, HW_Data.CommandPipe, CFE_SB_PEND_FOREVER);

        // check if there was an error with receiving the buffer
        if(Status == CFE_SUCCESS) {
            // if no error, send the "void" buffer to be processed
            HW_ProcessCommandPacket(SBBufPtr);
        }

        // one "iteration" has completed, stamp the performance exit entry
        CFE_ES_PerfLogExit(HW_PERF_ID);

        // start the performance entry again for the next loop
        CFE_ES_PerfLogEntry(HW_PERF_ID);

    }

    // last performance entry stamp
    CFE_ES_PerfLogExit(HW_PERF_ID);

    // exit application - generally an error if we get here
    CFE_ES_ExitApp(HW_Data.RunStatus);

}

int32 HW_Init(void) {
    int32 Status; // return status

    // indicate that we're in a run state
    // other options are:
    //      CFE_ES_RunStatus_APP_EXIT  - for normal exit
    //      CFE_ES_RunStatus_APP_ERROR - for errors
    HW_Data.RunStatus = CFE_ES_RunStatus_APP_RUN;

    // initialize app command execution counters
    // these counters give ground operators clues if their commands are working
    HW_Data.CmdCounter = 0;
    HW_Data.ErrCounter = 0;

    // initialize event filter table
    // we can filter certain events using special EVS rules
    // check out Event Message Filtering in cFE User's Guide for more
    // 0x0000 is no masking for an of the events
    HW_Data.EventFilters[0].EventID = HW_INIT_INF_EID;
    HW_Data.EventFilters[0].Mask    = 0x0000;
    HW_Data.EventFilters[1].EventID = HW_COMMAND_ERR_EID;
    HW_Data.EventFilters[1].Mask    = 0x0000;
    HW_Data.EventFilters[2].EventID = HW_COMMANDNOP_INF_EID;
    HW_Data.EventFilters[2].Mask    = 0x0000;
    HW_Data.EventFilters[3].EventID = HW_COMMANDRST_INF_EID;
    HW_Data.EventFilters[3].Mask    = 0x0000;
    HW_Data.EventFilters[4].EventID = HW_INVALID_MSGID_ERR_EID;
    HW_Data.EventFilters[4].Mask    = 0x0000;
    HW_Data.EventFilters[5].EventID = HW_LEN_ERR_EID;
    HW_Data.EventFilters[5].Mask    = 0x0000;
    HW_Data.EventFilters[6].EventID = HW_PIPE_ERR_EID;
    HW_Data.EventFilters[6].Mask    = 0x0000;

    // pass the previous array to EVS so we can start sending events
    Status = CFE_EVS_Register(HW_Data.EventFilters, HW_EVENT_COUNTS, CFE_EVS_EventFilter_BINARY);
    if (Status != CFE_SUCCESS) {
        CFE_ES_WriteToSysLog("Hello World: Error Registering Events, RC = 0x%08lX\n", (unsigned long)Status);

        // return with error
        return Status;
    }

    // initialize housekeeping (telemetry) packet
    // clears the uninitialized data so everything is empty
    CFE_MSG_Init(&HW_Data.HkTlm.TlmHeader.Msg, HW_HK_TLM_MID, sizeof(HW_Data.HkTlm));

    // create a Software Bus message pipe to hold incoming commands
    // this is like a queue that we'll process on each iteration of the app
    // if we receive more commands then we can process, maybe increase the pipe depth
    HW_Data.PipeDepth = HW_PIPE_DEPTH;
    strncpy(HW_Data.PipeName, "HW_CMD_PIPE", sizeof(HW_Data.PipeName)); // name it
    HW_Data.PipeName[sizeof(HW_Data.PipeName) - 1] = 0; // null terminate the string

    // actually create the pipe and check for an error
    Status = CFE_SB_CreatePipe(&HW_Data.CommandPipe, HW_Data.PipeDepth, HW_Data.PipeName);
    if (Status != CFE_SUCCESS) {
        CFE_ES_WriteToSysLog("Hello World: Error creating pipe, RC = 0x%08lX\n", (unsigned long)Status);

        // return with error
        return Status;
    }

    // subscribe to housekeeping request commands
    // any messages with the HW_SEND_HK_MID will get passed to our command pipe
    Status = CFE_SB_Subscribe(HW_SEND_HK_MID, HW_Data.CommandPipe);
    if (Status != CFE_SUCCESS) {
        CFE_ES_WriteToSysLog("Hello World: Error Subscribing to HK request, RC = 0x%08lX\n", (unsigned long)Status);

        // return with error
        return Status;
    }

    // subscribe to ground command packets
    // any messages with the HW_CMD_MID will get passed to our command pipe
    Status = CFE_SB_Subscribe(HW_CMD_MID, HW_Data.CommandPipe);
    if (Status != CFE_SUCCESS) {
        CFE_ES_WriteToSysLog("Hello World: Error Subscribing to Command, RC = 0x%08lX\n", (unsigned long)Status);

        // return with error
        return Status;
    }

    // successful initialization - print version string
    CFE_EVS_SendEvent(HW_INIT_INF_EID, CFE_EVS_EventType_INFORMATION, "Hello World App Initialized.%s", HW_VERSION_STRING);

    // return successfully
    return CFE_SUCCESS;

}

// processes the two types of commands we've subscribed to
void HW_ProcessCommandPacket(CFE_SB_Buffer_t *SBBufPtr) {
    CFE_SB_MsgId_t MsgId = CFE_SB_INVALID_MSG_ID;

    // get the message ID - check cFE User's Guide for more
    CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);

    // call the required function depending on which message ID was sent
    switch (MsgId) {

        // received a command from the ground
        case HW_CMD_MID:
            HW_ProcessGroundCommand(SBBufPtr);
            break;

        // received a request for housekeeping data
        case HW_SEND_HK_MID:
            HW_ReportHousekeeping((CFE_MSG_CommandHeader_t *)SBBufPtr);
            break;

        // unknown message ID
        default:
            CFE_EVS_SendEvent(HW_INVALID_MSGID_ERR_EID, CFE_EVS_EventType_ERROR, "Hello World: invalid command packet,MID = 0x%x", (unsigned int)CFE_SB_MsgIdToValue(MsgId));
            break;
    }
}

void HW_ProcessGroundCommand(CFE_SB_Buffer_t *SBBufPtr) {
    CFE_MSG_FcnCode_t CommandCode = 0;

    // get the function code, let's us know which type of command code was sent
    CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &CommandCode);

    // call the required function depending on which command code was sent
    switch (CommandCode) {

        // no-op
        case HW_NOOP_CC:
            // check if the message payload is the expected size before continuing
            if (HW_VerifyCmdLength(&SBBufPtr->Msg, sizeof(HW_NoopCmd_t))) {
                HW_Noop((HW_NoopCmd_t *)SBBufPtr);
            }
            break;

        // reset
        case HW_RESET_COUNTERS_CC:
            // check if the message payload is the expected size before continuing
            if (HW_VerifyCmdLength(&SBBufPtr->Msg, sizeof(HW_ResetCountersCmd_t))) {
                HW_ResetCounters((HW_ResetCountersCmd_t *)SBBufPtr);
            }
            break;

        // drive forward
        case HW_DRIVE_FORWARD_CC:
            // check if the message payload is the expected size before continuing
            if (HW_VerifyCmdLength(&SBBufPtr->Msg, sizeof(HW_DriveForwardCmd_t))) {
                HW_DriveForward((HW_DriveForwardCmd_t *)SBBufPtr);
            }
            break;

        // drive reverse
        case HW_DRIVE_REVERSE_CC:
            // check if the message payload is the expected size before continuing
            if (HW_VerifyCmdLength(&SBBufPtr->Msg, sizeof(HW_DriveReverseCmd_t))) {
                HW_DriveReverse((HW_DriveReverseCmd_t *)SBBufPtr);
            }
            break;

        // drive CW
        case HW_DRIVE_CW_CC:
            // check if the message payload is the expected size before continuing
            if (HW_VerifyCmdLength(&SBBufPtr->Msg, sizeof(HW_DriveCWCmd_t))) {
                HW_DriveCW((HW_DriveCWCmd_t *)SBBufPtr);
            }
            break;

        // drive CCW
        case HW_DRIVE_CCW_CC:
            // check if the message payload is the expected size before continuing
            if (HW_VerifyCmdLength(&SBBufPtr->Msg, sizeof(HW_DriveCCWCmd_t))) {
                HW_DriveCCW((HW_DriveCCWCmd_t *)SBBufPtr);
            }
            break;

        // unknown command code - error
        default:
            CFE_EVS_SendEvent(HW_COMMAND_ERR_EID, CFE_EVS_EventType_ERROR, "Invalid ground command code: CC = %d", CommandCode);
            break;
    }
}

// send housekeeping out using HW_HK_TLM_MID 
int32 HW_ReportHousekeeping(const CFE_MSG_CommandHeader_t *Msg) {

    // copy command execution counters into the telemetry packet
    HW_Data.HkTlm.CommandErrorCounter = HW_Data.ErrCounter;
    HW_Data.HkTlm.CommandCounter      = HW_Data.CmdCounter;

    // timestamp the telemetry packet
    CFE_SB_TimeStampMsg(&HW_Data.HkTlm.TlmHeader.Msg);

    // send the telemetry packet
    CFE_SB_TransmitMsg(&HW_Data.HkTlm.TlmHeader.Msg, true);

    // return successfully
    return CFE_SUCCESS;

} 

// command code 0 - NOOP - does nothing
int32 HW_Noop(const HW_NoopCmd_t *Msg) {
    
    // increment the command counter
    HW_Data.CmdCounter++;

    // print NO-OP message with version
    CFE_EVS_SendEvent(HW_COMMANDNOP_INF_EID, CFE_EVS_EventType_INFORMATION, "Hello World: NOOP command %s", HW_VERSION);

    // return successfully
    return CFE_SUCCESS;

}

// command code 1 - reset - resets the command and error counters
int32 HW_ResetCounters(const HW_ResetCountersCmd_t *Msg) {

    // reset the counters
    HW_Data.CmdCounter = 0;
    HW_Data.ErrCounter = 0;

    // print reset message
    CFE_EVS_SendEvent(HW_COMMANDRST_INF_EID, CFE_EVS_EventType_INFORMATION, "Hello World: RESET command");

    // return successfully
    return CFE_SUCCESS;

} 

// since we're casting SB buffers directly to the expected payload (NOOP or reset)
// we can perform a quick sanity check to make sure they're expected length before continuing
bool HW_VerifyCmdLength(CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength) {
    bool              result       = true;
    size_t            ActualLength = 0;
    CFE_SB_MsgId_t    MsgId        = CFE_SB_INVALID_MSG_ID;
    CFE_MSG_FcnCode_t FcnCode      = 0;

    // get the size
    CFE_MSG_GetSize(MsgPtr, &ActualLength);

    // verify the command packet length.
    if (ExpectedLength != ActualLength) {

        // get the message ID and function code to print in the error message
        CFE_MSG_GetMsgId(MsgPtr, &MsgId);
        CFE_MSG_GetFcnCode(MsgPtr, &FcnCode);

        CFE_EVS_SendEvent(HW_LEN_ERR_EID, CFE_EVS_EventType_ERROR, "Invalid Msg length: ID = 0x%X,  CC = %u, Len = %u, Expected = %u", (unsigned int)CFE_SB_MsgIdToValue(MsgId), (unsigned int)FcnCode, (unsigned int)ActualLength, (unsigned int)ExpectedLength);

        result = false;

        // increment the error counter
        HW_Data.ErrCounter++;
    }

    // return successfully
    return result;
}

int32 HW_DriveForward(const HW_DriveForwardCmd_t *Msg) {
    int32 Status;

    // Use RPI library to access hardware
    Status = RPI_LIB_DriveForward(Msg->TimeMS);
    if(Status == CFE_SUCCESS) {
        CFE_EVS_SendEvent(HW_DRIVE_FWD_INF_EID, CFE_EVS_EventType_INFORMATION, "HW: Drove forward for %dms",
                      Msg->TimeMS);
    }
    else {
        CFE_EVS_SendEvent(HW_DRIVE_ERR_EID, CFE_EVS_EventType_ERROR, "HW: Error on forward drive for %dms (EC=%d)",
                      Msg->TimeMS, Status);
    }

    return CFE_SUCCESS;
}

int32 HW_DriveReverse(const HW_DriveReverseCmd_t *Msg) {
    int32 Status;

    // Use RPI library to access hardware
    Status = RPI_LIB_DriveReverse(Msg->TimeMS);
    if(Status == CFE_SUCCESS) {
        CFE_EVS_SendEvent(HW_DRIVE_REV_INF_EID, CFE_EVS_EventType_INFORMATION, "HW: Drove reverse for %dms",
                      Msg->TimeMS);
    }
    else {
        CFE_EVS_SendEvent(HW_DRIVE_ERR_EID, CFE_EVS_EventType_ERROR, "HW: Error on reverse drive for %dms (EC=%d)",
                      Msg->TimeMS, Status);
    }

    return CFE_SUCCESS;
}

int32 HW_DriveCW(const HW_DriveCWCmd_t *Msg) {
    int32 Status;

    // Use RPI library to access hardware
    Status = RPI_LIB_DriveTurnCW(Msg->TimeMS);
    if(Status == CFE_SUCCESS) {
        CFE_EVS_SendEvent(HW_DRIVE_FWD_INF_EID, CFE_EVS_EventType_INFORMATION, "HW: Drove CW for %dms",
                      Msg->TimeMS);
    }
    else {
        CFE_EVS_SendEvent(HW_DRIVE_ERR_EID, CFE_EVS_EventType_ERROR, "HW: Error on CW drive for %dms (EC=%d)",
                      Msg->TimeMS, Status);
    }

    return CFE_SUCCESS;
}

int32 HW_DriveCCW(const HW_DriveCCWCmd_t *Msg) {
    int32 Status;

    // Use RPI library to access hardware
    Status = RPI_LIB_DriveTurnCCW(Msg->TimeMS);
    if(Status == CFE_SUCCESS) {
        CFE_EVS_SendEvent(HW_DRIVE_CCW_INF_EID, CFE_EVS_EventType_INFORMATION, "HW: Drove CCW for %dms",
                      Msg->TimeMS);
    }
    else {
        CFE_EVS_SendEvent(HW_DRIVE_ERR_EID, CFE_EVS_EventType_ERROR, "HW: Error on CCW drive for %dms (EC=%d)",
                      Msg->TimeMS, Status);
    }

    return CFE_SUCCESS;
}

