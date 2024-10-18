/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/10/17 13:40:15 by nidionis         ###   ########.fr       */
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
	while (*str != (char)c)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return ((char *)str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			len_s1;
	unsigned int	ii;
	char			*ret;

	ii = 0;
	len_s1 = ft_strlen((char *) s1);
	ret = (char *) malloc(sizeof(char) * (ft_strlen((char *) s2) + len_s1 + 1));
	if (!ret)
		return (NULL);
	ii = 0;
	while (ii < len_s1)
	{
		ret[ii] = s1[ii];
		ii++;
	}
	while (s2[ii - len_s1])
	{
		ret[ii] = s2[ii - len_s1];
		ii++;
	}
	ret[ii] = '\0';
	return (ret);
}

/*
//
#include <stdio.h>
#include <string.h>
#include "libft.h"
// MAIN
int main(void)
{
	char s1[1000];
	char s2[1000];
	char *verif;

	strcpy(s1, "ch1 ");
	strcpy(s2, "ch2");
	verif = ft_strjoin(s1, s2);
	if (ft_strncmp(verif, "ch1 et ch2", 20))
	{
		printf("Pb at ft_strjoin\n");
	}
	free(verif);
}
*/
