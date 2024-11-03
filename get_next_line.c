/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/11/03 15:39:18 by nidionis         ###   ########.fr       */
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

char	*ft_strdup(const char *s1)
{
	int		i;
	int		s_len;
	char	*scpy;

	s_len = ft_strlen(s1);
	scpy = (char *) calloc(sizeof(char), s_len + 1);
	if (!scpy)
		return ((char *) 0);
	i = 0;
	while (i < s_len)
	{
		scpy[i] = s1[i];
		i++;
	}
	return (scpy);
}

char	*line_from_buff(char *buff)
{
	char	*return_car;
	char	*line;

	line = NULL;
	return_car = ft_strchr(buff, '\n');
	if (!return_car)
		return_car = ft_strlen(buff) + buff;
	if (buff)
		line = ft_substr(buff, 0, return_car - buff + 1);
	return (line);
}

void	append_line(char *buff, char **next_line)
{
	char		*last_line;
	char		*new_line;;

	last_line = *next_line;
	new_line = line_from_buff(buff);
	if (*next_line)
		*next_line = ft_strjoin(*next_line, new_line);
	else
		*next_line = ft_strdup(new_line);
	if (last_line)
	{
		free(last_line);
		last_line = NULL;
	}
	free(new_line);
	new_line = NULL;
}

void	format_buff(char *buff)
{
	char	*return_car;

	if (buff)
	{
		return_car = ft_strchr(buff, '\n');
		if (return_car)
			ft_strlcpy(buff, return_car + 1, BUFFER_SIZE);
		else if (buff && *buff)
			ft_bzero(buff, BUFFER_SIZE);
	}
}

char	*load_until_line(int fd, char **buff)
{
	int		read_val;
	char	*next_line;

	read_val = 1;
	next_line = NULL;
	append_line(*buff, &next_line);
	while (!ft_strchr(next_line, '\n') && read_val > 0)
	{
		read_val = read(fd, *buff, BUFFER_SIZE);
		(*buff)[read_val] = '\0';
		append_line(*buff, &next_line);
		//format_buff(*buff);
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	if (!buff)
	{
		buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buff)
			return (NULL);
	}
	next_line = NULL;
	if (!ft_strchr(buff, '\n'))
		next_line = load_until_line(fd, &buff);
	else
		next_line = line_from_buff(buff);
	format_buff(buff);
	if (next_line)
		if (!*buff && !*next_line)
		{
			free(buff);
			buff = NULL;
			free(next_line);
			next_line = NULL;
		}
	return (next_line);
}
