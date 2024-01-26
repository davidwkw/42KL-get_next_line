# pragma once

# ifndef __GET_NEXT_LINE_H__

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_gnl_data {
    ssize_t         read_bytes;
    char            *p_brk;
    char            *temp;
    char            *result_str;
}   t_gnl_data;

char    *get_next_line(int fd);

char    *ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);

# endif
