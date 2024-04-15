/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/15 13:26:37 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_multi_pipes(t_pipex *pipex, char **argv, char **env)
{
	while (pipex->i < pipex->argc - 3)
	{
		if (pipe(pipex->curr_pipe) == -1)
			ft_handle_pipe_error(pipex);
		pipex->pid1 = fork();
		if (pipex->pid1 == -1)
			ft_handle_fork_error(pipex);
		if (pipex->pid1 == 0)
			ft_handle_processes(pipex, argv, env);
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

int	ft_exec(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	ft_memset(&pipex, 0, sizeof(t_pipex));
	pipex.argc = argc;
	ft_exec_here_doc(&pipex, argv);
	if (argc < 5 || (pipex.here_doc && argc < 6))
		ft_print_missing_param();
	ft_get_path(&pipex, env);
	if (pipe(pipex.prev_pipe) == -1)
		ft_handle_pipe_error(&pipex);
	ft_handle_multi_pipes(&pipex, argv, env);
	ft_close_processes(&pipex);
	ft_free_tab(pipex.cmd_path);
	pipex.i = 0;
	while (pipex.i++ < argc - 3)
		ft_waitpid(&pipex);
	return (pipex.code_status);
}
