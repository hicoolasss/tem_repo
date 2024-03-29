#include "../inc/uls.h"

t_file *create_file_node(t_stat *stats, char *permiss, char *name, char *path)
{
    t_file *files = (t_file *)malloc(sizeof(t_file));

    files->stat.st_mode = stats->st_mode;
    files->stat.st_ino = stats->st_ino;
    files->stat.st_dev = stats->st_dev;
    files->stat.st_rdev = stats->st_rdev;
    files->stat.st_nlink = stats->st_nlink;
    files->stat.st_uid = stats->st_uid;
    files->stat.st_gid = stats->st_gid;
    files->stat.st_size = stats->st_size;
    files->stat.st_atime = stats->st_atime;
    files->stat.st_mtime = stats->st_mtime;
    files->stat.st_ctime = stats->st_ctime;
    files->stat.st_blksize = stats->st_blksize;
    files->stat.st_blocks = stats->st_blocks;

    files->permission = mx_strdup(permiss);
    files->links = mx_strdup(mx_itoa((nlink_t)(stats->st_nlink)));
    files->owner = mx_strdup(getpwuid(stats->st_uid)->pw_name);
    if (getgrgid(stats->st_gid) == NULL)
    {
        files->group = mx_strdup(mx_itoa(stats->st_gid));
    }
    else
        files->group = mx_strdup(getgrgid(stats->st_gid)->gr_name);

    if (S_ISCHR(stats->st_mode) || S_ISBLK(stats->st_mode))
    {
        char *majr = mx_itoa(major(stats->st_rdev));
        char *minr = mx_itoa(minor(stats->st_rdev));
        char *oxoo = mx_strnew(4);
        oxoo[0] = ',';
        oxoo[1] = ' ';
        oxoo[2] = '0';
        oxoo[3] = 'x';
        if (minor(stats->st_rdev) > 255)
        {
            for (int i = 0; i < 8 - mx_strlen(mx_nbr_to_hex(minor(stats->st_rdev))); ++i)
            {
                oxoo = mx_strjoin(oxoo, "0");
            }
            files->bytes = mx_strdup(mx_strjoin(mx_strjoin(majr, oxoo), mx_nbr_to_hex(minor(stats->st_rdev))));
        }
        else if (mx_strlen(minr) == 3 && minor(stats->st_rdev) <= 255)
            files->bytes = mx_strdup(mx_strjoin(mx_strjoin(majr, ", "), mx_itoa(minor(stats->st_rdev))));
        else if (mx_strlen(minr) == 2)
            files->bytes = mx_strdup(mx_strjoin(mx_strjoin(majr, ",  "), mx_itoa(minor(stats->st_rdev))));
        else
            files->bytes = mx_strdup(mx_strjoin(mx_strjoin(majr, ",   "), mx_itoa(minor(stats->st_rdev))));
        free(oxoo);
        oxoo = NULL;
    }
    else
        files->bytes = mx_strdup(mx_itoa((off_t)(stats->st_size)));

    char *time_temp = ctime(&(stats->st_mtime));
    char *t_dup = mx_strndup(&time_temp[19], 5);
    time_t lt = time(NULL);
    char *time_now = ctime(&lt);
    char *n_dup = mx_strndup(&time_now[19], 5);

    if (mx_strcmp(t_dup, n_dup) != 0)
    {
        files->time = mx_strdup(mx_strjoin(mx_strndup(&ctime(&(stats->st_mtime))[4], 7), t_dup));
    }
    else
        files->time = mx_strndup(&ctime(&(stats->st_mtime))[4], 12);

    if (!S_ISLNK(stats->st_mode))
    {
        files->name = mx_strdup(name);
    }
    else
    {
        int bufsiz = stats->st_size;
        if (stats->st_size == 0)
            bufsiz = PATH_MAX;
        char *buf = mx_strnew(bufsiz);

        if (path != NULL)
            readlink(path, buf, bufsiz);
        else
            readlink(name, buf, bufsiz);

        files->name = mx_strdup(mx_strjoin(mx_strjoin(name, " -> "), buf));
        free(buf);
        buf = NULL;
    }
    files->next = NULL;

    return files;
}

void push_back_file(t_file **files, t_stat *stats, char *permiss, char *name, char *path)
{
    if (!files)
    {
        return;
    }
    if (!*files)
    {
        *files = create_file_node(stats, permiss, name, path);
        return;
    }

    t_file *temp = *files;
    while (temp->next)
    {
        temp = temp->next;
    }
    temp->next = create_file_node(stats, permiss, name, path);
}

// int file_list_size(t_file *files)
// {
//     int count = 0;
//     while (files)
//     {
//         files = files->next;
//         count++;
//     }
//     return count;
// }

t_file *sort_file_list(t_file *files, int (*cmp)(const char *, const char *))
{
    if (cmp == NULL || files == NULL)
        return files;
    t_file *temp = files;
    int count = 0;
    while (temp)
    {
        temp = temp->next;
        count++;
    }

    for (int i = 0; i < count; i++)
    {
        temp = files;
        for (int j = 0; j < count - 1; j++)
        {
            if (cmp(temp->name, temp->next->name) > 0)
            {
                char *permission = temp->permission;
                temp->permission = temp->next->permission;
                temp->next->permission = permission;
                char *links = temp->links;
                temp->links = temp->next->links;
                temp->next->links = links;
                char *owner = temp->owner;
                temp->owner = temp->next->owner;
                temp->next->owner = owner;
                char *group = temp->group;
                temp->group = temp->next->group;
                temp->next->group = group;
                char *bytes = temp->bytes;
                temp->bytes = temp->next->bytes;
                temp->next->bytes = bytes;
                char *time = temp->time;
                temp->time = temp->next->time;
                temp->next->time = time;
                char *name = temp->name;
                temp->name = temp->next->name;
                temp->next->name = name;
            }
            temp = temp->next;
        }
    }
    return files;
}

void clear_file_list(t_file **list)
{
    if (!*list)
        return;
    t_file *temp;
    while (*list)
    {
        temp = (*list)->next;
        (*list)->next = NULL;
        free(*list);
        *list = temp;
    }
}
