/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:08:21 by ebennix           #+#    #+#             */
/*   Updated: 2022/12/19 21:39:34 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_restbuff(char *buff)
{
	char *str;
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return NULL;
	}
	str = (char *) malloc ((ft_strlen(buff)) - i + 1 * sizeof(char));
	if (!str)
	{
		// free (str);
		return NULL;
	}
	if (buff[i] && buff[i] == '\n')
	{
		i++;
		while (buff[i])
		{
			str[j] = buff[i];
			j++;
			i++;
		}
		str[j] = '\0';
	}
	free (buff);
	return (str);
}

char *ft_getline(char *buff)
{
	char *line;
	int i;

	i = 0;
	if (!buff[i])
		return NULL;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		line = (char *) malloc(i + 2 * sizeof(char));
	else
		line = (char *) malloc(i + 1 * sizeof(char));
	if(!line)
	{
		// free(line);
		return NULL;
	}
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
	{
		line [i] = buff[i];
		i++;
	}
	line [i] = '\0';
	return(line);
}

char    *ft_readit(int fd, char *buff)
{
    char	*line;
    int	read_bytes;

    line = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!line)
        return (NULL);
    read_bytes = 1;
    while (read_bytes > 0)
    {
        read_bytes = read(fd, line, BUFFER_SIZE);
		// if (read_bytes == 0)
		// {
		// 	free (line);
		// 	line = NULL;
		// 	break;
		// }
        if (read_bytes == -1)
        {
            free(line);
            return (NULL);
        }
        line[read_bytes] = '\0';
        buff = ft_strjoin(buff, line);
		if (ft_strchr(buff,'\n'))
			break ;
    }
    free(line);
    return (buff);
}
// char *ft_readit(int fd , char *buff)
// {
// 	char *line;
// 	int i;
// 	// char *tmp;
	
// 	// if (!buff)
// 	//     buff = ft_calloc(1,1);
// 	line = calloc (BUFFER_SIZE + 1 , sizeof(char));
// 	if (!line)
// 		return NULL;
// 	i = 1;
// 	while(i > 0)
// 	{
// 		i = read(fd, line, BUFFER_SIZE);
// 		if (i == 0)
// 		{
// 			free (line);
// 			line = NULL;
// 			break;
// 		}
// 		if (i == -1)
// 		{
// 			free (line);
// 			return NULL;
// 		}
// 		line[i] = '\0';
// 		// tmp = buff;
// 		buff = ft_strjoin(buff , line);
// 		// free(tmp);
// 		if (ft_strchr(buff,'\n'))
// 			break ;
// 	}
// 	free(line);
// 	return (buff);
// }

char *get_next_line(int fd)
{
	static char *buff;
	char *line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL ;
	buff = ft_readit(fd , buff);
	if (!buff)
		return NULL;
	line = ft_getline(buff);
	buff = ft_restbuff(buff);
	return (line);
}

// int main (void)
// {
// 	int fd =open("testnl.txt", O_RDONLY);
// 	char *line = get_next_line(fd);
// 	int i=0;
// 	while(i < 5)
// 	{
// 		printf ("%s",line);
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	return(0);
// }