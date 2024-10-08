/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <ahmetabdullahcan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 02:06:14 by acan              #+#    #+#             */
/*   Updated: 2024/08/30 17:23:16 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line_bonus.h"

char	*find_line(int fd, char *text)
{
	int		rdcount;
	char	*buf;

	rdcount = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (rdcount != 0 && !hasnlornull(text))
	{
		rdcount = read(fd, buf, BUFFER_SIZE);
		if (rdcount < 0)
		{
			free(buf);
			free(text);
			return (NULL);
		}
		buf[rdcount] = '\0';
		text = buf_to_text(text, buf);
	}
	free(buf);
	return (text);
}

char	*seperate_line(char *text)
{
	int		i;
	char	*ret;
	int		j;

	i = 0;
	if (!*text)
		return (NULL);
	while (text[i] != '\n' && text[i])
		i++;
	i++;
	ret = (char *)malloc(i + 1);
	j = -1;
	while (++j < i)
		ret[j] = text[j];
	ret[j] = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*text[10240];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 10240)
		return (NULL);
	text[fd] = find_line(fd, text[fd]);
	if (!text[fd])
		return (NULL);
	line = seperate_line(text[fd]);
	text[fd] = cut_line(text[fd]);
	return (line);
}
