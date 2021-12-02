/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:03:52 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/02 21:24:55 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef int	t_bool;

void	ft_swap(int *a, int *b);
void	ft_sort_int_tab(int *tab, int size);
void	*ft_memset(void *s, int c, unsigned long int n);
void	ft_bzero(void *s, unsigned long int n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *s);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putchar_fd(char c, int fd);
void	ft_putchar(char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr(char *s);
void	ft_putstr_limited(char *s, int i);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);
int		ft_countnbr(int n);
void	ft_putnbr_no_minus(int n);
void	ft_putnbr_base(unsigned int nbr, char *base);
void	ft_putnbr_base_pointer(unsigned long int nbr, char *base);
int		ft_countnbr_base(unsigned int nbr, char *base);
void	ft_putnbr_unsigned_int(unsigned int n);
int		ft_countnbr_unsigned_int(unsigned int n);
int		ft_countnbr_base_pointer(unsigned long int nbr, char *base);
t_bool	ft_str_insert(char **str1, char *str2, size_t position);
void	ft_free_split(char **ptr);
size_t	ft_strlen_split(char **s);
t_bool	ft_split_n_join(char **str, char c);

#endif
