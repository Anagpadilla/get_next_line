/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anagarc4 <anagarc4@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:15:52 by anagarc4          #+#    #+#             */
/*   Updated: 2023/04/10 14:16:04 by anagarc4         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_before(const char *str)
{
	int		i;
	char	*ptr;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	ptr = malloc((i + 1 + 1) * (sizeof(char)));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		ptr[i] = '\n';
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_after(char *str)
{
	int		i;
	int		n;
	char	*ptr;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		ft_free(str);
		return (NULL);
	}
	n = ft_strlen(str);
	ptr = malloc((n - i) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	n = 0;
	i++;
	while (str[i] != '\0')
		ptr[n++] = str[i++];
	ptr[n] = '\0';
	ft_free(str);
	return (ptr);
}

int	ft_newline(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_read(int fd, char *buf, char *tmp, char *str)
{
	int	bytes_read;

	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buf[bytes_read] = '\0';
		tmp = str;
		if (tmp == NULL)
		{
			tmp = malloc(sizeof(char));
			if (tmp == NULL)
				return (NULL);
			tmp[0] = '\0';
		}
		str = ft_strjoin(tmp, buf);
		ft_free(tmp);
		if (!str)
			return (NULL);
		if (ft_newline(str) == 1 || bytes_read == 0)
			break ;
	}
	ft_free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*buf;
	char		*line;
	char		*tmp;

	if (fd <= -1 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd >= OPEN_MAX)
	{	
		free(str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	tmp = NULL;
	str[fd] = ft_read(fd, buf, tmp, str[fd]);
	if (str[fd] == NULL)
		return (NULL);
	line = ft_before(str[fd]);
	str[fd] = ft_after(str[fd]);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>

#define MAX_FD 256

int main()
{
    int fds[3];
    char *line;
    int i;

    fds[0] = open("tests/test1.txt", O_RDONLY);
    if (fds[0] == -1)
    {
        perror("open");
        return 1;
    }
    fds[1] = open("tests/test2.txt", O_RDONLY);
    if (fds[1] == -1)
    {
        perror("open");
        close(fds[0]);
        return 1;
    }
    fds[2] = open("tests/test3.txt", O_RDONLY);
    if (fds[2] == -1)
    {
        perror("open");
        close(fds[0]);
        close(fds[1]);
        return 1;
    }

    for (i = 0; i < 3; i++)
    {
        while ((line = get_next_line(fds[i])) != NULL)
        {
            printf("%s\n", line);
            free(line);
        }

        if (line == NULL)
        {
            printf("End of file %d\n", fds[i]);
        }
        else
        {
            printf("An error occurred %d.\n", fds[i]);
            free(line);
        }
    }

    close(fds[0]);
    close(fds[1]);
    close(fds[2]);
    return 0;
}
*/