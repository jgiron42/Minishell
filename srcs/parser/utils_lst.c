#include "minishell.h"

t_token_list	*ft_lstnew(t_token_type	 token)
{
	t_token_list *new;

	if (!(new = (t_token_list *)malloc(sizeof(t_token_list))))
		return (NULL);
	new->arg = NULL;
	new->type = token;
	new->nb = NONE;
	new->next = NULL;
	return (new);
}

t_token_list	*ft_lstcpy(t_token_list	 *current)
{
	t_token_list	 *cpy;

	cpy = ft_lstnew(current->type);
	cpy->arg = (current)->arg;
	return (cpy);
}
