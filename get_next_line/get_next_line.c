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

#include "get_next_line.h"

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
	static char	*str;
	char		*buf;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{	
		free(str);
		str = NULL;
		return (NULL);
	}
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	tmp = NULL;
	str = ft_read(fd, buf, tmp, str);
	if (str == NULL)
		return (NULL);
	line = ft_before(str);
	str = ft_after(str);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("tests/text2.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	//system("leaks a.out");
	return (0);
}
*/