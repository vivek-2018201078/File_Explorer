//
// Created by vivek on 24/8/18.
//

#include "list_directory.h"
#include "global_variables.h"
//#include <string>
#include <string.h>
#include <unistd.h>
#include "raw_input.h"

using namespace std;

void list(vector<file_detail> file_names) {
    for(int i = left_file_index; i <= right_file_index; i++) {
        printf("%-35s \n", file_names[i].name);
    }
}

vector<file_detail> list_directory(char* pathname) {
    vector<file_detail> file_names;
    struct dirent **file_list;
    int no_of_entries;
    no_of_entries = scandir(pathname, &file_list, NULL, alphasort);
    if (no_of_entries == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }
    printf("\r");
    printf("\033[%dB", terminal_lines);
    printf("------NORMAL MODE------");
    printf("\r");                         //Move cursor to strt of line
    printf("\033[%dA", terminal_lines);
    //printf("%s ", pathname);
    for (long long i = 0; i < no_of_entries; i++) {
        file_names.push_back(file_detail());
        file_names[i].name = file_list[i]->d_name;
        file_names[i].index = i;
        struct stat file_stats;
        struct passwd *pwd;
        struct group *grp;
        char stat_path[1000];
        strcpy(stat_path, pathname);
        strcat(stat_path, "/");
        strcat(stat_path, file_names[i].name);
        if (stat(stat_path, &file_stats) == -1) {
            //printf("path =  %s ", stat_path);
        }
        file_names[i].isdir = S_ISDIR(file_stats.st_mode);
        if(i >= left_file_index && i <= right_file_index) {
            printf("%-20.20s ", file_list[i]->d_name);
            long long size = (long long) file_stats.st_size;
            if (size < 1024)
                printf("%-5lld ", size);
            else if ((size / 1024.0) < 1024) {
                printf("%.1fK", (size / 1024.0));

            } else if ((size / (1024 * 1024)) < 1024) {
                printf("%.1fM ", size / (1024.0 * 1024.0));
            } else if ((size / (1024 * 1024 * 1024)) < 1024) {
                printf("%.1fG ", size / (1024.0 * 1024.0 * 1024.0));
            }

            if ((pwd = getpwuid(file_stats.st_uid)) != NULL)
                printf("\t%s", pwd->pw_name);
            else
                printf("\t%d", file_stats.st_uid);


            if ((grp = getgrgid(file_stats.st_gid)) != NULL)
                printf("\t%s", grp->gr_name);
            else
                printf("\t%d", file_stats.st_gid);
            if (file_stats.st_mode & S_IRUSR)
                printf("\tr");
            else
                printf("\t-");
            if (file_stats.st_mode & S_IWUSR)
                printf("w");
            else
                printf("-");
            if (file_stats.st_mode & S_IXUSR)
                printf("x");
            else
                printf("-");
            if (file_stats.st_mode & S_IRGRP)
                printf("r");
            else
                printf("-");
            if (file_stats.st_mode & S_IWGRP)
                printf("w");
            else
                printf("-");
            if (file_stats.st_mode & S_IXGRP)
                printf("x");
            else
                printf("-");
            printf("  %s", ctime(&file_stats.st_mtime));
        }
    }
    printf("--------------------------------------------------------------------------------\n");

    printf("Current Directory : %.30s\n", pathname);
    return file_names;
}
