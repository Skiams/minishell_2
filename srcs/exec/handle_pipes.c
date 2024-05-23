/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/23 23:32:05 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_swap_pipes(t_data *data, t_cmds *cmds)
{
	if (cmds->here_doc != -1)
	{
		dprintf(2, "oui\n");
		close(cmds->here_doc);
		cmds->here_doc = -1;
	}
	if (close(cmds->prev_pipe[0]) == -1)
		ft_handle_close_error(data, cmds);
	if (close(cmds->prev_pipe[1]) == -1)
		ft_handle_close_error(data, cmds);

	if (cmds->next)
	{
		cmds->next->prev_pipe[0] = cmds->curr_pipe[0];
		cmds->next->prev_pipe[1] = cmds->curr_pipe[1];
	}
	ft_free_tab(cmds->cmd_path);
	ft_free_tab(data->mini_env);
}

static void	ft_fork_built_in_pipes(t_data *data, t_cmds *cmds, char **env)
{
	(void)env;
	cmds->pid = fork();
	if (cmds->pid == -1)
		ft_handle_fork_error(data, cmds);
	if (cmds->pid == 0)
	{
		ft_handle_processes(data, cmds, NULL);
	//ft_handle_processes(data, cmds, data->mini_env);
	if (cmds->here_doc != -1)
		dprintf(2, "MESDAMES ET MESSIEURS, LES BUILT-IN\n");
	}
	ft_waitpid_only_one_cmd(cmds);
}

static	void	ft_fork_no_built_in(t_data *data, t_cmds *cmds, char **env)
{
	(void)env;
	cmds->pid = fork();
	if (cmds->pid == -1)
		ft_handle_fork_error(data, cmds);
	if (cmds->pid == 0)
		ft_handle_processes(data, cmds, NULL);
	//		ft_handle_processes(data, cmds, data->env);
	if (cmds->here_doc != -1)
	{
		dprintf(2, "CECI N'EST PAS UN BUILT-IN\n");
		close(cmds->here_doc);
		cmds->here_doc = -1;
	}
}

void	ft_handle_pipes(t_data *data, t_cmds *cmds, char **env)
{
	(void)env;
	t_cmds	*tmp;

	tmp = cmds;
	while (cmds && cmds != NULL)
	{
		ft_get_path(data, cmds);
		if (pipe(cmds->curr_pipe) == -1)
			ft_handle_pipe_error(data, cmds);
		if (ft_is_a_built_in(cmds->cmd))
			ft_fork_built_in_pipes(data, cmds, NULL);
		//ft_fork_built_in_pipes(data, cmds, data->env);
		else
			ft_fork_no_built_in(data, cmds, NULL);
		//ft_fork_no_built_in(data, cmds, data->env);
		ft_swap_pipes(data, cmds);
		if (cmds->here_doc != -1)
		{
			dprintf(2, "OUIIIII, J'ai un here_doc dans handle_pipes() APRES LE SWAP\n");
			close(cmds->here_doc);
			cmds->here_doc = -1;
		}
		if (cmds->next == NULL)
			break ;
		cmds = cmds->next;
	}
	cmds = tmp;
	if (cmds->here_doc != -1)
	{
		dprintf(2, "OUIIIII, J'ai un here_doc dans handle_pipes() DERNIER HERE_DOC APRES LE BREAK\n");
		close(cmds->here_doc);
		cmds->here_doc = -1;
	}
	cmds->i = 0;
	dprintf(2, "666\n");
	while (cmds->i++ < cmds->cmd_count)
		ft_waitpid(cmds);
}
