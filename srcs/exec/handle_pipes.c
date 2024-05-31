/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/31 23:40:38 by eltouma          ###   ########.fr       */
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
	ft_close_hd_in_fork(data->cmd_list, NULL);
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
	while (tmp && tmp != NULL)
	{
		ft_get_path(data, tmp);
		if (pipe(tmp->curr_pipe) == -1)
			ft_handle_pipe_error(data, tmp); 
		if (ft_is_a_built_in(tmp->cmd))
			ft_fork_built_in_pipes(data, tmp);
		else
			ft_fork_no_built_in(data, tmp);
		ft_swap_pipes(data, tmp);
		tmp = tmp->next;
		fprintf(stderr,">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>v\n");
	}
	//cmds = tmp;
	cmds->i = 0;
	while (cmds->i++ < cmds->cmd_count)
		ft_waitpid(cmds);
	ft_handle_signal(1);
}
