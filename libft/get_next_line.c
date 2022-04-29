/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: milan <milan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 16:38:22 by milan         #+#    #+#                 */
/*   Updated: 2022/04/28 18:38:21 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <limits.h>

static char	*ft_split_line(char *save)
{
	char	*temp;
	int		i;

	i = 0;
	if ((unsigned int)gnl_stop_newline(save) < gnl_strlen(save))
	{
		temp = malloc(ft_strlen(save) - gnl_stop_newline(save));
		if (!temp)
			return (NULL);
		while (((unsigned int)(i + gnl_stop_newline(save)) < gnl_strlen(save)))
		{
			temp[i] = save[gnl_stop_newline(save) + i + 1];
			i++;
		}
		free(save);
		save = gnl_strdup(temp);
		free(temp);
	}
	else
		save = NULL;
	return (save);
}

char	*ft_get_line(char *save, char *line)
{
	if ((unsigned int)gnl_stop_newline(save) < gnl_strlen(save))
		line = gnl_substr(save, 0, (gnl_stop_newline(save) + 1));
	else
		line = save;
	return (line);
}

static char	*ft_thisline(char *buff, char *save)
{
	char	*temp;

	if (save)
	{
		temp = gnl_strjoin(save, buff);
		free(save);
		save = gnl_strdup(temp);
		free(temp);
	}
	else
		save = gnl_strdup(buff);
	if (save == NULL)
		free(save);
	return (save);
}

static char	*ft_get_save(char *save, int fd)
{
	char	buff[BUFFER_SIZE + 1];
	int		ret;

	ret = 1;
	while (ret > 0)
	{
		if (save)
			if (gnl_stop_newline(save) != -1)
				break ;
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		buff[ret] = '\0';
		save = ft_thisline(buff, save);
		if (save == NULL)
			return (NULL);
	}
	if (ret == 0 && gnl_strlen(save) == 0)
	{
		free(save);
		return (NULL);
	}
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;

	line = NULL;
	if ((fd < 0 && fd <= OPEN_MAX) || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = ft_get_save(save[fd], fd);
	if (save[fd])
	{
		line = ft_get_line(save[fd], line);
		save[fd] = ft_split_line(save[fd]);
	}
	return (line);
}
