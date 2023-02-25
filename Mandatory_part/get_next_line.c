/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:08:21 by ebennix           #+#    #+#             */
/*   Updated: 2023/02/25 08:41:04 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_restbuff(char *buff)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free (buff);
		return (NULL);
	}
	str = (char *) malloc ((ft_strlen(buff)) - i + 1 * sizeof(char));
	if (!str)
		return (NULL);
	if (buff[i] && buff[i] == '\n')
	{
		i++;
		while (buff[i])
			str[j++] = buff[i++];
		str[j] = '\0';
	}
	free (buff);
	return (str);
}

static char	*ft_getline(char *buff)
{
	char	*line;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		line = (char *) malloc (i + 2 * sizeof(char));
	else
		line = (char *) malloc (i + 1 * sizeof(char));
	if (!line)
		return (NULL);
	i = -1;
	while (buff[++i] && buff[i] != '\n')
		line[i] = buff[i];
	if (buff[i] == '\n')
	{
		line[i] = buff[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_readit(int fd, char *buff)
{
	char	*line;
	int		i;

	line = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 1;
	while (!ft_strchr(buff, '\n') && i > 0)
	{
		i = read(fd, line, BUFFER_SIZE);
		if (i == -1)
		{
			free (line);
			if (buff)
				free (buff);
			return (NULL);
		}
		line[i] = '\0';
		buff = ft_strjoin(buff, line);
	}
	free (line);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_readit(fd, buff);
	if (!buff)
		return (NULL);
	line = ft_getline(buff);
	buff = ft_restbuff(buff);
	return (line);
}

int main (void)
{
	int fd =open("Lorem", O_RDONLY);
	while(1)
	{
		char *line = get_next_line(fd);
		printf ("%s",line);
		free(line);
		if(!line)
			break;
	}
	return(0);
}