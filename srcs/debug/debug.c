/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:28:44 by ahayon            #+#    #+#             */
/*   Updated: 2024/02/29 19:11:32 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokens(t_token *token_lst)
{
	int	i;

	i = 1;
	while (token_lst->next != NULL)
	{
		printf("Token %d / type = %d / value = %s\n",
			i, token_lst->type, token_lst->value);
		token_lst = token_lst->next;
		i++;
	}
}
