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
    //string dir = string(pathname);
    struct dirent **file_list;
    int no_of_entries;
    no_of_entries = scandir(pathname, &file_list, NULL, alphasort);
    if (no_of_entries == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }
    for (long long i = 0; i < no_of_entries; i++) {
        file_names.push_back(file_detail());
        file_names[i].name = file_list[i]->d_name;
        file_names[i].index = i;
        struct stat file_stats;
        struct passwd *pwd;
        struct group *grp;
        //printf(" pathname = %s ", pathname);
        char stat_path[1000];
        strcpy(stat_path, pathname);
        strcat(stat_path, "/");
        strcat(stat_path, file_names[i].name);
        if (stat(stat_path, &file_stats) == -1) {
            printf("path =  %s ", stat_path);
        }
        file_names[i].isdir = S_ISDIR(file_stats.st_mode);
        if(i >= left_file_index && i <= right_file_index) {
            printf("%-35.20s ", file_list[i]->d_name);
            //printf("isdir = %d ", file_names[i].isdir);
            long long size = (long long) file_stats.st_size;
            if (size < 1024)
                printf("%-5lld ", size);
            else if ((size / 1024.0) < 1024) {
                printf("%-5.1fK", (size / 1024.0));

            } else if ((size / (1024 * 1024)) < 1024) {
                printf("%-10.1fM ", size / (1024.0 * 1024.0));
            } else if ((size / (1024 * 1024 * 1024)) < 1024) {
                printf("%-10.1fG ", size / (1024.0 * 1024.0 * 1024.0));
            }

            if ((pwd = getpwuid(file_stats.st_uid)) != NULL)
                printf(" %12s", pwd->pw_name);
            else
                printf(" %-20d", file_stats.st_uid);


            /* Print out group name if it is found using getgrgid(). */
            if ((grp = getgrgid(file_stats.st_gid)) != NULL)
                printf(" %12s       ", grp->gr_name);
            else
                printf(" %20d", file_stats.st_gid);
            if (file_stats.st_mode & S_IRUSR)
                printf("r");
            else
                printf("-");
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
                printf("x       ");
            else
                printf("-       ");
            printf("%12s", ctime(&file_stats.st_mtime));
            // printf("\n");
            //right++;
        }
    }
    printf("----------------------------------------------------------------------------------------------------------------\n");

    //printf("%s\n", get_current_dir_name());
    /*for(int i = 0 ; i  < path_history.size() ; i++) {
        printf("%s   ", path_history[i]);
    }*/
    //printf(" %s ",get_current_dir_name());
    printf("Current Directory : %s\n", curr_dir);
   // for(int i = 0; i < )
 //   printf("%*\n", 20);
    //cursordownward();
    return file_names;
}
