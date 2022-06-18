# include "tmp.h"

void	free_alist(t_alist *head)
{
	t_alist	*next;
	while (head)
	{
		next = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = next;
	}
}

t_alist *rm_alist(t_alist *head, const char *key)
{
	t_alist	*prev;
	t_alist	*cur;

	if (head == NULL || key == NULL)
		return (NULL);
	prev = head;
	cur = head;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			prev->next = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			break;
		}
		cur = cur->next;
		prev = cur;
	}
	return (head);
}

t_alist	*search_alist(t_alist *head, const char *key)
{
	t_alist	*cur;

	cur = head;
	while (cur)
	{
		if (ft_strcmp(key, cur->key) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

t_alist	*update_alist(t_alist *head, const char *key, const char *value)
{
	t_alist	*target;

	if (head == NULL)
		return (NULL);
	target = search_alist(head, key);
	if (target == NULL)
		return (NULL);
	free(target->value);
	target->value = ft_strdup(value);
	if (target->value == NULL)
		exit(1);
	return (head);
}

t_alist	*add_new_alist(t_alist *head, const char *key, const char *value)
{
	t_alist	*new;
	t_alist *tail;

	if (search_alist(head, key))
		return (update_alist(head, key, value));
	new = malloc(sizeof(t_alist));
	if (new == NULL)
		exit(1);
	new->next = NULL;
	new->key = ft_strdup(key);
	if (new->key == NULL)
		exit(1);
	new->value = ft_strdup(value);
	if (new->value == NULL)
		exit(1);
	if (head == NULL)
		return (new);
	tail = head;
	while (tail->next)
		tail = tail->next;
	tail->next = new;
	return (head);
}
