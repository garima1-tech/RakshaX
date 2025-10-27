
#include <stdio.h>
#include <stdlib.h>
#include "sms.h"

void sendSMS(const char* number,const char* msg) {
    char cmd[256];
    snprintf(cmd,sizeof(cmd),"echo 'To:%s Msg:%s' >> datasets/sms.log", number, msg);
    system(cmd);
}
