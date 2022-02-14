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
#define HW_DRIVE_FWD_INF_EID     8  // Drive motors forward 
#define HW_DRIVE_REV_INF_EID     9  // Drive motors reverse 
#define HW_DRIVE_CW_INF_EID      10 // Drive motors CW 
#define HW_DRIVE_CCW_INF_EID     11 // Drive motors CCW 
#define HW_DRIVE_ERR_EID         12 // Drive motors error 

/*
used to create a correctly-sized array that will contain information for registering the events with Event Services (EVS)
*/
#define HW_EVENT_COUNTS 12

#endif 
