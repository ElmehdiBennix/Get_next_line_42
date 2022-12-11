/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:08:21 by ebennix           #+#    #+#             */
/*   Updated: 2022/12/11 22:59:03 by ebennix          ###   ########.fr       */
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
	str = ft_calloc ((ft_strlen(buff)) - i, sizeof(char));
	if (!str)
	{
		free (str);
		return (NULL);
	}
	if (buff[i] && buff[i] == '\n')
	{
		i++;
		while (buff[i])
			str[j++] = buff[i++];
	}
	free (buff);
	return (str);
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
	{
		free (line);
		return NULL;
	}
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		line [i] = '\n';
	return(line);
}

char *ft_readit(int fd , char *buff)
{
	char *line;
	int i;
	char *tmp;
	
	// if (!buff)
	//     buff = ft_calloc(1,1);
	line = ft_calloc (BUFFER_SIZE + 1 , sizeof(char));
	if (!line)
		return NULL;
	i = 1;
	while(i > 0)
	{
		i = read(fd, line, BUFFER_SIZE);
		if (i == 0)
		{
			free(line);
			line = NULL;
			break;
		}
		if (i == -1)
		{
			free(line);
			return NULL;
		}
		tmp = buff;
		buff = ft_strjoin(buff , line);
		free(tmp);
		if (ft_strchr(buff,'\n'))
			break ;
	}
	free (line);
	return (buff);
}

char *get_next_line(int fd)
{
	static char *buff;
	char *line;

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
// 	int fd =open("test.txt", O_RDONLY);
// 	char *line = "";
// 	while(line)
// 	{
// 		line = get_next_line(fd);
// 		printf ("|%s|\n",line);
// 	}
// 	// printf ("|%s|\n",get_next_line(fd));
// 	// printf ("|%s|\n",get_next_line(fd));

// 	return(0);
// }