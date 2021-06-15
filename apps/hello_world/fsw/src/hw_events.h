#ifndef _hw_events_h_
#define _hw_events_h_

#define HW_RESERVED_EID          0  // Reserved, do not use
#define HW_INIT_INF_EID          1  // Init has been successful
#define HW_COMMAND_ERR_EID       2  // Error with a command
#define HW_COMMANDNOP_INF_EID    3  // NO-OP command success
#define HW_COMMANDRST_INF_EID    4  // Reset command success
#define HW_INVALID_MSGID_ERR_EID 5  // Invalid Message ID
#define HW_LEN_ERR_EID           6  // Invalid Length
#define HW_PIPE_ERR_EID          7  // Pipe Error (Software Bus)

/*
used to create a correctly-sized array that will contain information for registering the events with Event Services (EVS)
*/
#define HW_EVENT_COUNTS 7

#endif 
