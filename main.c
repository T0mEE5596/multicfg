#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 300

// mines strcmp (because string.h's strcmp doesnt work properly in my code *idk why)
int stringcmp(char *str1, char *str2) {
    int i = 0;
    while (str1[i+1] != '\0')
    {
          if (str1[i] != str2[i])
	  {
	      return -1;
	  }
	  i++;
    }
    return 0;
}


int count(char *str) {
  int ret = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    ret++;
  }
  return ret;
}

struct cords {
  int start; // start row of node
  int end; // end row of node (length)
  char value[MAX_LEN];
};

int find_node_start(struct cords *cordinate, char *rootname, int namesize, char *file,
              char **buffer) {
  namesize--;

  size_t name_length = 0;
  int onnode = 0;  /* iteration/boolean value indicating if loop is on node data iteration or not
		         * used to skip data inside node brackets    */
  int onstr = 0;   // indicates if current iteration state is on string * used to ignore in-string brackets

  char namebuffer[namesize];  // compare buffer
  cordinate->start = 0;
  FILE *f = fopen(file, "r");
  char temp[MAX_LEN];
  int i = 0;
  int size;

  if (f == NULL) return -2;
  while (fgets(temp, MAX_LEN, f)) {
    size = count(temp);

    buffer[i] = (char *)malloc(size + 1);
    for (int j = 0; j <= size; j++) {
      buffer[i][j] = temp[j];
    }
    i++;
  }
  fclose(f);

  for (int l = 0; l <= i - 1; l++) {
    for (int c = 0; buffer[l][c] != '\n'; c++) {

      if (buffer[l][c] == 34) {
        if (onstr) {
	  onstr = 0;
	  continue;
	}
	onstr = 1;
	continue;
      }
      if (onstr) continue;

      if (buffer[l][c] == '}' && onnode) {
        onnode--;
	continue;
      }else if(onnode > 0) continue;
      namebuffer[name_length] = buffer[l][c];
      name_length++;
      if (buffer[l][c] == ' ') {
        namebuffer[name_length] = '\0';
        name_length = 0;
      }else if(buffer[l][c] == '{'){
        onnode++;
	continue;
      }
      if (name_length == namesize) {
        namebuffer[name_length + 1] = '\0';
        if (stringcmp(rootname, namebuffer) == 0) {

          cordinate->start = l;
          return 0;
        }
      }
    }
  }
  return -1;
}

int find_node_end(struct cords *cordinate, char **buffer) {
  int innode = 0;
  int instr = 0;
  cordinate->end = 0;


  for(int i=cordinate->start;; i++) {
    for(int j=0; buffer[i][j] != '\n'; j++) {

      if (buffer[i][j] == 34) {
        if (instr) {
	  instr = 0;
	  continue;
	}
	instr = 1;
	continue;
      }

      if (instr) continue;
      if (innode == 0 && i != cordinate->start) {
        cordinate->end = i;
	return 0;
      }
      if (buffer[i][j] == '{') innode++;
      else if (buffer[i][j] == '}' && innode) innode--;
    }
  }
  return -1;
}

int getvalue(struct cords *range, char *key, int keysize, char **buffer) {
  keysize--;
  int instr = 0;
  size_t key_length = 0;
  char keybuffer[keysize];

  for (int i = range->start; i != range->end; i++) {
    for (int j = 0; buffer[i][j] != '\n'; j++) {

      if (buffer[i][j] == 34) {
        if (instr) {
	  instr = 0;
	  continue;
	}
	instr = 1;
	continue;
      }
      if (instr) continue;
      keybuffer[key_length] = buffer[i][j];
      key_length++;
      if (buffer[i][j] == ' ') {
        keybuffer[key_length] = '\0';
	key_length = 0;
      }
      if (key_length == keysize) {
        keybuffer[key_length + 1] = '\0';
	if (stringcmp(key, keybuffer) == 0) {
	  while (buffer[i][j] != '\0') {
	    if (buffer[i][j] == '=') {
	      int c = 1;
	      for (j; buffer[i][j] != '\0'; j++) {
	        if (buffer[i][j] == 34) {
		  if (instr) {
		    return 0;
		  }
		  instr = 1;
		  j++;
		}
		if (instr) {
		  range->value[c] = buffer[i][j];
		  c++;
		}
	      }
	    }
	    j++;
	  }
	  return 0;
	}
      }
    }
  }
  return -1;
}



int main(int argc, char *argv[]) {
  if (argc < 3) {
    perror("too few arguments\n");
    return 1;
  }
  struct cords c;
  char *buffer[MAX_LEN];
  char **buffer_ptr = buffer;

  int sex = find_node_start(&c, argv[1], count(argv[1]), argv[3], buffer_ptr);
  if (sex == -2) {
    perror("file not found\n");
    return 2;
  }
  if (sex == -1) {
    printf("[!]: node not found\n");
    return 3;
  }
  int sex1 = find_node_end(&c, buffer_ptr);
  int cum = getvalue(&c, argv[2], count(argv[2]), buffer_ptr);
  if (cum == 0) printf("[+]: key founded\n");
  else printf("[!]: key not found\n");
  printf("\nopened in line: %d\nended in line: %d\nreturned code: %d\n"\
		  "finded any end?: %d\nfounded value?:%d\nvalue:%s", c.start, c.end, sex, sex1, cum, c.value);
  return 0;


}

