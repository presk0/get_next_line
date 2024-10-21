/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/10/21 13:17:09 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

void	tester(int argc, char **argv)
{
	int		fd;
	char	*line;
	static char	buff[BUFFER_SIZE] = {0};

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((line = load_buff(fd, (char **)&buff)))
		{
			printf("%s", line);
			free(line);
			line = NULL;
		}
		close(fd);
	}
	else	
		printf("Usage: %s <file>\n", argv[0]);
}

void	get_next_line_tester(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((line = get_next_line(fd)))
		{
			printf("%s", line);
			free(line);
			line = NULL;
		}
		close(fd);
	}
	else	
		printf("Usage: %s <file>\n", argv[0]);
}

int	main(int argc, char **argv)
{
	//tester(argc, argv);
	get_next_line_tester(argc, argv);
	return (0);
}
