#include "inc/get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int		fd;
    char	*line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}