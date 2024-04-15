/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:37:39 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/15 12:48:00 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_free_env(t_env **env, void (*del)(void *))
// {
// 	t_env	*temp;

// 	if (!*env || !*del)
// 		return ;
// 	temp = *env;
// 	while (temp->next != NULL)
// 	{
// 		(*del)(temp->var);
// 		(*del)(temp->value);
// 		temp = temp->next;
// 		free (temp->prev);
// 		temp->prev = NULL;
// 	}
// 	temp = NULL;
// }

void	ft_free_env(t_env *env)
{
	t_env	*temp;

	if (!env)
		return ;
	while (env != NULL)
	{
		temp = env->next;
		if (env->var != NULL)
			free(env->var);
		if (env->value != NULL)
			free(env->value);
		free(env);
		env = temp;
	}
	env = NULL;
}

void	ft_token_lstclear(t_token **token_lst, void (*del)(void *))
{
	t_token	*temp;

	temp = NULL;
	if (!*token_lst || !*del)
		return ;
	while (*token_lst)
	{
		temp = (*token_lst)->next;
		(*del)((*token_lst)->value);
		free (*token_lst);
		*token_lst = NULL;
		*token_lst = temp;
	}
	*token_lst = NULL;
}

void	ft_free_ptr(void *ptr)
{
	if (!ptr)
		return ;
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	ft_free_data(t_data *data)
{
	if (data && data->input)
	{
		ft_free_ptr(data->input);
		data->input = NULL;
	}
	if (data && data->token_list)
	{
		ft_token_lstclear(&data->token_list, &ft_free_ptr);
		data->token_list = NULL;
	}
	if (data && data->cmd_list)
		ft_lstclear_cmd(&data->cmd_list, &ft_free_ptr);
}

void	ft_clean_all(t_data *data)
{
	ft_free_data(data);
	if (data && data->env)
		ft_free_env(data->env);
	rl_clear_history();
}
