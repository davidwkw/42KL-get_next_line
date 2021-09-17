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

static void	init_static(char **str)
{
	if (*str == NULL)
		*str = ft_strndup("", 0);
}

static int	store_readbuff(int fd, t_line *l_obj)
{
	(*l_obj).read_bytes = read(fd, (*l_obj).buff, BUFFER_SIZE);
	if ((*l_obj).read_bytes >= 0)
		(*l_obj).buff[(*l_obj).read_bytes] = '\0';
	return ((*l_obj).read_bytes);
}

static void	store_endline(t_line *l_obj, char **r_str)
{
	char	*temp;

	temp = ft_substr((*l_obj).p_end, 1, ft_strlen((*l_obj).p_end) - 1);
	free(*r_str);
	*r_str = temp;
}

static int	store_prevline(t_line *l_obj, char **r_str, char **line)
{
	if ((*l_obj).read_bytes == -1)
	{
		free(*r_str);
		*r_str = NULL;
		return (-1);
	}
	(*l_obj).p_end = ft_strchr(*r_str, '\n');
	if (!(*l_obj).p_end)
		(*l_obj).p_end = ft_strchr(*r_str, '\0');
	if (l_obj->l_temp)
		free(*line);
	l_obj->l_temp = ft_strndup(*r_str, (*l_obj).p_end - *r_str);
	*line = l_obj->l_temp;
	if (ft_strchr(*r_str, '\n'))
	{
		store_endline(l_obj, r_str);
		return (1);
	}
	free(*r_str);
	*r_str = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static t_line	l_obj = {.l_temp = NULL};
	char			*temp;

	if (fd == -1 || !line || fd >= OPEN_MAX)
		return (-1);
	init_static(&l_obj.r_str[fd]);
	while (!(ft_strchr(l_obj.r_str[fd], '\n')) && store_readbuff(fd, &l_obj) > 0)
	{
		temp = ft_strjoin(l_obj.r_str[fd], l_obj.buff);
		free(l_obj.r_str[fd]);
		l_obj.r_str[fd] = temp;
	}
	return (store_prevline(&l_obj, &l_obj.r_str[fd], line));
}