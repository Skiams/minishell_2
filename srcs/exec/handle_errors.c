/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:15:12 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/19 13:33:33 by eltouma          ###   ########.fr       */
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
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	exit (1);
}

void	ft_handle_pipe_error(t_pipex *pipex)
{
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	ft_free_tab(pipex->cmd_path);
	exit (1);
}

void	ft_handle_fork_error(t_pipex *pipex)
{
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	waitpid(pipex->cmd1, NULL, 0);
	ft_free_tab(pipex->cmd_path);
	exit (1);
}

void	ft_handle_close_error(t_pipex *pipex)
{
	ft_putstr_fd("close failed\n", 2);
	ft_free_tab(pipex->cmd_path);
	close(pipex->outfile);
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
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
	if (pipex->fd_pipe[0] != -1 && close(pipex->fd_pipe[0]) == -1)
		ft_putstr_fd("fd_pipe[0] close failed\n", 2);
	if (pipex->fd_pipe[1] != -1 && close(pipex->fd_pipe[1]) == -1)
		ft_putstr_fd("fd_pipe[1] close failed\n", 2);
	exit (1);
}
