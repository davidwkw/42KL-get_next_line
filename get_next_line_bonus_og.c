/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 22:28:52 by kwang             #+#    #+#             */
/*   Updated: 2021/06/06 22:28:52 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*init_static(char **str)
{
	if (*str == NULL)
		*str = ft_strndup("", 0);
	return (*str);
}

int	store_readbuff(int fd, t_line *l_obj)
{
	(*l_obj).read_bytes = read(fd, (*l_obj).buff, BUFFER_SIZE);
	if ((*l_obj).read_bytes >= 0)
		(*l_obj).buff[(*l_obj).read_bytes] = '\0';
	return ((*l_obj).read_bytes);
}

void	store_endline(t_line *l_obj, char **r_str)
{
	char	*temp;

	temp = ft_substr((*l_obj).p_end, 1, ft_strlen((*l_obj).p_end) - 1);
	free(*r_str);
	*r_str = temp;
}

int	get_next_line(int fd, char **line)
{
	t_line		l_obj;
	static char	*r_str[OPEN_MAX];
	char		*temp;

	if (fd == -1 || !line)
		return (-1);
	r_str[fd] = init_static(&r_str[fd]);
	while (!(ft_strchr(r_str[fd], '\n')) && store_readbuff(fd, &l_obj) > 0)
	{
		temp = ft_strjoin(r_str[fd], l_obj.buff);
		free(r_str[fd]);
		r_str[fd] = temp;
	}
	if (l_obj.read_bytes == -1)
	{
		free(r_str[fd]);
		r_str[fd] = NULL;
		return (-1);
	}
	l_obj.p_end = ft_strchr(r_str[fd], '\n');
	if (!l_obj.p_end)
		l_obj.p_end = ft_strchr(r_str[fd], '\0');
	*line = ft_strndup(r_str[fd], l_obj.p_end - r_str[fd]);
	if (ft_strchr(r_str[fd], '\n'))
	{
		store_endline(&l_obj, &r_str[fd]);
		return (1);
	}
	free(r_str[fd]);
	r_str[fd] = NULL;
	return (0);
}