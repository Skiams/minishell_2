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

void	ft_exec_cmds(t_data *data, t_cmds *cmds, char **argv, char **env)
{
	char	*cmds_path;
	(void)argv;


	cmds_path = ft_get_cmd_path(data, cmds, cmds->cmd, cmds->args);
	execve(cmds_path, cmds->args, env);
	ft_putstr_fd("Attention tout le monde ! Je fail meme avec plusieurs commandes !\n", 2);
	ft_putstr_fd("minishell: ", 2);
	perror(cmds_path);
	free(cmds_path);
	while (cmds && cmds != NULL)
	{
		ft_free_tab(cmds->cmd_path);
		cmds = cmds->next;
	}
	ft_clean_all(data);
	ft_exit_code(1, ADD);
	exit (1);
}

void     ft_handle_first_cmd(t_data *data, t_cmds *cmds)
{
        if (!cmds->cmd)
                return ;
        else
        {
		while (cmds->redir)
		{
			ft_handle_redir(data, cmds);
			cmds->redir = cmds->redir->next;
		}
		if (close(cmds->prev_pipe[0]) == -1)
			ft_handle_close_error(cmds);
		if (dup2(cmds->curr_pipe[1], 1) == -1)
			ft_handle_dup2_error(cmds);
		if (close(cmds->curr_pipe[1]) == -1)
			ft_handle_close_error(cmds);
        }
}

void	ft_handle_last_cmd(t_cmds *cmds)
{
    	if (!cmds->cmd)
                return ;
	else
	{
		if (close(cmds->curr_pipe[1]) == -1)
			ft_handle_close_error(cmds);
		if (dup2(cmds->prev_pipe[0], 0) == -1)
			ft_handle_dup2_error(cmds);
		if (close(cmds->prev_pipe[0]) == -1)
			ft_handle_close_error(cmds);
	}
}

void	ft_handle_processes(t_data *data, t_cmds *cmds, char **argv, char **env)
{
	(void)argv;

	if (cmds && !cmds->prev)
		ft_handle_first_cmd(data, cmds);
	else if (cmds->next == NULL)
		ft_handle_last_cmd(cmds);
	else
	{
		if (dup2(cmds->prev_pipe[0], STDIN_FILENO) == -1)
			ft_handle_dup2_error(cmds);
		if (dup2(cmds->curr_pipe[1], STDOUT_FILENO) == -1)
			ft_handle_dup2_error(cmds);
	}
	ft_waitpid(cmds);
	ft_exec_cmds(data, cmds, argv, env);
}
/*
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
*/
/*
void	ft_handle_infile(t_pipex *pipex, char **argv)
{
	if (pipex->is_here_doc)
		ft_handle_here_doc(pipex, argv);
	else if (pipex->infile)
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
*/



/*
void	ft_handle_outfile(t_pipex *pipex, char **argv)
{
	int	flag;

	if (pipex->here_doc)
		flag = O_APPEND;
	else
		flag = O_TRUNC;
	pipex->outfile = open(argv[pipex->argc - 1],
			O_WRONLY | O_CREAT | flag, 0755);
	if (pipex->outfile == -1)
		ft_handle_file_error(&argv[pipex->argc - 1], pipex);
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		ft_handle_dup2_error(pipex);
	if (close(pipex->outfile) == -1)
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
*/
