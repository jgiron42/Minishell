/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:35:41 by ereali            #+#    #+#             */
/*   Updated: 2021/05/30 18:54:46 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp && del)
	{
		tmp = tmp->next;
		del((void *)((*lst)->content));
		free((void *)(*lst));
		*lst = tmp;
	}
	*lst = NULL;
}
