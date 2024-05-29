/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/29 18:21:33 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_exec(t_data *data, t_cmds *cmds)
{
	(void)data;
	dprintf(2, "init_exec() TSAIS\n");
	while (cmds != NULL)
	{
		cmds->cmd_count = ft_lstsize_cmd(cmds);
		cmds = cmds->next;
	}
}

int     ft_handle_here_doc(t_data *data, t_cmds *cmds)
{
	t_redir *head;
	while (cmds != NULL)
	{
		head = cmds->redir;
		while (head != NULL)
		{
			if (head->type == 2)
				ft_exec_here_doc(data, cmds, head);
			head = head->next;
		}
		cmds = cmds->next;
	}
	return (-1);
}

// Voir avec Antoine le code erreur
int	ft_exec(t_data *data, t_cmds *cmds, char **env)
{
	(void)env;
	if (!cmds)
		return (ft_exit_code(0, GET));
	ft_init_exec(NULL, cmds);
	ft_is_max_here_doc_nb_reached(data, cmds);
	ft_handle_here_doc(data, cmds);
	if (cmds->cmd_count == 1)
	{
		//ft_is_only_one_cmd(data, cmds, data->env);
		ft_is_only_one_cmd(data, cmds, NULL);
		ft_free_tab(cmds->cmd_path);
		ft_free_tab(data->mini_env);
	}
	else
	{
		if (pipe(cmds->prev_pipe) == -1)
			ft_handle_pipe_error(data, cmds);
		ft_handle_pipes(data, cmds, NULL);
		//		ft_handle_pipes(data, cmds, data->env);
	}
	// if (cmds->name)
	// {
	// 	dprintf(2, "MESSIEURS, DAMES, le name %s\n", cmds->name);
	// 	ft_free_ptr(cmds->name);
	// 	cmds->name = NULL;
	// }
	(cmds->name) ? dprintf(2, "On a un name manifestement\n") : dprintf(2, "On n'a plus de name, il est bien free t'as vu\n");
	return (ft_exit_code(0, GET));
}
