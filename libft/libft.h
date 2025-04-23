/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:17:32 by uzyberaj          #+#    #+#             */
/*   Updated: 2025/04/23 01:07:05 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <ctype.h>
# include <limits.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdarg.h>

# define FLAGS	"-+ #0"
# define NUMBERS	"0123456789"
# define SPECIFIERS	"cspdiuxXb%"
# define LOWER_SYMBOLS	"0123456789abcdef"
# define UPPER_SYMBOLS	"0123456789ABCDEF"

typedef union union_int
{
	unsigned long	uint64;
	long			int64;
}	t_union_int;

typedef enum e_error
{
	OK = 0,
	MALLOC_ERROR = -1337,
	PARSE_ERROR = -42,
}	t_error;

typedef enum e_base
{
	BASE_2 = 2,
	BASE_8 = 8,
	BASE_10 = 10,
	BASE_16 = 16,
}	t_base;

typedef struct s_format
{
	bool	left_justify;
	bool	zero;
	bool	plus;
	bool	space;
	bool	hash;
	int		width;
	int		precision;
	char	specifier;
	char	tmp_buffer[64];
	int		nbr_len;
	bool	uppercase;
	t_base	base;
	int		padding_spaces;
	int		padding_zeros;
	bool	is_negative;
	bool	is_converted;
	bool	signed_value;
}	t_format;

typedef struct s_data
{
	const char	*s;
	va_list		ap;
	int			chars_written;
	char		*buffer;
	int			buffer_index;
	t_format	format;
}	t_data;

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}				t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *src);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putendl_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_itoa(int num);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);
void	ft_free_double_tab(char ***tab);
int		found_newline(t_list *list);
t_list	*find_last_node(t_list *list);
char	*get_line(t_list *list);
void	copy_str(t_list *list, char *str);
int		len_to_newline(t_list *list);
void	polish_list(t_list **list);
char	*get_next_line(int fd);
void	dealloc(t_list **list, t_list *clean_node, char *buf);
void	create_list(t_list **list, int fd);
int		ft_printf(const char *format, ...);
void	my_memset(void *ptr, unsigned char value, size_t n);
bool	my_strchr(const char *s, char c);
int		parse_format(t_data *data);
void	flush_buffer(t_data *data);
void	write_buffer(t_data *data, char c);
void	putchar_buffer(char c, int precision, t_data *data);
void	print_char(t_data *data, int c);
void	putstr_buffer(char *s, int precision, t_data *data);
int		my_strlen(const char *s);
void	print_str(t_data *data, char *s);
void	itoa_base(t_data *data, t_union_int int_values);
void	set_padding_zeros(t_data *data);
void	set_padding_spaces(t_data *data);
void	print_int(t_data *data, t_union_int int_values);

#endif