/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/11/03 19:54:06 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*pop_line(char *buff)
{
	char	*return_car;
	char	*line;

	line = NULL;
	return_car = ft_strchr(buff, '\n');
	if (!return_car)
	{
		line = ft_substr(buff, 0, ft_strlen(buff) + 1);
		*buff = '\0';
	}
	else
	{
		line = ft_substr(buff, 0, return_car - buff + 1);
		ft_strlcpy(buff, return_car + 1, BUFFER_SIZE);
	}
	return (line);
}

char	*load_until_line(int fd, char **buff)
{
	int		read_val;
	char	*next_line;
	char	*tmp;
	char	*lfb;

	read_val = 1;
	next_line = pop_line(*buff);
	while (!ft_strchr(next_line, '\n') && read_val > 0)
	{
		read_val = read(fd, *buff, BUFFER_SIZE);
		if (read_val >= 0)
		{
			(*buff)[read_val] = 0;
			lfb = pop_line(*buff);
			tmp = ft_strjoin(next_line, lfb);
			free(lfb);
			lfb = NULL;
			free(next_line);
			next_line = NULL;
			next_line = tmp;
		}
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buff)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buff)
			return (NULL);
		*buff = '\0';
	}
	next_line = NULL;
	if (!ft_strchr(buff, '\n'))
		next_line = load_until_line(fd, &buff);
	else
		next_line = pop_line(buff);
	if (!*next_line)
	{
		free(next_line);
		return (NULL);
	}
	return (next_line);
}
