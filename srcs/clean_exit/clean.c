/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:37:39 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/04 15:43:53 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_env(t_env **env, void (*del)(void *))
{
	t_env	*temp;

	if (!env || !del)
		return ;
	while (*env)
	{
		temp = (*env)->next;
		(*del)((*env)->var);
		(*del)((*env)->value);
		free (*env);
		*env = temp;
	}
	*env = NULL;
}
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

void	ft_clean_all(t_data *data)
{
	ft_free_data(data);
	if (data && data->env)
		ft_free_env(&data->env, &ft_free_ptr);
	if (data)
		free(data);
}

// int    ft_garbage(int rule, void *p, int whichlst)
// {
// 	t_garb_data	*garb_data;
// 	t_garb_env	*env;
//     static void	*lst_env;
//     static void	*lst_data;

//     if (rule == ADD) 
// 	{
// 		if (whichlst = DATALST)
// 		{
// 			//ajoute le pointeur a liste chainee
// 			lst_data = p;
// 			if (!lst_data)
		
//         // si alloc faile pour creer node => free(p) + garbagge (3 , NULL) + exit
//     }
//     else if (rule == FREE)
//         //free le pointeur passe en parametre => supprimer le node de la liste chainee + free le ptr
//         free(p); // => dans lst
//     else if (rule == FREELST)
//         free la whichlist entiere
//     else // rule == 4
//         //free toutes les liste chainee
//         free(lst);
//     return (0);
// }
