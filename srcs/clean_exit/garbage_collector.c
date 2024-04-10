/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:46:34 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/10 19:09:12 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_lstclear_garbage(t_garbage **lst)
// {
// 	t_garbage	*temp;

// 	if (!*lst)
// 		return ;
// 	while ((*lst)->next)
// 	{
// 		free((*lst)->ptr);
// 		temp = (*lst)->next;
// 		free(*lst);
// 		*lst = temp;
// 	}
// 	// free((*lst)->ptr);
// 	// free(*lst);
// 	*lst = NULL;
// }

// // t_garbage	*ft_lstlast_garbage(t_garbage *lst)
// // {
// // 	if (!lst)
// // 		return (NULL);
// // 	while (lst->next)
// // 		lst = lst->next;
// // 	return (lst);
// // }

// void	ft_list_remove_if(t_garbage **begin_list, void *data_ref)
// {
// 	t_garbage	*node;

// 	if (!*begin_list)
// 		return ;
// 	node = *begin_list;
// 	if (!ft_strcmp(data_ref, node->ptr))
// 	{
// 		*begin_list = node->next;
// 		free(node);
// 		ft_list_remove_if(begin_list, data_ref);
// 	}
// 	else
// 	{
// 		node = *begin_list;
// 		ft_list_remove_if(&node->next, data_ref);
// 	}
// }

// t_garbage	*ft_lstnew_garbage(void *content)
// {
// 	t_garbage	*newel;

// 	newel = malloc(sizeof(t_garbage));
// 	if (!newel)
// 		return (NULL);
// 	newel->ptr = content;
// 	newel->next = NULL;
// 	return (newel);
// }

// void	*ft_lstadd_back_garbage(t_garbage **lst, t_garbage *new)
// {
// 	t_garbage   *head;

// 	head = *lst;
// 	if (*lst)
// 	{
// 		while ((*lst)->next != NULL)
// 			*lst = (*lst)->next;
// 		(*lst)->next = new;
// 		*lst = head;
// 	}
// 	else
// 		*lst = new;
// 	return (new->ptr);
// }

// void    *ft_garbage(int rule, void *p)
// {
// 	static t_garbage	*garbage = NULL;
// 	t_garbage   *new;

// 	if (!p && (rule == ADD || rule == FREE))
// 		return (NULL);
// 	new = ft_lstnew_garbage(p);
// 	if (!new)
// 		return (NULL);
// 	if (rule == ADD)
// 		return(ft_lstadd_back_garbage(&garbage, new));
// 		//ft_lstadd_back_garbage(&garbage, new);
// 	if (rule == FREE)
// 		ft_list_remove_if(&garbage, p);
// 	if (rule == FREE_ALL)
// 	{
// 		ft_lstclear_garbage(&garbage);
// 	}
// 	return (NULL);
// }

static void	*ft_garbage_add_mlc(t_data *data, t_list **mlc, int rule, t_garbage *p)
{
	t_list	*head;
	t_list	*tmp;

	head = *mlc;
	if (rule == MALLOC)
		tmp = ft_lstnew_malloc(p->size);
	else
		tmp = ft_lstnew_add(p->addr);
	if (!tmp)
		return (write(2, "minishell: Cannot allocate memory\n", 35),
			ft_exit_code(12, ADD), NULL);
	if (*mlc)
	{
		while ((*mlc)->next)
			(*mlc) = (*mlc)->next;
		(*mlc)->next = tmp;
		*mlc = head;
	}
	else
		*mlc = tmp;
	free(p);
	return (tmp->content);
}

static void	ft_clearlst(int lst, t_list **mlc, t_list **mlc_env)
{
	if (lst == DATALST)
		ft_lstclear(mlc, del);
	else if (lst == ENVLST)
		ft_lstclear(mlc_env, del);
}

static void	ft_clearall(t_list **mlc, t_list **mlc_env)
{
	ft_lstclear(mlc, del);
	ft_lstclear(mlc_env, del);
}

/*
size == 1 => signifie regle ADD select
*/
t_garbage	*mlcp(void *addr, size_t size)
{
	t_garbage	*param;

	if (!addr && size == 0)
		return (NULL);
	param = malloc(sizeof(t_garbage));
	if (!param)
	{
		if (size == 1 && addr)
			free(addr);
		return (NULL);
	}
	param->addr = addr;
	param->size = size;
	return (param);
}

void    *ft_garbage(t_garbage *p, int rule, int whichlst, t_data *data)
{
	static t_list	*lst_data;
	static t_list	*lst_env;

	if (!p && (rule == ADD || rule == FREE))
		return (NULL);
    if (rule == ADD) 
	{
		if (whichlst = DATALST)
		{
			//ajoute le pointeur a liste chainee
			lst_data = p;
			if (!lst_data)
		
        // si alloc faile pour creer node => free(p) + garbagge (3 , NULL) + exit
    }
    else if (rule == FREE)
        //free le pointeur passe en parametre => supprimer le node de la liste chainee + free le ptr
        free(p); // => dans lst
    else if (rule == FREELST)
        free la whichlist entiere
    else // rule == 4
        //free toutes les liste chainee
        free(lst);
    return (0);
}
