
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:03:26 by supersko          #+#    #+#             */
/*   Updated: 2024/10/16 15:05:56 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef X_H
# define X_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


void	*ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		refresh_line(int fd, char *buff, char **next_line);
char	*format_buff(char *buff);
char	*load_buff(int fd, char **buff);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	get_next_line_tester(int argc, char **argv);

#endif
