/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_small.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 11:37:18 by kwang             #+#    #+#             */
/*   Updated: 2021/06/07 11:37:18 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	init_static(char **str)
{
	if (*str == NULL)
		*str = ft_strndup("", 0);
}

static int	store_readbuff(int fd, t_line *l_obj)
{
	l_obj->read_bytes = read(fd, l_obj->buff, BUFFER_SIZE);
	if (l_obj->read_bytes >= 0)
		l_obj->buff[l_obj->read_bytes] = '\0';
	return (l_obj->read_bytes);
}

static void	store_endline(t_line *l_obj, char **r_str)
{
	char	*temp;

	temp = ft_substr(l_obj->p_end, 1, ft_strlen(l_obj->p_end) - 1);
	free(*r_str);
	*r_str = temp;
}

static int	store_prevline(t_line *l_obj, char **line)
{
	if (l_obj->read_bytes == -1)
	{
		free(l_obj->r_str);
		l_obj->r_str = NULL;
		return (-1);
	}
	l_obj->p_end = ft_strchr(l_obj->r_str, '\n');
	if (!l_obj->p_end)
		l_obj->p_end = ft_strchr(l_obj->r_str, '\0');
	if (l_obj->l_temp)
		free(*line);
	l_obj->l_temp = ft_strndup(l_obj->r_str, l_obj->p_end - l_obj->r_str);
	*line = l_obj->l_temp;
	if (ft_strchr(l_obj->r_str, '\n'))
	{
		store_endline(l_obj, &l_obj->r_str);
		return (1);
	}
	free(*line);
	free(l_obj->r_str);
	l_obj->r_str = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static t_line	l_obj = {.l_temp = NULL};
	static char		*r_str = NULL;
	char			*temp;

	if (fd == -1 || !line || BUFFER_SIZE < 0)
		return (-1);
	init_static(&l_obj.r_str);
	while (!(ft_strchr(l_obj.r_str, '\n')) && store_readbuff(fd, &l_obj) > 0)
	{
		temp = ft_strjoin(l_obj.r_str, l_obj.buff);
		free(l_obj.r_str);
		l_obj.r_str = temp;
	}
	return (store_prevline(&l_obj, line));
}