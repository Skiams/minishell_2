/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:54:11 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/08 15:36:08 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ft_lstnew_cmd(void)
{
	t_cmd	*newel;

	newel = malloc(sizeof(t_cmd));
	if (!newel)
		return (NULL);
	newel->value = NULL;
	newel->args = NULL;
	newel->next = NULL;
	newel->prev = NULL;
	return (newel);
}

t_cmd	*ft_lstlast_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

void	ft_lstadd_back_cmd(t_cmd **cmd_lst, t_cmd *new_cmd)
{
	t_cmd	*lastelem;

	if (!cmd_lst || !new_cmd)
		return ;
	lastelem = ft_lstlast_cmd(*cmd_lst);
	if (lastelem == NULL)
		*cmd_lst = new_cmd;
	else
		lastelem->next = new_cmd;
}