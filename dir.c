#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *pad(char* str, int to) {
    char *padded = (char *)malloc(to + 1);
    strncpy(padded, str, to);
    int i;
    for(i = strlen(str); i < to; i++) {
        padded[i] = ' ';
    }
    padded[to] = 0;
    return padded;
}

int listDir(char *path, char *tabs) {
    if(strlen(tabs) > 20) return; // max recursion depth = 10
    DIR* here = opendir(path);
    struct dirent *element = readdir(here);
    int sumsize = 0;
    int first = 1;
    while(element != NULL) {
        if(strcmp(element->d_name, ".") && strcmp(element->d_name, "..")) {
            struct stat *info = (struct stat *)malloc(sizeof(struct stat));
            char *fullpath = (char *)malloc(strlen(path) + strlen(element->d_name) + 2);
            strcpy(fullpath, path);
            strcat(fullpath, "/");
            strcat(fullpath, element->d_name);
            stat(fullpath, info);
            int isdir = S_ISDIR(info->st_mode);
            char *extname = (char *)malloc(44);
            strcpy(extname, tabs);
            strcat(extname, first ? "└> " : "   ");
            strncat(extname, element->d_name, 35 - strlen(tabs));
            if(strlen(extname) >= 38) {
                strcat(extname, "...");
            }
            char *padded = pad(extname, first ? 45 : 43);
            if(!isdir)
                printf("%s  file  %dB\n", padded, info->st_size);
            else
                printf("%s  dir\n", padded);
            fflush(stdout);
            free(padded);
            if(isdir) {
                char *newTabs = (char *)malloc(strlen(tabs) + 3);
                strcpy(newTabs, tabs);
                strcat(newTabs, "   ");
                sumsize += listDir(fullpath, newTabs);
                free(newTabs);
            }
            else
                sumsize += info->st_size;
            free(info);
            free(fullpath);
            free(extname);
            first = 0;
        }
        element = readdir(here);
    }
    free(here);
    free(element);
    return sumsize;
}

int main() {
    umask(0);
    printf("In directory .\n");
    printf("Total size: %dB", listDir(".", ""));
    return 0;
}
