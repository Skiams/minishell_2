/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:34:21 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/23 16:02:47 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_init_redir_node(t_redir *redir_node)
{
	redir_node->path = NULL;
	redir_node->args = NULL;
	redir_node->type = -1;
	//redir_node->here_doc = 0;
	redir_node->next = NULL;
	redir_node->prev = NULL;
}

static bool	ft_init_redir_lst(t_cmds *cmd)
{
	t_redir	*temp;

	if (!cmd->redirections)
	{
		cmd->redirections = (t_redir *)malloc(sizeof(t_redir));
		if (!(cmd->redirections))
			return (false);
		ft_init_redir_node(cmd->redirections);
	}
	else
	{
		temp = cmd->redirections;
		while (temp->next)
			temp = temp->next;
		temp->next = (t_redir *)malloc(sizeof(t_redir));
		if (!temp->next)
			return (false);
		ft_init_redir_node(temp->next);
		temp->next->prev = temp;
	}
	return (true);
}

static void	ft_delone_redir(t_redir *redir_node, void (*del)(void *))
{
	if (redir_node->path)
		(*del)(redir_node->path);
	if (redir_node->args)
		ft_free_tab(redir_node->args);
	(*del)(redir_node);
}

void	ft_clear_redirlst(t_redir **redir_list, void (*del)(void *))
{
	t_redir	*temp;

	temp = NULL;
	while (*redir_list)
	{
		temp = (*redir_list)->next;
		ft_delone_redir(*redir_list, del);
		*redir_list = temp;
	}
}

static t_token	*get_next_token(t_token *token)
{
	if (token->next->next)
		return (token->next->next);
	else
		return (token->next);
}

bool	ft_redir_cmd(t_cmds **cmd_lst, t_token **token_lst)
{
	t_cmds		*cmd;
	t_token		*tmp;
	t_redir	*last_redir;

	tmp = *token_lst;
	cmd = ft_last_cmd(*cmd_lst);
	if (!ft_init_redir_lst(cmd))
		return (false);
	last_redir = cmd->redirections;
	while (last_redir && last_redir->next)
		last_redir = last_redir->next;
	last_redir->path = ft_strdup(tmp->next->value);
	if (!last_redir->path)
		return (false);
	last_redir->type = tmp->type;
	tmp = get_next_token(tmp);
	*token_lst = tmp;
	return (true);
}
