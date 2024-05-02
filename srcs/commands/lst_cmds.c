/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:54:36 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/02 14:44:10 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmds	*lst_new_cmd(void)
{
	t_cmds	*node;

	node = (t_cmds *)malloc(sizeof(t_cmds));
	if (!node)
		return (NULL);
	node->redir = NULL;
	node->env_path = NULL;
	node->cmd_path = NULL;
	node->right_path = NULL;
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
	if (cmd->redir)
		ft_clear_redirlst(&cmd->redir, del);
	// if (cmd->cmd_path != NULL)
	// 	ft_free_tab(cmd->cmd_path);
	// if (cmd->env_path != NULL)
	// 	(*del)(cmd->env_path);
	// if (cmd->right_path != NULL)
	// 	(*del)(cmd->right_path);
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
