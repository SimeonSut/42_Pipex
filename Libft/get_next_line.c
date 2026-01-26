/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:23:06 by ssutarmi          #+#    #+#             */
/*   Updated: 2026/01/26 16:35:48 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*addline(int fd, char *line)
{
	int		i;
	char	*tmp;
	int		bytes;

	i = 0;
	bytes = 1;
	if (!line)
		return (NULL);
	while (line[i] != '\n')
	{
		tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!tmp)
			return (free(line), NULL);
		bytes = (int)read(fd, tmp, BUFFER_SIZE);
		if (bytes == -1)
			return (free(tmp), free(line), NULL);
		tmp[bytes] = '\0';
		line = ft_freejoin(line, tmp);
		if (!line || bytes == 0)
			return (line);
		i = 0;
		while (line[i] && line[i] != '\n')
			i++;
	}
	return (line);
}

char	*ft_nextline(char *str, int i)
{
	int		j;
	char	*line;

	j = i;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (i--)
		line[i] = str[i];
	i = 0;
	if (str[j] == '\0' && j > 0)
		return (str[i] = '\0', line);
	else if (str[j] == '\0' && j == 0)
		return (free(str), free(line), NULL);
	while (str[j])
		str[i++] = str[j++];
	return (str[i] = '\0', line);
}

char	*get_next_line(int fd)
{
	static char	*center[1024];
	char		*output;
	int			i;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!center[fd])
		center[fd] = ft_strdup("");
	center[fd] = addline(fd, center[fd]);
	if (!center[fd])
		return (NULL);
	i = 0;
	while (center[fd][i] && center[fd][i] != '\n')
		i++;
	if (center[fd][i] == '\n')
		output = ft_nextline(center[fd], ++i);
	else if (center[fd][i] == '\0' && i > 0)
		output = ft_nextline(center[fd], i);
	else
		return (NULL);
	if (!output)
		return (NULL);
	return (output);
}
/*
int	main(void)
{
	int	fd1;
	int	fd2;
	int	fd3;
	char	*line;
	
	fd1 = open("input.txt", O_RDONLY);
	printf("START of input.txt\n", fd1);
	while ((line = get_next_line(fd1)))
	{
		printf("%s", line);
		free(line);
	}
	printf("END OF input.txt\n");
	fd2 = open("nl.txt", O_RDONLY);
	printf("START of nl.txt\n", fd2);
	while ((line = get_next_line(fd2)))
        {
                printf("%s", line);
                free(line);
        }
	printf("\nEND OF nl.txt\n");
	fd3 = open("empty.txt", O_RDONLY);
        printf("START of empty.txt\n", fd3);
        while ((line = get_next_line(fd3)))
                printf("%s", line);
        printf("END OF empty.txt\n");
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/
