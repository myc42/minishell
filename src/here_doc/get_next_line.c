/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:58:53 by macoulib          #+#    #+#             */
/*   Updated: 2025/10/15 19:24:50 by macoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*freestat(char *staticbuffer, char *buffer)
{
	char	*temp;

	if (!staticbuffer)
		return (ft_strdup(buffer));
	temp = ft_strjoin(staticbuffer, buffer);
	free(staticbuffer);
	return (temp);
}

char	*readfile(int fd, char *staticbuffer)
{
	char	*buffer;
	int		byteread;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	byteread = 1;
	while (byteread > 0)
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		if (byteread == -1)
			return (free(buffer), NULL);
		buffer[byteread] = 0;
		staticbuffer = freestat(staticbuffer, buffer);
		if (!staticbuffer)
			return (free(buffer), NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), staticbuffer);
}

char	*definedline(char *staticbuffer)
{
	size_t	i;
	size_t	slashexiste;
	char	*line;

	i = 0;
	slashexiste = 0;
	if (staticbuffer[i] == '\0')
		return (NULL);
	while (staticbuffer[i] != '\n' && staticbuffer[i])
		i++;
	if (staticbuffer[i++] == '\n')
		slashexiste = 1;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (staticbuffer[i] != '\n' && staticbuffer[i])
	{
		line[i] = staticbuffer[i];
		i++;
	}
	if (slashexiste)
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*therest(char *staticbuffer)
{
	size_t	i;
	size_t	j;
	char	*therest;

	i = 0;
	j = 0;
	while (staticbuffer[i] && staticbuffer[i] != '\n')
		i++;
	if (!staticbuffer[i])
	{
		free(staticbuffer);
		return (NULL);
	}
	i++;
	therest = malloc((ft_strlen(staticbuffer) - i) + 1);
	if (!therest)
		return (NULL);
	while (staticbuffer[i])
	{
		therest[j++] = staticbuffer[i++];
	}
	therest[j] = '\0';
	free(staticbuffer);
	return (therest);
}

char	*get_next_line(int fd)
{
	static char	*staticbuffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	staticbuffer = readfile(fd, staticbuffer);
	if (!staticbuffer)
		return (NULL);
	line = definedline(staticbuffer);
	staticbuffer = therest(staticbuffer);
	return (line);
}
/*
 int main() {
	int fd = open("read_error.txt", O_RDONLY);

		char *line;
while	((line = get_next_line(fd)) != NULL)
{
	printf("%s", line);
	free(line);
}

	close(fd);
	return (0);
 } */