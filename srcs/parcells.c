/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcells.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:21:55 by ahayon            #+#    #+#             */
/*   Updated: 2024/02/29 14:04:58 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_lstlast_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
	{
		token = token->next;
	}
	return (token);
}

void	ft_lstadd_back_token(t_token **token_lst, t_token *new_token)
{
	t_token	*lastelem;

	if (!token_lst || !new_token)
		return ;
	lastelem = ft_lstlast_token(*token_lst);
	if (lastelem == NULL)
		*token_lst = new_token;
	else
		lastelem->next = new_token;
}

t_token	*ft_lstnew_token(char *value, t_token_tp type)
{
	t_token	*newel;

	newel = malloc(sizeof(t_token));
	if (!newel)
		return (NULL);
	newel->value = value;
	newel->type = type;
	newel->next = NULL;
	newel->prev = NULL;
	return (newel);
}
