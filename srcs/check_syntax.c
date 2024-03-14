/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:43:49 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/14 21:10:40 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_syntax(t_data *data, char *str)
{
	t_token	*token;
	char	*value;

	token = data->token_list;
	while (token)
	{
		if (!token->prev && token->type == PIPE)
			return (ft_syntax_error(token->type), false);
		else if (token->type < PIPE || (token->type == PIPE && token->prev && token->prev->type == PIPE))
		{
			if (token->next->type < PIPE)
				return (ft_syntax_error(token->next->type), false);
		}
		else if (token->type < PIPE && !token->next)
			return (ft_syntax_error("newline"), false);
	}
	return (true);
}