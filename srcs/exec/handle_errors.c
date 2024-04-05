/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:15:12 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/05 18:18:25 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_handle_file_error(char **argv, t_pipex *pipex)
{
	perror(*argv);
	ft_free_tab(pipex->cmd_path);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	ft_close_processes(pipex);
	exit (1);
}

void	ft_handle_pipe_error(t_pipex *pipex)
{
	ft_putstr_fd("pipe failed\n", 2);
	ft_close_processes(pipex);
	ft_free_tab(pipex->cmd_path);
	exit (1);
}

void	ft_handle_fork_error(t_pipex *pipex)
{
	ft_putstr_fd("fork failed\n", 2);
	ft_close_processes(pipex);
	waitpid(pipex->pid1, NULL, 0);
	ft_free_tab(pipex->cmd_path);
	exit (1);
}

void	ft_handle_close_error(t_pipex *pipex)
{
	ft_putstr_fd("close failed\n", 2);
	ft_free_tab(pipex->cmd_path);
	close(pipex->outfile);
	ft_close_processes(pipex);
	exit (1);
}

void	ft_handle_dup2_error(t_pipex *pipex)
{
	ft_putstr_fd("dup2 failed\n", 2);
	ft_free_tab(pipex->cmd_path);
	if (pipex->infile != -1 && close(pipex->infile) == -1)
		ft_putstr_fd("infile close failed\n", 2);
	if (pipex->outfile != -1 && close(pipex->outfile) == -1)
		ft_putstr_fd("outfile close failed\n", 2);
	if (pipex->prev_pipe[0] != -1 && close(pipex->prev_pipe[0]) == -1)
		ft_putstr_fd("prev_pipe[0] close failed\n", 2);
	if (pipex->prev_pipe[1] != -1 && close(pipex->prev_pipe[1]) == -1)
		ft_putstr_fd("prev_pipe[1] close failed\n", 2);
	if (pipex->curr_pipe[0] != -1 && close(pipex->curr_pipe[0]) == -1)
		ft_putstr_fd("curr_pipe[0] close failed\n", 2);
	if (pipex->curr_pipe[1] != -1 && close(pipex->curr_pipe[1]) == -1)
		ft_putstr_fd("curr_pipe[1] close failed\n", 2);
	exit (1);
}
