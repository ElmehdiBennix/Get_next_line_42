/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:08:21 by ebennix           #+#    #+#             */
/*   Updated: 2022/12/09 04:18:09 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_joinem(char *buff , char *line)
{
    char *tmp;
    tmp = ft_strjoin(buff,line);
    free (line);
    return(tmp);
}

char *ft_getline(char *buff)
{
    char *line;
    int i;

    i = 0;
    while (buff[i] && buff[i] != '\n')
        i++;
    line = ft_calloc(i + 2 , sizeof(char));
    if(!line)
        return NULL;
    i = 0;
    while (buff[i] && buff[i] != '\n')
    {
        line[i] = buff[i];
        i++;
    }
    if (buff[i] && buff[i] == '\n')
    {
        line [i++] = '\n';
        line [i] = '\0';
    }
    return(line);
}

char *ft_readit(int fd , char *buff)
{
    char *line;
    int i;

    if (!buff)
        buff = (char *) malloc (1);
    line = ft_calloc (BUFFER_SIZE + 1 , sizeof(char));
    if (!line)
        return NULL ;
    i = 1;
    while(i > 0)
    {
        i = read(fd, line, BUFFER_SIZE);
        if (i == -1)
        {
            free(line);
            return NULL;
        }
        line[i + 1]= '\0';
        buff = ft_joinem(buff , line);
        if(ft_strchr(buff,'\n'))
            break;
    }
    free(line);
    return (buff);
}

char *ft_restbuff(char *buff)
{
    char *str;
    int i;
    int j;

    i = 0;
    j = 0;
    
    while (buff[i] && buff[i] != '\n')
        i++;
    if (buff[i] && buff[i] == '\n')
    {
        while (buff[i])
        {
            str[j++] = buff[i++];
        }
        str[j] = '\0';
    }
    return (str);
}

char *get_next_line(int fd)
{
    static char *buff;
    char *save;
        
    if (fd < 3)
        return NULL ;
    buff = ft_readit(fd , buff);
    if (!buff)
        return NULL;
    save = ft_getline(buff);
    buff = ft_restbuff(buff);
    return (save);
}

// int main (void)
// {
//     int fd =open("test.txt", O_RDONLY);
//     printf ("%s",get_next_line(fd));
//     return(0);
// }