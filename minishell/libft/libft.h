/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:27:57 by cogata            #+#    #+#             */
/*   Updated: 2024/05/15 13:23:45 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_flags
{
	char			character;
	char			status;
	int				count;
}					t_flags;

typedef struct s_word
{
	char			*s;
	int				count_letters;
	int				i;
	int				j;
}					t_word;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_atoi(const char *nptr);
long long			ft_atol(char *str);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

char				*get_next_line(int fd);
char				*ft_read_file(char *buffer, char *next_line, int fd);
char				*ft_get_next_line(char *next_line);
char				*ft_get_line(char *next_line);
int					ft_count_len(char *next_line);
void				free_next_line(char **next_line);

int					ishex(char c);
int					ft_atoi_base(char *str);

int					ft_put_and_count_char(char c);
int					ft_put_and_count_str(char *s);
int					ft_int_to_char(int nb);
int					ft_put_and_count_nbr(int nb);
int					ft_unsigned_putnbr(unsigned int nb);
int					ft_base10_to_base16(unsigned long int nb, char type);
void				find_format(va_list *args, const char *format, int *i,
						int *count);
int					ft_printf(const char *format, ...);
char				*ft_strndup(char *s, size_t n);
t_list				**get_mem_address(void);
t_list				**get_env_address(void);
void				collect_mem(void *content);
void				collect_env_mem(char **env_table);
void				*allocate_mem(size_t nmemb, size_t size);
void				free_mem(t_list **list);
void				ft_put_strjoin_fd(char *str1, char *str2, int fd);
void				init_quote_structs(t_flags *sing_quote,
						t_flags *doub_quote);
void				is_quote(t_flags *quote, char c, int count_flag,
						int *count_word);
void				is_delimiter(int single_count_quote, int double_count_quote,
						int *count_flag, int *count_word);
void				is_word(int *count_word, int *count_flag);
int					ft_modified_count_words(char *s, char delimiter);
void				is_quote_letter(char *first_status, char second_status,
						int *count_letters);
void				check_character(t_flags *sing, t_flags *doub,
						int *count_letters, char c);
void				ft_count_letters(char *s, char **words, char delimiter,
						int count_word);
void				is_quote_init_letter(char **words, t_word *aux,
						t_flags *first, t_flags *second);
void				check_and_init_letters(char **words, t_word *aux,
						t_flags *sing, t_flags *doub);
void				ft_init_modified_words(char *s, char **words,
						char delimiter, int count_word);
char				**remove_quotes(char *s, char delimiter);

#endif