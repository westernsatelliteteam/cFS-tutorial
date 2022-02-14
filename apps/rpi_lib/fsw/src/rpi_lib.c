#include "rpi_lib_version.h"
#include "rpi_lib.h"

#include <unistd.h> // for usleep
#include <fcntl.h> // for open, close, write

#define RPI_LIB_LEFT_MOTOR_A 0
#define RPI_LIB_LEFT_MOTOR_B 1
#define RPI_LIB_RIGHT_MOTOR_A 2
#define RPI_LIB_RIGHT_MOTOR_B 3
#define RPI_LIB_MOTOR_ENABLE 4

int RPI_LIB_Motor_FD[5];
const char* RPI_LIB_MOTOR_PINS[5] = { "24", "23", "5", "6", "25" };
const char* RPI_LIB_FORWARD[5] = { "1", "0", "1", "0", "1" };
const char* RPI_LIB_REVERSE[5] = { "0", "1", "0", "1", "1" };
const char* RPI_LIB_CW[5]      = { "1", "0", "0", "1", "1" };
const char* RPI_LIB_CCW[5]     = { "0", "1", "1", "0", "1" };

// init the library - required by cFE
int32 RPI_LIB_Init(void) {
    int32 Status;

    // unexport any previously exported pins
    int UnexportFD = open("/sys/class/gpio/unexport", O_WRONLY);
    if (UnexportFD == -1) {
        OS_printf("Unable to open /sys/class/gpio/unexport");
        return -1;
    }

    for(int i = 0; i < 5; i++) {
        Status = write(UnexportFD, RPI_LIB_MOTOR_PINS[i], 2);
    }

    // export the pins
    int ExportFD = open("/sys/class/gpio/export", O_WRONLY);
    if (ExportFD == -1) {
        OS_printf("Unable to open /sys/class/gpio/export");
        return -1;
    }

    for(int i = 0; i < 5; i++) {
        Status = write(ExportFD, RPI_LIB_MOTOR_PINS[i], 2);
        if(Status < 0) {
            OS_printf("Error enabling pin %s (EC=%d)\n", RPI_LIB_MOTOR_PINS[i], Status);
            return -1;
        }
    }

    close(ExportFD);

    // set direction to OUT
    for(int i = 0; i < 5; i++) {
        char Path[64];
        sprintf(Path, "/sys/class/gpio/gpio%s/direction", RPI_LIB_MOTOR_PINS[i]);
        int DirectionFD = open(Path, O_WRONLY);
        if (DirectionFD == -1) {
            OS_printf("Unable to open %s (EC=%d)\n", Path, Status);
            return -1;
        }

        Status = write(DirectionFD, "out", 3);
        if(Status < 0) {
            OS_printf("Unable to configure %s as out (EC=%d)\n", Path, Status);
            return -1;
        }

        close(DirectionFD);

    }

    // open the value files for later writing
    for(int i = 0; i < 5; i++) {
        char Path[64];
        sprintf(Path, "/sys/class/gpio/gpio%s/value", RPI_LIB_MOTOR_PINS[i]);
        RPI_LIB_Motor_FD[i] = open(Path, O_WRONLY);
        if (RPI_LIB_Motor_FD[i] == -1) {
            OS_printf("Unable to open %s (EC=%d)\n", Path, Status);
            return -1;
        }
    }



    OS_printf("RPI library Initialized.%s\n", RPI_LIB_VERSION_STRING);
    return CFE_SUCCESS;
}

// drive commands from https://www.ics.com/blog/how-control-gpio-hardware-c-or-c

int32 RPI_LIB_DriveForward(int32 DriveTime) {
    int32 Status;

    // write to value files
    for(int i = 0; i < 5; i++) {
        Status = write(RPI_LIB_Motor_FD[i], RPI_LIB_FORWARD[i], 1);
        if (Status < 0) {
            OS_printf("Error writing pin index %d (EC=%d)\n", i, Status);
            return -1;
        }
    }

    usleep(DriveTime*1000);

    Status = write(RPI_LIB_Motor_FD[RPI_LIB_MOTOR_ENABLE], "0", 1);
    if (Status != 1) {
        OS_printf("Error stopping motors (EC=%d)\n", Status);
        return -1;
    }

    return CFE_SUCCESS;
}

int32 RPI_LIB_DriveReverse(int32 DriveTime) {
    int32 Status;

    // write to value files
    for(int i = 0; i < 5; i++) {
        Status = write(RPI_LIB_Motor_FD[i], RPI_LIB_REVERSE[i], 1);
        if (Status < 0) {
            OS_printf("Error writing pin index %d (EC=%d)\n", i, Status);
            return -1;
        }
    }

    usleep(DriveTime*1000);

    Status = write(RPI_LIB_Motor_FD[RPI_LIB_MOTOR_ENABLE], "0", 1);
    if (Status != 1) {
        OS_printf("Error stopping motors (EC=%d)\n", Status);
        return -1;
    }

    return CFE_SUCCESS;
}

int32 RPI_LIB_DriveTurnCW(int32 DriveTime) {
    int32 Status;

    // write to value files
    for(int i = 0; i < 5; i++) {
        Status = write(RPI_LIB_Motor_FD[i], RPI_LIB_CW[i], 1);
        if (Status < 0) {
            OS_printf("Error writing pin index %d (EC=%d)\n", i, Status);
            return -1;
        }
    }

    usleep(DriveTime*1000);

    Status = write(RPI_LIB_Motor_FD[RPI_LIB_MOTOR_ENABLE], "0", 1);
    if (Status != 1) {
        OS_printf("Error stopping motors (EC=%d)\n", Status);
        return -1;
    }

    return CFE_SUCCESS;
}

int32 RPI_LIB_DriveTurnCCW(int32 DriveTime) {
    int32 Status;

    // write to value files
    for(int i = 0; i < 5; i++) {
        Status = write(RPI_LIB_Motor_FD[i], RPI_LIB_CCW[i], 1);
        if (Status < 0) {
            OS_printf("Error writing pin index %d (EC=%d)\n", i, Status);
            return -1;
        }
    }

    usleep(DriveTime*1000);

    Status = write(RPI_LIB_Motor_FD[RPI_LIB_MOTOR_ENABLE], "0", 1);
    if (Status != 1) {
        OS_printf("Error stopping motors (EC=%d)\n", Status);
        return -1;
    }

    return CFE_SUCCESS;
}
