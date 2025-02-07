#ifndef MULTICFG_H
#define MULTICFG_H

#define MAX_LEN 300

struct cords{
    int start;
    int end;
    char value[MAX_LEN];
};

int multicfg_wrap(struct cords* c,
	char* nodename, char* key, char* file
		);


#endif
