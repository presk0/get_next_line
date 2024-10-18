/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/10/18 15:58:08 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	refresh_line(int fd, char *buff, char **next_line)
{
	char		*last_line;
	int			read_val;

	last_line = *next_line;
	*next_line = ft_strjoin(*next_line, buff);
	read_val = read(fd, buff, BUFFER_SIZE);
	if (last_line)
		free(last_line);
	return (read_val);
}

void	format_buff(char *buff)
{
	char	*return_car;

	return_car = ft_strchr(buff, '\n');
	if (return_car)
		ft_strlcpy(buff, return_car, BUFFER_SIZE);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*next_line;
	int			read_val;

	if (!buff)
		buff = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buff)
		return (NULL);
	else
		buff[BUFFER_SIZE] = '\0';
	next_line = NULL;
	if (!ft_strchr(buff, '\n'))
	{
		read_val = 1;
		while (!ft_strchr(buff, '\n') && read_val)
			read_val = refresh_line(fd, buff, &next_line);
	}
	if (!ft_strchr(buff, '\n'))
	{
		if (*buff == '\0')
			return (NULL);
		return (next_line);
	}
	format_buff(buff);
	return (next_line);
}
/*
#include <stdio.h>

void	get_next_line_tester(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((line = get_next_line(fd)))
			printf("%s\n", line);
		close(fd);
	}
	else	
		printf("Usage: %s <file>\n", argv[0]);
}
int	main(int argc, char **argv)
{
	get_next_line_tester(argc, argv);
	return (0);
}
*/
