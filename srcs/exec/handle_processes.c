/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/05 18:19:12 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_handle_here_doc(t_pipex *pipex, char **argv)
{
	pipex->here_doc = open(argv[1], O_RDONLY, 0755);
	if (pipex->here_doc == -1)
		ft_handle_file_error(&argv[1], pipex);
	if (dup2(pipex->here_doc, STDIN_FILENO) == -1)
		ft_handle_dup2_error(pipex);
	if (close(pipex->here_doc) == -1)
		ft_handle_close_error(pipex);
	pipex->i += 1;
}

void	ft_handle_infile(t_pipex *pipex, char **argv)
{
	if (pipex->is_here_doc)
		ft_handle_here_doc(pipex, argv);
	else
	{
		pipex->infile = open(argv[1], O_RDONLY, 0755);
		if (pipex->infile == -1)
			ft_handle_file_error(&argv[1], pipex);
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			ft_handle_dup2_error(pipex);
		if (close(pipex->infile) == -1)
			ft_handle_close_error(pipex);
	}
	if (close(pipex->prev_pipe[0]) == -1)
		ft_handle_close_error(pipex);
	if (dup2(pipex->curr_pipe[1], STDOUT_FILENO) == -1)
		ft_handle_dup2_error(pipex);
	if (close(pipex->curr_pipe[1]) == -1)
		ft_handle_close_error(pipex);
	if (ft_is_space_only(argv[2]))
		ft_handle_space_error(&argv[2], pipex);
	if (ft_is_slash_only(argv[2]))
		ft_handle_slash_error(&argv[2], pipex);
}

void	ft_exec_cmds(t_pipex *pipex, char **argv, char **env)
{
	int		i;
	char	**cmds;
	char	*cmds_path;

	i = 0;
	cmds = ft_split(argv[pipex->i + 2]);
	if (!cmds)
	{
		ft_free_tab(pipex->cmd_path);
		exit (1);
	}
	while (cmds[i++])
		cmds[i] = ft_handle_quotes_and_slash(cmds[i]);
	cmds_path = ft_get_cmd_path(pipex, cmds[0], cmds);
	execve(cmds_path, cmds, env);
	perror(cmds_path);
	free(cmds_path);
	ft_free_tab(pipex->cmd_path);
	exit (1);
}

void	ft_handle_outfile(t_pipex *pipex, char **argv)
{
	if (pipex->here_doc)
		pipex->outfile = open(argv[pipex->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0755);
	else
		pipex->outfile = open(argv[pipex->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (pipex->outfile == -1)
		ft_handle_file_error(&argv[pipex->argc - 1], pipex);
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		ft_handle_dup2_error(pipex);
	if (close(pipex->outfile) == 1)
		ft_handle_close_error(pipex);
	if (close(pipex->curr_pipe[1]) == -1)
		ft_handle_close_error(pipex);
	if (dup2(pipex->prev_pipe[0], STDIN_FILENO) == -1)
		ft_handle_dup2_error(pipex);
	if (close(pipex->prev_pipe[0]) == -1)
		ft_handle_close_error(pipex);
	if (ft_is_space_only(argv[pipex->argc - 1]))
		ft_handle_space_error(&argv[pipex->argc - 1], pipex);
	if (ft_is_slash_only(argv[pipex->argc - 1]))
		ft_handle_slash_error(&argv[pipex->argc - 1], pipex);
}

void	ft_handle_processes(t_pipex *pipex, char **argv, char **env)
{
	if (pipex->i == 0)
		ft_handle_infile(pipex, argv);
	else if (pipex->i == pipex->argc - 4)
		ft_handle_outfile(pipex, argv);
	else
	{
		if (dup2(pipex->prev_pipe[0], STDIN_FILENO) == -1)
			ft_handle_dup2_error(pipex);
		if (dup2(pipex->curr_pipe[1], STDOUT_FILENO) == -1)
			ft_handle_dup2_error(pipex);
		if (ft_is_space_only(argv[pipex->i + pipex->is_here_doc]))
			ft_handle_space_error(&argv[pipex->i + pipex->is_here_doc], pipex);
		if (ft_is_slash_only(argv[pipex->i + pipex->is_here_doc]))
			ft_handle_slash_error(&argv[pipex->i + pipex->is_here_doc], pipex);
	}
	ft_close_processes(pipex);
	ft_waitpid(pipex);
	ft_exec_cmds(pipex, argv, env);
}
