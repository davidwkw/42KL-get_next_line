#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;
	size_t			str_len;

	if (!s)
		return (NULL);
	str_len = strlen(s);
	if (start > str_len)
		return strdup("");
	if (len > str_len - start)
		len = str_len - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (substr);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static int  calculatejoinedLength(char const *s1, char const *s2)
{
    int length;

    length = 0;
    if (s1)
        length += strlen(s1);
    if (s2)
        length += strlen(s2);
    return (length);
}

char	    *ft_strjoin(char const *s1, char const *s2)
{
	char			*joinedstr;
	unsigned int	i;
	unsigned int	j;
    int             joinedLength;

    joinedLength = calculatejoinedLength(s1, s2);
	joinedstr = malloc(sizeof(char) * (joinedLength + 1));
	if (!joinedstr)
		return (joinedstr);
	i = 0;
	while (s1 && s1[i])
	{
		joinedstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		joinedstr[i + j] = s2[j];
		j++;
	}
	joinedstr[i + j] = '\0';
	return (joinedstr);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	dup = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dup)
		return (dup);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
