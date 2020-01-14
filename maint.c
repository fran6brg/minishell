#include "libft/libft.h"
#include <stdio.h>
int main(void)
{
    char ** ret;

    ret = ft_split_set("aa \'bb cc dd", " ");
    int i = -1;
    while (ret[++i])
        printf("ret[%d] = %s\n", i, ret[i]);
    return (1);
}