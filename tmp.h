#ifndef TMP_H
# define TMP_H

#include <stdio.h>
#include <errno.h>

#include "libft/libft.h"

// PATH_MAXの2倍
#define MAX_PATHSIZE 8192

typedef struct s_info {
	int		last_result;
	char	pwd[MAX_PATHSIZE];
}	t_info;

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
int	builtin_cd(const char *path);
int builtin_pwd();

#endif
