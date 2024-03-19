/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:28:44 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/19 13:34:19 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokens(t_token *token_lst)
{
	t_token	*tmp;
	int		i;

	tmp = token_lst;
	i = 1;
	while (tmp)
	{
		dprintf(2, "Token %d / type = %d / value = %s\n",
			i, tmp->type, tmp->value);
		tmp = tmp->next;
		i++;
	}
}

void	print_env(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp)
	{
		dprintf(2, "env var = %s / value = %s\n",
			tmp->var, tmp->value);
		tmp = tmp->next;
	}
}

// void	print_cmd(t_cmd *cmd_lst)
// {
// 	int	i;

// 	i = 1;
// 	while (cmd_lst)
// 	{
// 		printf("cmd %d / value = %s / args = %s\n",
// 			i, cmd_lst->value, &cmd_lst->args);
// 		cmd_lst = cmd_lst->next;
// 		i++;
// 	}
// }
