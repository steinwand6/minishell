#ifndef TMP_H
# define TMP_H

#include "libft/libft.h"

typedef struct s_alist {
	char			*key;
	char			*value;
	struct s_alist	*next;
}	t_alist;

char	*ft_strndup(char const *src, size_t n);
int	ft_strcmp(const char *s1, const char *s2);
void	free_alist(t_alist *head);
t_alist *rm_alist(t_alist *head, const char *key);
t_alist	*search_alist(t_alist *head, const char *key);
t_alist	*add_new_alist(t_alist *head, const char *key, const char *value);

#endif
