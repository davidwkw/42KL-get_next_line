#include "get_next_line.h"
#include <stdio.h>

static char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	ch;

	i = 0;
	ch = (char)c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i++;
	}
	if (!c && s[i] == ch)
		return ((char *)s + i);
	return (NULL);
}

ssize_t read_append_buffer(int fd, char **read_string)
{
    char    buffer[BUFFER_SIZE + 1];
    ssize_t read_bytes;
    char    *joined_string;

    read_bytes = read(fd, buffer, BUFFER_SIZE);
    printf("read bytes %ld\n", read_bytes);
    if (read_bytes <= 0)
        return (read_bytes);
    buffer[read_bytes] = '\0';
    joined_string = ft_strjoin(*read_string, buffer);
    free(*read_string);
    *read_string = joined_string;
    return (read_bytes);
}

void free_string(char **str)
{
    free(*str);
    *str = NULL;
}

char *get_next_line(int fd)
{
    static char     *read_str = NULL;
    t_gnl_data      gnl_data;

    gnl_data = (t_gnl_data){};
    if (read_str && *read_str)
        gnl_data.p_brk = ft_strchr(read_str, '\n');
    while (gnl_data.p_brk == NULL)
    {
        gnl_data.read_bytes = read_append_buffer(fd, &read_str);
        if (gnl_data.read_bytes <= 0 && read_str && *read_str)
        {
            gnl_data.p_brk = ft_strchr(read_str, '\0');
            break;
        }
        else if (gnl_data.read_bytes <= 0)
        {
            free_string(&read_str);
            return NULL;
        }
        gnl_data.p_brk = ft_strchr(read_str, '\n');
    }
    gnl_data.result_str = ft_substr(read_str, 0, gnl_data.p_brk - read_str + 1);
    gnl_data.temp = ft_strdup(gnl_data.p_brk + !!(*gnl_data.p_brk));
    free_string(&read_str);
    read_str = gnl_data.temp;
    return (gnl_data.result_str);
}
