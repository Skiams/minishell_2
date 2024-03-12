/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:28:44 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/11 16:35:56 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokens(t_token *token_lst)
{
	int	i;

	i = 1;
	while (token_lst)
	{
		printf("Token %d / type = %d / value = %s\n",
			i, token_lst->type, token_lst->value);
		token_lst = token_lst->next;
		i++;
	}
}

void	print_cmd(t_cmd *cmd_lst)
{
	int	i;

	i = 1;
	while (cmd_lst)
	{
		printf("cmd %d / value = %s / args = %s\n",
			i, cmd_lst->value, &cmd_lst->args);
		cmd_lst = cmd_lst->next;
		i++;
	}
}
