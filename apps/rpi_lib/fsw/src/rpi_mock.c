#include "rpi_lib_version.h"
#include "rpi_lib.h"

// init the library - required by cFE
int32 RPI_LIB_Init(void) {
    // mocked function so just return successful
    OS_printf("RPI Mock Initialized.%s\n", RPI_LIB_VERSION_STRING);
    return CFE_SUCCESS;
}

// drive commands

int32 RPI_LIB_DriveForward(int32 DriveTime) {
    OS_printf("Driving forward for %d ms\n", DriveTime);
    return CFE_SUCCESS;
}

int32 RPI_LIB_DriveReverse(int32 DriveTime) {
    OS_printf("Driving reverse for %d ms\n", DriveTime);
    return CFE_SUCCESS;
}

int32 RPI_LIB_DriveTurnCW(int32 DriveTime) {
    OS_printf("Driving CW for %d ms\n", DriveTime);
    return CFE_SUCCESS;
}

int32 RPI_LIB_DriveTurnCCW(int32 DriveTime) {
    OS_printf("Driving CCW for %d ms\n", DriveTime);
    return CFE_SUCCESS;
}
