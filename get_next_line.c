/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/10/22 15:16:43 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	while (*src && dstsize > 1)
	{
		*(dst++) = *(src++);
		dstsize--;
	}
	if (dstsize)
		*dst = '\0';
	return (src_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*return_val;

	if (!s)
		return (NULL);
	substr = (char *) malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (start--)
	{
		if (!*s++)
		{
			substr[0] = '\0';
			return (substr);
		}
	}
	return_val = substr;
	while (len-- && *s)
		*substr++ = *s++;
	*substr = '\0';
	return (return_val);
}

char	*ft_strchr(const char *str, int c)
{
	if (str)
	{
		while (*str != (char)c)
		{
			if (!*str)
				return (NULL);
			str++;
		}
	}
	else
		return (NULL);
	return ((char *)str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			len_s1;
	unsigned int	i;
	char			*ret;

	if (!s1)
		return (NULL);
	i = 0;
	len_s1 = ft_strlen((char *) s1);
	ret = (char *) malloc(sizeof(char) * (ft_strlen((char *) s2) + len_s1 + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[i - len_s1])
	{
		ret[i] = s2[i - len_s1];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

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
		else
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
		if (read_val >= 0)
			(*buff)[read_val] = '\0';
		if (read_val)
			append_line(*buff, &next_line);
		else if (*buff && !**buff)
		{
			free(*buff);
			*buff = NULL;
		}
	}
	if (read_val <= 0 && !*next_line)
	{
		free(next_line);
		next_line = NULL;
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
	return (next_line);
}
