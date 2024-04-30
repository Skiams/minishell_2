/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/20 22:55:51 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_cmds(t_data *data, t_cmds *cmds, char **env)
{
	cmds->right_path = ft_get_cmd_path(data, cmds, cmds->cmd, cmds->args);
	execve(cmds->right_path, cmds->args, env);
	ft_handle_execve_error(data, cmds);
}

void     ft_handle_first_cmd(t_data *data, t_cmds *cmds, char **env)
{
	(void)env;
	(void)data;
        if (!cmds->cmd)
                return ;
	else
	{
		if (close(cmds->prev_pipe[0]) == -1)
			ft_handle_close_error(cmds);
		if (dup2(cmds->curr_pipe[1], 1) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->curr_pipe[1]) == -1)
			ft_handle_close_error(cmds);
        }
}

void	ft_handle_last_cmd(t_data *data, t_cmds *cmds, char **env)
{
	(void)env;
    	if (!cmds->cmd)
                return ;
	else
	{
		if (close(cmds->curr_pipe[1]) == -1)
			ft_handle_close_error(cmds);
		if (dup2(cmds->prev_pipe[0], 0) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->prev_pipe[0]) == -1)
			ft_handle_close_error(cmds);
	}
}

void	ft_handle_processes(t_data *data, t_cmds *cmds, char **argv, char **env)
{
	(void)argv;
	if (cmds && !cmds->prev)
		ft_handle_first_cmd(data, cmds, env);
	else if (cmds->next == NULL)
		ft_handle_last_cmd(data, cmds, env);
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
