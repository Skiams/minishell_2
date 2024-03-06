/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:37:39 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/06 14:32:45 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
