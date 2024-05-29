/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_hd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:09:58 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/28 21:14:17 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_hd	*lst_new_hd(char *name)
{
	t_hd	*node;

	node = (t_hd *)malloc(sizeof(t_hd));
	if (!node)
		return (NULL);
	node->hdname = ft_strdup(name);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	lst_add_back_hd(t_hd **hd_lst, t_hd *hd)
{
	t_hd	*start;

	start = *hd_lst;
	if (!start)
	{
		*hd_lst = hd;
		return ;
	}
	if (hd_lst && *hd_lst && hd)
	{
		while (start->next)
			start = start->next;
		start->next = hd;
		hd->prev = start;
	}
}

t_hd	*ft_last_hd(t_hd *hd)
{
	while (hd->next)
		hd = hd->next;
	return (hd);
}

void	ft_lstdelone_hd(t_hd *hd, void (*del)(void *))
{
	if (hd->hdname)
	{
		unlink(hd->hdname);
		(*del)(hd->hdname);
	}
	(*del)(hd);
}

void	ft_lstclear_hd(t_hd **hd_lst, void (*del)(void *))
{
	t_hd	*temp;

	temp = NULL;
	while (*hd_lst)
	{
		temp = (*hd_lst)->next;
		ft_lstdelone_hd(*hd_lst, del);
		*hd_lst = temp;
	}
}