/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:28:44 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/25 15:46:50 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokens(t_token *token_lst)
{
	t_token	*tmp;
	int		i;

	tmp = token_lst;
	i = 1;
	while (tmp)
	{
		dprintf(2, "Token %d / type = %d / value = %s\n",
			i, tmp->type, tmp->value);
		tmp = tmp->next;
		i++;
	}
}

void	print_env(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp)
	{
		dprintf(2, "env var = %s / value = %s\n",
			tmp->var, tmp->value);
		tmp = tmp->next;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab)
	{
		dprintf(2, "%s\n", tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	print_redir(t_redir *redir)
{
	t_redir	*tmp;
	
	tmp = redir;
	while (tmp)
	{
		dprintf(2, "redir->type = %d\n", tmp->type);
		dprintf(2, "redir->path = %s\n", tmp->path);
		tmp = tmp->next;
	}
	
}

void	print_cmds(t_cmds *cmd_list)
{
	t_cmds	*tmp;
	int		i;
	
	tmp = cmd_list;
	while (tmp)
	{
		i = 0;
		dprintf(2, "cmds->cmd = %s\n", tmp->cmd);
		// dprintf(2, "cmds->argc = %d\n", tmp->argc);
		while (tmp->args[i])
		{
			dprintf(2, "cmd->args[%d] = %s\n", i, tmp->args[i]);
			i++;
		}
		while (tmp->redir)
		{
			dprintf(2, "redir->type = %d\n", tmp->redir->type);
			dprintf(2, "redir->path = %s\n", tmp->redir->path);
			free(tmp->redir->path);
			tmp->redir = tmp->redir->next;
		}
		tmp = tmp->next;
	}
}

/*
void	print_redir(t_redir *redir)
{
	t_redir	*tmp;
	
	if (redir)
	{

		dprintf(2, "redir->type = %d\n", tmp->type);
		dprintf(2, "redir->path = %s\n", tmp->path);
		tmp = tmp->next;
	}
	
}*/
/*
  tmp = redir;
		while (tmp)
		{
			dprintf(2, "redir->type = %d\n", tmp->type);
			dprintf(2, "redir->path = %s\n", tmp->path);
			tmp = tmp->next;
		}
}
*/
