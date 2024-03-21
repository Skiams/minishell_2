/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:37:39 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/21 16:38:29 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_token_lstclear(t_token **token_lst, void (*del)(void *))
{
	t_token	*temp;

	if (!token_lst || !del)
		return ;
	while (*token_lst)
	{
		temp = (*token_lst)->next;
		(*del)((*token_lst)->value);
		free (*token_lst);
		*token_lst = temp;
	}
	*token_lst = NULL;
}

void	ft_free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	ft_free_data(t_data *data)
{
	if (data && data->input)
		ft_free_ptr(data->input);
	if (data && data->token_list)
		ft_token_lstclear(&data->token_list, &ft_free_ptr);
}

int    ft_garbage(int rule, void *p, int whichlst)
{
    static void	*lst_env;
    static void	*lst_exec_parsing;

    if (rule == 1) 
	{
		
        //ajoute le pointeur a liste chainee
        lst = p;
        // si alloc faile pour creer node => free(p) + garbagge (3 , NULL) + exit
    }
    else if (rule == 2)
        //free le pointeur passe en parametre => supprimer le node de la liste chainee + free le ptr
        free(p); // => dans lst
    else if (rule == 3)
        free la whichlist entiere
    else // rule == 4
        //free toutes les liste chainee
        free(lst);
    return (0);
}
