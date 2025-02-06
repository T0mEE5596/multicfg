#include<string.h>
#include<stdio.h>
#include "../src/multicfg.h"

int find_node_start(struct cords* cordinate, char* rootname, int namesize, char* file, char** buffer);
int find_node_end(struct cords* cordinate, char** buffer);
int getvalue(struct cords* range, char* key, int keysize, char** buffer);
int count(char* str);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("too few arguments\n");
        return 1;
    }
    struct cords c;
    char* buffer[MAX_LEN];
    char** buffer_ptr = buffer;

    char r[255];
    if (strlen(argv[1]) > 255){
        printf("exceeded the buffer length");
        return 4;
    }
    strcpy(r, argv[1]);
    strcat(r, "0");

    int open_node = find_node_start(&c, r, strlen(r), argv[3], buffer_ptr);
    if (open_node == -2) {
        perror("file not found\n");
	return 2;
    }else if (open_node == -1) {
        printf("[!]: node not found");
	return 3;
    }else if (open_node == -3) {
        printf("[!]: unclosed string");
	return 5;
    }
    int close_node = find_node_end(&c, buffer_ptr);
    if (close_node == -2) {
        printf("[!]: unclosed string");
	return 5;
    }


    if (strlen(argv[2]) > 255){
        printf("exceeded the buffer length");
        return 4;
    }
    strcpy(r, argv[2]);
    strcat(r, "0");

    int retvalue = getvalue(&c, r, strlen(r), buffer_ptr);
    if (retvalue == 0) printf("[+]: key founded");
    else printf("[!]: key not found");
    printf("\nopened in line: %d\nended in line: %d\nreturned code: %d\nfounded any end?: %d\nfounded any value?: %d\nvalue: %s", c.start, c.end, open_node, close_node, retvalue, c.value);
    return 0;
}






