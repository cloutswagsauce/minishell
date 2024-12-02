/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaria-m <lfaria-m@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:47:57 by lfaria-m          #+#    #+#             */
/*   Updated: 2024/11/20 13:51:08 by lfaria-m         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# define HEX_UPPER "0123456789ABCDEF"

# define HEX_LOWER "0123456789abcdef"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memmove(void *dst, void *src, size_t len);
void		*ft_memchr(void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strncat(char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
int			ft_atoi(const char *str);
int			ft_isalnum(int c);
char		*get_next_line(int fd);
int			ft_printf(const char *format, ...);
int			print_hex(unsigned int n, int uppercase);
int			print_u(unsigned int n);
int			print_s(char *str);
int			print_p(void *p);
int			print_di(int n);

#endif