#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

int get_number_of_files_sol(const char *path){
    struct stat st;
    if (stat(path, &st) != 0) return -1;
    if (S_ISREG(st.st_mode)) return 1;
    DIR *dir = opendir(path);
    if (!dir) return -2;
    struct dirent *entry;
    int sum = 0;
    while ((entry = readdir(dir)) != NULL){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;  // skip 
        char buffer[PATH_MAX];              // buffer to contain new path
        strcpy(buffer, path);
        strcat(buffer, "/");
        strcat(buffer, entry->d_name);    
        int temp = get_number_of_files_sol(buffer);
        if (temp < 0) return temp;
        sum += temp;
    }
    return sum;
}
