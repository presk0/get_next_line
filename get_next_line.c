/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/10/21 13:30:08 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned int	ii;

	ii = 0;
	while (ii < n)
	{
		*((char *) s + ii) = '\0';
		ii++;
	}
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size * count / size != count)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

int	refresh_line(int fd, char *buff, char **next_line)
{
	char		*last_line;
	int			read_val;

	last_line = *next_line;
	if (*next_line)
		*next_line = ft_strjoin(*next_line, buff);
	else
		*next_line =ft_substr(buff, 0, ft_strlen(buff) + 1);
	read_val = read(fd, buff, BUFFER_SIZE);
	if (last_line)
	{
		free(last_line);
		last_line = NULL;
	}

	return (read_val);
}

char	*format_buff(char *buff)
{
	char	*return_car;
	char	*next_line;

	return_car = ft_strchr(buff, '\n');
	next_line = ft_substr(buff, 0, return_car - buff + 1);
	if (return_car)
		ft_strlcpy(buff, return_car + 1, BUFFER_SIZE);
	return (next_line);
}

char	*load_buff(int fd, char **buff)
{
	int		read_val;
	char	*next_line;

	read_val = 1;
	next_line = NULL;
	while (!ft_strchr(next_line, '\n') && read_val > 0)
		read_val = refresh_line(fd, *buff, &next_line);
	if (read_val <= 0)
	{
		if (*buff)
		{
			free(*buff);
			*buff = NULL;
		}
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*next_line;

	if (!buff)
	{
		buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buff)
			return (NULL);
	}
	if (!ft_strchr(buff, '\n'))
	{
		next_line = load_buff(fd, &buff);
	}
	else
		next_line = format_buff(buff);
	if (*next_line == '\0')
	{
		free(next_line);
		next_line = NULL;
	}
	return (next_line);
}
