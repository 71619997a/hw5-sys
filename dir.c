#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *pad(char* str, int to) {
    char *padded = (char *)malloc(to + 1);
    padded[to] = 0;
    strncpy(padded, str, to);
    int i;
    for(i = strlen(str); i < to + 1; i++) {
        padded[i] = ' ';
    }
    return padded;
}

int main() {
    struct DIR* here = opendir(".");
    struct dirent *element = readdir(here);
    while(element != NULL) {
        struct stat info;
        stat(element->d_name, &info);
        int isdir = S_ISDIR(info.st_mode);
        if(isdir)
            printf("%s  dir\n", pad(element->d_name, 15));
        else
            printf(
                
            )
        element = readdir(here);
    }

}
