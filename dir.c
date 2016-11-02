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
    if(strlen(tabs) > 20) return;  // max recursion depth = 10
    struct DIR* here = opendir(path);
    struct dirent *element = readdir(here);
    int sumsize = 0;
    while(element != NULL) {
        if(strcmp(element->d_name, ".") && strcmp(element->d_name, "..")) {
            struct stat *info = (struct stat *)malloc(sizeof(struct stat));
            char *fullpath = (char *)malloc(strlen(path) + strlen(element->d_name) + 2);
            strcpy(fullpath, path);
            strcat(fullpath, "/");
            strcat(fullpath, element->d_name);
            stat(fullpath, info);
            int isdir = S_ISDIR(info->st_mode);
            char *padded = pad(element->d_name, 15);
            printf("%s%s  %s\n", tabs, padded, isdir ? "dir" : "file");
            fflush(stdout);
            free(padded);
            if(isdir) {
                char *newTabs = (char *)malloc(strlen(tabs) + 3);
                strcpy(newTabs, tabs);
                strcat(newTabs, "  ");
                sumsize += listDir(fullpath, newTabs);
                free(newTabs);
            }
            else
                sumsize += info->st_size;
            free(info);
            free(fullpath);
        }
        element = readdir(here);
    }
    free(here);
    free(element);
    return sumsize;
}

int main() {
    umask(0);
    setbuf(stdout, NULL);
    // struct DIR* here = opendir(".");
    // struct dirent *element = readdir(here);
    // int sumsize = 0;
    // while(element != NULL) {
    //     struct stat info;
    //     stat(element->d_name, &info);
    //     int isdir = S_ISDIR(info.st_mode);
    //
    //     if(!isdir)
    //         sumsize += info.st_size;
    //     element = readdir(here);
    // }
    // printf("Total size: %d bytes", sumsize)
    listDir(".", "");
}
