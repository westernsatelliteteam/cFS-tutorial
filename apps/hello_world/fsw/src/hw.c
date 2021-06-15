#include "hw_events.h"
#include "hw_version.h"
#include "hw.h"

HW_Data_t HW_Data;

void HW_Main(void) {

    // register the app with Executive services
    CFE_ES_RegisterApp();

    // print a message to the console - can't use EVS yet since we haven't registered!
    OS_printf("Hello world app says HELLO!\n");

    // let the cFE know we're successfully exiting
    CFE_ES_ExitApp(CFE_ES_RunStatus_APP_EXIT);

}
