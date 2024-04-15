/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:54:36 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/15 16:53:15 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmds	*lst_new_cmd(void)
{
	t_cmds	*node;

	node = (t_cmds *)malloc(sizeof(t_cmds));
	if (!node)
		return (NULL);
	node->cmd = NULL;
	node->args = NULL;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	lst_add_back_cmd(t_cmds **cmd_lst, t_cmds *cmd)
{
	t_cmds	*start;

	start = *cmd_lst;
	if (!start)
	{
		*cmd_lst = cmd;
		return ;
	}
	if (cmd_lst && *cmd_lst && cmd)
	{
		while (start->next)
			start = start->next;
		start->next = cmd;
		cmd->prev = start;
	}
}

t_cmds	*ft_last_cmd(t_cmds *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

static void	ft_lstdelone_cmd(t_cmds *cmd, void (*del)(void *))
{
	if (cmd->cmd)
		(*del)(cmd->cmd);
	if (cmd->args)
		ft_free_tab(cmd->args);
	(*del)(cmd);
}

void	ft_lstclear_cmd(t_cmds **cmd_lst, void (*del)(void *))
{
	t_cmds	*temp;

	temp = NULL;
	while (*cmd_lst)
	{
		temp = (*cmd_lst)->next;
		ft_lstdelone_cmd(*cmd_lst, del);
		*cmd_lst = temp;
	}
}