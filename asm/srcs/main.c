/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kev.grosjean@gmail.com>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 13:06:57 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/01 10:58:51 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "asm.h"

// void    parse_file(int fd, t_bool option)
// {

// }

int check_format(int ac, char **av, char **file, t_bool *option)
{
    if (ac == 1)
    {
        printf(USAGE);
        return (0);
    }
    int i = 1;
    while (i < ac)
    {
        if (!strcmp(av[i], "-a"))
            *option = TRUE;
        else
            *file = av[i];
        i++;
    }
    return (1);
}

int main(int ac, char **av)
{  
    char *file = NULL;
    t_bool option = FALSE;
    int fd = 0;
    if (!check_format(ac, av, &file, &option))
        exit(1);
    if ((fd = open(file, O_RDONLY)) != -1)
    {
        printf("fd = %d\n", fd);
        // parse_file(fd, option);
    }
    else
    {
        printf("%s : %s\n", strerror(errno), file);
    }
    
    exit(0);
}