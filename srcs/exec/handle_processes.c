/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/17 16:33:57 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_exit_properly2(t_data *data, t_cmds *cmds)
{
        ft_free_tab(cmds->cmd_path);
        ft_clean_all(data);
        ft_exit_code(0, GET);
        exit (1);
}

void	ft_exec_cmds(t_data *data, t_cmds *cmds, char **env)
{
	dprintf(2, "je passe dans exec_cmds\n");
	if (!cmds->args)
        {
                ft_dup_stdin_stdout(data, cmds);
                ft_handle_redir_without_cmd(data, cmds);
                ft_dup2_and_close_stdin_stdout(data, cmds);
		ft_exit_properly2(data, cmds);
        }
	if (cmds->redir)
	{
		//dprintf(2, "dans exec_cmds() cmds->name %s\n", cmds->name);
		ft_handle_redir(data, cmds);
	//	dprintf(2, "dans exec_cmds() cmds->name %s\n", cmds->name);
	}
	if (ft_is_a_built_in(cmds->cmd))
	{
		ft_exec_built_in(data, cmds);
		ft_exit_properly2(data, cmds);
	}
	cmds->right_path = ft_get_cmd_path(data, cmds, cmds->cmd, cmds->args);
	execve(cmds->right_path, cmds->args, env);
	ft_handle_execve_error(data, cmds);

}

void     ft_handle_first_cmd(t_data *data, t_cmds *cmds)
{
	if (close(cmds->prev_pipe[0]) == -1)
		ft_handle_close_error(data, cmds);
	if (dup2(cmds->curr_pipe[1], 1) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->curr_pipe[1]) == -1)
		ft_handle_close_error(data, cmds);
}

void	ft_handle_last_cmd(t_data *data, t_cmds *cmds)
{
	if (close(cmds->curr_pipe[1]) == -1)
		ft_handle_close_error(data, cmds);
	if (dup2(cmds->prev_pipe[0], 0) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->prev_pipe[0]) == -1)
		ft_handle_close_error(data, cmds);
}

void	ft_handle_processes(t_data *data, t_cmds *cmds, char **env)
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
	ft_waitpid(cmds);
	ft_exec_cmds(data, cmds, env);
}
