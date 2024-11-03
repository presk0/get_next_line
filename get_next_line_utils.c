/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/11/03 20:15:16 by nidionis         ###   ########.fr       */
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

char	*ft_strjoin(char *s1, char *s2)
{
	size_t			len_s1;
	unsigned int	i;
	char			*ret;

	if (!s1)
		return (NULL);
	i = 0;
	len_s1 = ft_strlen(s1);
	ret = malloc(sizeof(char) * (ft_strlen(s2) + len_s1 + 1));
	if (!ret)
		return (NULL);
	i = 0;
	if (s1)
		while (i < len_s1)
			ret[i++] = *s1++;
	if (s2)
	{
		while (s2[i - len_s1])
		{
			ret[i] = s2[i - len_s1];
			i++;
		}
	}
	ret[i] = '\0';
	return (ret);
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
