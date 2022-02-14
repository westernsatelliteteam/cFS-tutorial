#ifndef _rpi_lib_h_
#define _rpi_lib_h_

#include "cfe.h"

// init the library - required by cFE
int32 RPI_LIB_Init(void);

// drive commands
int32 RPI_LIB_DriveForward(int32 DriveTime);
int32 RPI_LIB_DriveReverse(int32 DriveTime);
int32 RPI_LIB_DriveTurnCW(int32 DriveTime);
int32 RPI_LIB_DriveTurnCCW(int32 DriveTime);

#endif