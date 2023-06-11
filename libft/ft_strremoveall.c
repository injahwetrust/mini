/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremoveall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:28:18 by bvaujour          #+#    #+#             */
/*   Updated: 2023/06/11 14:28:36 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*remove all occurences of to_del in src, option = 1 to free src, option = 2 to free to_del, option = 3 to free both*/

static int del_in(char *src, char *to_del, int begin)
{
    int i;
    int j;

    i = -1;
    while (src[++i])
    {
        j = 0;
        while (src[i] == to_del[j])
        {
            i++;
            j++;
            if (!to_del[j])
                return (i - ft_strlen(to_del) + begin);
        }
        if (!src[i])
            break;
    }
    return (-1);
}

static void manage_heap(char *src, char *to_del, int option)
{
    if (src && option == 1)
        free(src);
    if (to_del && option == 2)
        free(to_del);
    if (option == 3)
    {
        if (src)
            free(src);
        if (to_del)
            free(to_del);
    }
}
 
static int x_str(char *src, char *to_del)
{
    int go_to;
    int i;
    int x;

    x = 0;
    i = 0;
    while ((go_to = del_in(src + i, to_del, i)) != -1)
    {
        i = ft_strlen(to_del) + go_to;
        x++;
    }
    return (x);
}

char    *ft_strremoveall(char *src, char *to_del, int option)
{
    int i;
    int j;
    int go_to;
    char    *new;
    
    i = 0;
    j = 0;
    if (!to_del || !*to_del || !src || !*src || del_in(src, to_del, i) == -1)
        return (manage_heap(src, to_del, option), src);
    new = malloc(sizeof(char) * (ft_strlen(src) - (ft_strlen(to_del) * x_str(src, to_del)) + 1));
    if (!new)
        return (NULL);
    while ((go_to = del_in(src + i, to_del, i)) != -1)
    {
         while (i < go_to)
            new[j++] = src[i++];
        i += ft_strlen(to_del);
    }
    while (src[i])
        new[j++] = src[i++];
    new[j] = '\0';
    manage_heap(src, to_del, option);
    return (new);
}

/*int main()
{
    char    *src = "apr je aprenapr apres";
    char    *to_del = "apr";
    
    char    *removed = ft_strremoveall(src, to_del, 0);
    printf("removed = %s", removed);
    free(removed);
}*/