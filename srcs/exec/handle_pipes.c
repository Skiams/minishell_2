/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/31 14:56:58 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_swap_pipes(t_data *data, t_cmds *cmds)
{
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

static void	ft_fork_built_in_pipes(t_data *data, t_cmds *cmds)
{
	cmds->pid = fork();
	if (cmds->pid == -1)
		ft_handle_fork_error(data, cmds);
	if (cmds->pid == 0)
		ft_handle_processes(data, cmds);
	if (cmds->here_doc_count > 0 && close(cmds->here_doc) == -1)
		ft_handle_close_error(data, cmds);
	ft_waitpid_only_one_cmd(cmds);
}

static	void	ft_fork_no_built_in(t_data *data, t_cmds *cmds)
{
	ft_handle_signal(2);
	cmds->pid = fork();
	if (cmds->pid == -1)
		ft_handle_fork_error(data, cmds);
	if (cmds->pid == 0)
		ft_handle_processes(data, cmds);
}

void	ft_handle_pipes(t_data *data, t_cmds *cmds)
{
	t_cmds	*tmp;

	tmp = cmds;
	while (cmds && cmds != NULL)
	{
		ft_get_path(data, cmds);
		if (pipe(cmds->curr_pipe) == -1)
			ft_handle_pipe_error(data, cmds);
		if (ft_is_a_built_in(cmds->cmd))
			ft_fork_built_in_pipes(data, cmds);
		else
			ft_fork_no_built_in(data, cmds);
		ft_swap_pipes(data, cmds);
		if (cmds->next == NULL)
			break ;
		cmds = cmds->next;
	}
	cmds = tmp;
	cmds->i = 0;
	while (cmds->i++ < cmds->cmd_count)
		ft_waitpid(cmds);
	ft_handle_signal(1);
}
