/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/18 13:26:52 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

static void	ft_handle_multi_pipes(t_data *data, t_pipex *pipex, char **argv, char **env)
{
	while (pipex->i < pipex->argc - 3)
	{
		if (pipe(pipex->curr_pipe) == -1)
			ft_handle_pipe_error(pipex);
		pipex->pid1 = fork();
		if (pipex->pid1 == -1)
			ft_handle_fork_error(pipex);
		if (pipex->pid1 == 0)
			ft_handle_processes(data, pipex, argv, env);
		else if (pipex->pid1 > 0)
		{
			close(pipex->prev_pipe[0]);
			close(pipex->prev_pipe[1]);
			pipex->prev_pipe[0] = pipex->curr_pipe[0];
			pipex->prev_pipe[1] = pipex->curr_pipe[1];
		}
		pipex->i += 1;
	}
}

int	ft_is_only_one_cmd(t_data *data, t_cmds *cmds, char **env)
{
	char	*cmds_path;

	if (!cmds)
		return (0);
	if (!cmds->cmd)
		return  (0);
	if (ft_is_a_built_in(cmds->cmd))
	{
		ft_exec_built_in(data, cmds);
		return (0);
	}
	else
	{
		cmds->pid1 = fork();
		if (cmds->pid1 == -1)
			ft_handle_fork_error2(cmds);
		if (cmds->pid1 == 0)
		{
			cmds_path = ft_get_cmd_path2(data, cmds, cmds->cmd, cmds->args);
			execve(cmds_path, cmds->args, env);
			ft_printf(2, "Attention tout le monde ! Je fail\n");
			perror(cmds_path);
			free(cmds_path);
			ft_free_tab(cmds->args);
			ft_exit_code(1, ADD);
			exit (1);
		}
		else if (cmds->pid1 > 0)
		{
			cmds->i = 0;
			while (cmds->i++ < cmds->argc)
				ft_waitpid_only_one_cmd(cmds);
		}
		return (ft_exit_code(0, GET));
	}
}

int	ft_exec(t_data *data, t_cmds *cmds, int argc, char **argv, char **env)
{
	t_pipex	pipex;

	ft_memset(&pipex, 0, sizeof(t_pipex));
	cmds->argc = argc;
	//	ft_exec_here_doc(&pipex, argv);
	ft_get_path(cmds, env);
	if (cmds->argc == 1)
		ft_is_only_one_cmd(data, cmds, env);
	else if (pipe(pipex.prev_pipe) == -1)
	{
		ft_handle_pipe_error(&pipex);
		ft_handle_multi_pipes(data, &pipex, argv, env);
	}
	ft_free_tab(pipex.cmd_path);
	ft_free_tab(cmds->cmd_path);
	return (0);
}
