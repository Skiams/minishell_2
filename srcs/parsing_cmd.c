/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:14:01 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/08 18:10:38 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_new_cmd(t_data *data, t_token **token_lst)
{
	t_cmd	*new_cmd;

	if (!(*token_lst)->prev || (*token_lst)->type == PIPE)
	{
		new_cmd = ft_lstnew_cmd();
		if (!new_cmd)
			return (false);
		if ((*token_lst)->type == PIPE)
			(*token_lst) = (*token_lst)->next;
	}
	return (true);
}
bool	ft_set_cmd(t_data *data, t_token **token_lst)
{
	t_token	*token;

	token = *token_lst;
	while (token)
	{
		if (!ft_new_cmd(data, &token))
			return (false);
		if ((!token->prev && token->type == WORD) || (token->prev->type >= PIPE && token->type = WORD))
			
	}
}