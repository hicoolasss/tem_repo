#include "../inc/uls.h"

static void file_list_info(const char *dir, t_file **file_list)
{
    DIR *dir_stream = NULL;
    struct dirent *dir_entry = NULL;
    t_stat *file_stats = NULL;

    t_stat *temp_stats = (t_stat *)malloc(sizeof(t_stat));
    lstat(dir, temp_stats);

    if (!S_ISDIR(temp_stats->st_mode))
    {
        char *permissions = NULL;
        permissions = get_permission(temp_stats, (char *)dir);
        push_back_file(file_list, temp_stats, permissions, (char *)dir, NULL);

        free(permissions);
        permissions = NULL;
    }
    else
    {
        if ((dir_stream = opendir(dir)) == NULL)
        {
            mx_printerr("uls: ");
            mx_printerr(dir);
            mx_printerr(": Permission denied\n");
            return;
        }
        while ((dir_entry = readdir(dir_stream)) != NULL)
        {
            if (!mx_strcmp(dir_entry->d_name, ".") || !mx_strcmp(dir_entry->d_name, "..") || dir_entry->d_name[0] == '.' || !mx_strcmp(dir_entry->d_name, "uls"))
            {
                continue;
            }

            file_stats = (t_stat *)malloc(sizeof(t_stat));
            int st = lstat(mx_strjoin(mx_strjoin(dir, "/"), dir_entry->d_name), file_stats);

            if (st == -1)
            {
                mx_printerr(strerror(ENOENT));
                mx_printchar('\n');
                exit(-1);
            }
            char *path = mx_strjoin(mx_strjoin(dir, "/"), dir_entry->d_name);
            char *permissions = NULL;
            permissions = get_permission(file_stats, path);
            push_back_file(file_list, file_stats, permissions, dir_entry->d_name, path);

            free(file_stats);
            free(permissions);
            file_stats = NULL;
            permissions = NULL;
        }
    }

    free(temp_stats);
    temp_stats = NULL;
    if (dir_stream != NULL)
        closedir(dir_stream);
}

void Flag_l(char **argv, int file_count, int dir_count, int *exit_value)
{
    t_file *file_data = NULL;

    if (file_count == 0 && dir_count == 0)
    {
        file_list_info(".", &file_data);
        sort_file_list(file_data, &mx_strcmp);
        format_output(file_data, 1);
        clear_file_list(&file_data);
    }
    else if ((file_count == 1 && dir_count == 0) || (file_count == 0 && dir_count == 1))
    {
        file_list_info(argv[0], &file_data);
        if (file_data == NULL)
        {
            *exit_value = 1;
            return;
        }
        sort_file_list(file_data, &mx_strcmp);
        if ((file_count == 1 && dir_count == 0))
            format_output(file_data, 0);
        else
            format_output(file_data, 1);
        clear_file_list(&file_data);
    }
    else
    {
        for (int i = 0; i < file_count; i++)
        {
            file_list_info(argv[i], &file_data);
        }
        sort_file_list(file_data, &mx_strcmp);
        format_output(file_data, 0);
        clear_file_list(&file_data);

        if (dir_count != 0 && file_count != 0)
            mx_printchar('\n');
        for (int i = file_count; i < file_count + dir_count; i++)
        {
            mx_printstr(argv[i]);
            mx_printchar(':');
            mx_printchar('\n');
            file_list_info(argv[i], &file_data);
            if (file_data == NULL)
            {
                *exit_value = 1;
                if (i + 1 != file_count + dir_count)
                    mx_printchar('\n');
                continue;
            }
            sort_file_list(file_data, &mx_strcmp);
            format_output(file_data, 1);
            clear_file_list(&file_data);
            if (i + 1 == file_count + dir_count)
                break;
            mx_printchar('\n');
        }
    }
}
