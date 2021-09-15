/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:32:58 by kwang             #+#    #+#             */
/*   Updated: 2021/05/25 11:32:58 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int get_next_line(int fd, char **line)
{
	int 		read_bytes;
	char 		buff[BUFFER_SIZE + 1];
	static char	*read_chars = "";
	char 		*end;

	if (fd == -1 || !line)
		return (-1);
	read_bytes = read(fd, buff, BUFFER_SIZE);
	while (read_bytes > 0)
	{
		buff[read_bytes] = '\0';
		read_chars = ft_strjoin(read_chars, buff);
		read_bytes = read(fd, buff, BUFFER_SIZE);
	}
	if (read_bytes == -1)
		return (-1);
	end = ft_strchr(read_chars, '\n');
	if (end)
	{
		*line = ft_strndup(read_chars, end - read_chars);
		read_chars = end + 1;
		return (1);
	}
	end = ft_strchr(read_chars, '\0');
	*line = ft_strndup(read_chars, end - read_chars);
	return (0);
}