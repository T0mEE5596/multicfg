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

    int open_node = find_node_start(&c, argv[1], count(argv[1]), argv[3], buffer_ptr);
    if (open_node == -2) {
        perror("file not found\n");
	return 2;
    }
    if (open_node == -1) {
        printf("[!]: node not found");
	return 3;
    }
    int close_node = find_node_end(&c, buffer_ptr);
    int retvalue = getvalue(&c, argv[2], count(argv[2]), buffer_ptr);
    if (retvalue == 0) printf("[+]: key founded");
    else printf("[!]: key not found");
    printf("\nopened in line: %d\nended in line: %d\nreturned code: %d\nfounded any end?: %d\nfounded any value?: %d\nvalue: %s", c.start, c.end, open_node, close_node, retvalue, c.value);
    return 0;
}






