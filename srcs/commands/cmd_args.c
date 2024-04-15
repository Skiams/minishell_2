/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:15:47 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/15 20:04:36 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_args(t_token *token_list)
{
	ft_printf(2, "count args\n");	
	t_token	*tmp;
	int	i;

	tmp = token_list;
	i = 0;
	while (tmp && tmp->type == WORD)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static bool	ft_add_args(t_token **token_list, t_cmds *last_cmd, int *index)
{
	while (*token_list && ((*token_list)->type == WORD))
	{
		last_cmd->args[*index] = ft_strdup((*token_list)->value);
		if (!last_cmd->args[*index])
			return (ft_exit_code(12, ADD), false);
		*token_list = (*token_list)->next;
		(*index)++;
	}
	return (true);
}

bool	ft_set_args(t_cmds *last_cmd, t_token **token_list)
{
	t_token	*tmp;
	int		nb;
	int		i;
	
	i = 0;
	tmp = *token_list;
	nb = ft_count_args(tmp);
	last_cmd->args = malloc(sizeof(char *) * nb + 2);
	if (!last_cmd->args)
		return (ft_exit_code(12, ADD), false);
	last_cmd->args[i] = ft_strdup(last_cmd->cmd);
	if (!last_cmd->args[i])
		return (ft_exit_code(12, ADD), false);
	i++;
	// while (*token_list && (*token_list)->type == WORD)
	// {
	// 	last_cmd->args[i] = ft_strdup((*token_list)->value);
	// 	if (!last_cmd->args[i])
	// 		return (ft_exit_code(12, ADD), false);
	// 	i++;
	// 	*token_list = (*token_list)->next;
	// }
	if (!ft_add_args(&tmp, last_cmd, &i))
	last_cmd->args[i] = NULL;
	*token_list = tmp;
	return (true);
}
