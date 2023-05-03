#include "../inc/libmx.h"

void mx_sort_strarr(char ***arr)
{
	for (int i = 0; (*arr)[i]; ++i)
	{
		for (int j = 0; (*arr)[j+1]; ++j)
		{
			if(mx_strcmp((*arr)[j], (*arr)[j+1]) > 0)
			{
				char *temp = mx_strdup((*arr)[j]);
				(*arr)[j] = mx_strdup((*arr)[j+1]);
				(*arr)[j+1] = mx_strdup(temp);
			}
		}
	}
}

