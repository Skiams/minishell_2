/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:46:34 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/10 13:12:59 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstclear_garbage(t_garbage **lst)
{
	t_garbage	*temp;

	if (!*lst)
		return ;
	while ((*lst)->next)
	{
		free((*lst)->ptr);
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	// free((*lst)->ptr);
	// free(*lst);
	*lst = NULL;
}

// t_garbage	*ft_lstlast_garbage(t_garbage *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }

void	ft_list_remove_if(t_garbage **begin_list, void *data_ref)
{
	t_garbage	*node;

	if (!*begin_list)
		return ;
	node = *begin_list;
	if (!ft_strcmp(data_ref, node->ptr))
	{
		*begin_list = node->next;
		free(node);
		ft_list_remove_if(begin_list, data_ref);
	}
	else
	{
		node = *begin_list;
		ft_list_remove_if(&node->next, data_ref);
	}
}

t_garbage	*ft_lstnew_garbage(void *content)
{
	t_garbage	*newel;

	newel = malloc(sizeof(t_garbage));
	if (!newel)
		return (NULL);
	newel->ptr = content;
	newel->next = NULL;
	return (newel);
}

void	*ft_lstadd_back_garbage(t_garbage **lst, t_garbage *new)
{
	t_garbage   *head;

	head = *lst;
	if (*lst)
	{
		while ((*lst)->next != NULL)
			*lst = (*lst)->next;
		(*lst)->next = new;
		*lst = head;
	}
	else
		*lst = new;
	return (new->ptr);
}

void    *ft_garbage(int rule, void *p)
{
	static t_garbage	*garbage = NULL;
	t_garbage   *new;

	if (!p && (rule == ADD || rule == FREE))
		return (NULL);
	new = ft_lstnew_garbage(p);
	if (!new)
		return (NULL);
	if (rule == ADD)
		return(ft_lstadd_back_garbage(&garbage, new));
		//ft_lstadd_back_garbage(&garbage, new);
	if (rule == FREE)
		ft_list_remove_if(&garbage, p);
	if (rule == FREE_ALL)
	{
		ft_lstclear_garbage(&garbage);
	}
	return (NULL);
}
