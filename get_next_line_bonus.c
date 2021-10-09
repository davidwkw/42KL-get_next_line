/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 14:47:13 by kwang             #+#    #+#             */
/*   Updated: 2021/06/07 14:47:13 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*init_static(char **str)
{
	if (*str == NULL)
		*str = ft_strndup("", 0);
	return (*str);
}

static int	store_readbuff(int fd, t_line *line_obj)
{
	(*line_obj).read_bytes = read(fd, (*line_obj).line_buff, BUFFER_SIZE);
	if ((*line_obj).read_bytes >= 0)
		(*line_obj).line_buff[(*line_obj).read_bytes] = '\0';
	return ((*line_obj).read_bytes);
}

static void	store_endline(t_line *line_obj, char **read_str)
{
	char	*temp;

	temp = ft_substr((*line_obj).p_end, 1, ft_strlen((*line_obj).p_end) - 1);
	free(*read_str);
	*read_str = temp;
}

static int	store_prevline(t_line *line_obj, char **read_str, char **line)
{
	if ((*line_obj).read_bytes == -1)
	{
		free(*read_str);
		*read_str = NULL;
		return (-1);
	}
	(*line_obj).p_end = ft_strchr(*read_str, '\n');
	if (!(*line_obj).p_end)
		(*line_obj).p_end = ft_strchr(*read_str, '\0');
	*line = ft_strndup(*read_str, (*line_obj).p_end - *read_str);
	if (ft_strchr(*read_str, '\n'))
	{
		store_endline(line_obj, read_str);
		return (1);
	}
	free(*read_str);
	*read_str = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	t_line		line_obj;
	static char	*read_str[OPEN_MAX];
	char		*temp;

	if (fd == -1 || !line || fd >= OPEN_MAX)
		return (-1);
	read_str[fd] = init_static(&read_str[fd]);
	while (!(ft_strchr(read_str[fd], '\n')) && store_readbuff(fd, &line_obj) > 0)
	{
		temp = ft_strjoin(read_str[fd], line_obj.line_buff);
		free(read_str[fd]);
		read_str[fd] = temp;
	}
	return (store_prevline(&line_obj, &read_str[fd], line));
}
