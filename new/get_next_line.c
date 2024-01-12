#include "get_next_line.h"

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
    if (read_bytes <= 0)
        return (read_bytes);
    buffer[read_bytes] = '\0';
    joined_string = ft_strjoin(*read_string, buffer);
    free(*read_string);
    *read_string = joined_string;
    return (read_bytes);
}

char *get_next_line(int fd)
{
    static char     *read_string = NULL;
    ssize_t         read_bytes = 0;
    char            *break_ptr = NULL;
    char            *temp;
    char            *result_string;

    if (read_string && *read_string)
        break_ptr = ft_strchr(read_string, '\n');
    while (break_ptr == NULL)
    {
        read_bytes = read_append_buffer(fd, &read_string);
        if (read_bytes <= 0 && ft_strlen(read_string) > 0)
        {
            break_ptr = ft_strchr(read_string, '\0');
            break;
        }
        else if (read_bytes <= 0)
        {
            free(read_string);
            read_string = NULL;
            return NULL;
        }
        break_ptr = ft_strchr(read_string, '\n');
    }
    result_string = ft_substr(read_string, 0, break_ptr - read_string + 1);
    temp = ft_strdup(break_ptr + !!(*break_ptr));
    free(read_string);
    read_string = temp;
    return (result_string);
}
