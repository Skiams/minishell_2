/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/15 17:05:54 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit_properly2(t_data *data, t_cmds *cmds)
{
	ft_free_tab(cmds->cmd_path);
	ft_free_tab(data->mini_env);
	ft_clean_all(data);
	exit (ft_exit_code(0, GET));
}

void	ft_exec_cmds(t_data *data, t_cmds *cmds)
{
	if (!cmds->args)
	{
		ft_dup_stdin_stdout(data, cmds);
		ft_handle_redir(data, cmds);
		ft_dup2_and_close_stdin_stdout(data, cmds);
		ft_exit_properly2(data, cmds);
	}
	if (ft_is_a_built_in(cmds->cmd))
	{
		if (!ft_handle_redir(data, cmds))
			ft_exit_properly2(data, cmds);
		if (cmds->redir)
			ft_handle_redir(data, cmds);
		ft_exec_built_in(data, cmds);
		ft_exit_properly2(data, cmds);
	}
	if (cmds->redir)
		ft_handle_redir(data, cmds);
	cmds->right_path = ft_get_cmd_path(data, cmds, cmds->cmd);
	ft_exit_if_malloc(data);
	ft_close_hd_in_fork(data->cmd_list, NULL);
	execve(cmds->right_path, cmds->args, data->mini_env);
	ft_handle_execve_error(data, cmds);
}

void	ft_handle_first_cmd(t_data *data, t_cmds *cmds)
{
	if (close(cmds->prev_pipe[0]) == -1)
		ft_handle_close_error(data, cmds);
	if (dup2(cmds->curr_pipe[1], STDOUT_FILENO) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->curr_pipe[1]) == -1)
		ft_handle_close_error(data, cmds);
}

void	ft_handle_last_cmd(t_data *data, t_cmds *cmds)
{
	if (close(cmds->curr_pipe[1]) == -1)
		ft_handle_close_error(data, cmds);
	if (dup2(cmds->prev_pipe[0], STDIN_FILENO) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->prev_pipe[0]) == -1)
		ft_handle_close_error(data, cmds);
}

void	ft_handle_processes(t_data *data, t_cmds *cmds)
{
	if (cmds && !cmds->prev)
		ft_handle_first_cmd(data, cmds);
	else if (cmds->next == NULL)
		ft_handle_last_cmd(data, cmds);
	else
	{
		if (dup2(cmds->prev_pipe[0], STDIN_FILENO) == -1)
			ft_handle_dup2_error(data, cmds);
		if (dup2(cmds->curr_pipe[1], STDOUT_FILENO) == -1)
			ft_handle_dup2_error(data, cmds);
	}
	ft_close_processes(cmds);
//	Pas sur que ce add_pid soit utile, a mon avis il ne sert a rien
	ft_add_pid(data, cmds->pid);
	ft_exec_cmds(data, cmds);
}
