//
// Created by vivek on 24/8/18.
//

#include "list_directory.h"
#include "global_variables.h"
//#include <string>
#include <string.h>
#include <unistd.h>

using namespace std;


vector<file_detail> list_directory(char* pathname) {
    vector<file_detail> file_names;
    string dir = string(pathname);
    struct dirent **file_list;
    int no_of_entries;
    no_of_entries = scandir(pathname, &file_list, NULL, alphasort);
    if (no_of_entries == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }
    for (long long i = 0; i < no_of_entries; i++) {
        printf("%-35s ", file_list[i]->d_name);
        file_names.push_back(file_detail());
        file_names[i].index = i;
        file_names[i].name = file_list[i]->d_name;

        struct stat file_stats;
        struct passwd *pwd;
        struct group *grp;

        if (stat(file_list[i]->d_name, &file_stats) == -1)
            //cout << "not";
        file_names[i].isdir = S_ISDIR(file_stats.st_mode);
        long long size = (long long) file_stats.st_size;
        if (size < 1024)
            printf("%-4lld ", size);
        else if ((size / 1024.0) < 1024) {
            printf("%-4.1fK", (size / 1024.0));

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

    }


    //printf("%s\n", get_current_dir_name());
    /*for(int i = 0 ; i  < path_history.size() ; i++) {
        printf("%s   ", path_history[i]);
    }*/
    printf("Current Directory : %s\n", curr_dir);
    return file_names;
}
