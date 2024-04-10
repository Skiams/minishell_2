/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:46:34 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/10 17:49:36 by eltouma          ###   ########.fr       */
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
	*lst = NULL;
}

void    ft_list_remove_if(t_garbage **lst, void *data_ref)
{
        t_garbage       *prev;
        t_garbage       *current;

        if (!*lst)
                return ;
        prev = NULL;
        current = *lst;
        while (current->next != NULL)
        {       
                if (!ft_strcmp(data_ref, current->ptr))
                {
                        if (!prev)
                                *lst = current->next;
                        prev->next = current->next;
                        free(current);
                        break ;
                }       
                prev = current;
                current = current->next;
        }
}

t_garbage	*ft_lstnew_garbage(void *content)
{
	t_garbage	*new_node;

	new_node = malloc(sizeof(t_garbage));
	if (!new_node)
		return (NULL);
	new_node->ptr = content;
	new_node->next = NULL;
	return (new_node);
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
	if (rule == FREE)
		ft_list_remove_if(&garbage, p);
	if (rule == FREE_ALL)
		ft_lstclear_garbage(&garbage);
	return (NULL);
}
