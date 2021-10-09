#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		printf("%s\n", line);
	printf("%s\n", line);
}