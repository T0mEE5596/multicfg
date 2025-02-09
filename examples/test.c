#include<stdio.h>
#include "../src/multicfg.h"


int main(int argc, char *argv[]) {

    struct cords stc;

    int ret = multicfg_wrap(&stc, "player-1", "display-name", "testdoc");
    if (ret != 0) {
        printf("err");
        return -1;
    }
    printf("| %s                     ", stc.value);
    multicfg_wrap(&stc, "player-1", "last-online", "testdoc");
    printf("(%s)|", stc.value);

    return 0;
}



