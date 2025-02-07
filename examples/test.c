#include<string.h>
#include<stdio.h>
#include "../src/multicfg.h"


int main(int argc, char *argv[]) {
    struct cords stc;
    int ret = multicfg_wrap(&stc, argv[1], argv[2], argv[3]);

    if(ret != 0) {
        printf("err\n");
        return -1;
    }
    printf("value: %s\n", stc.value);
    return 0;
}



