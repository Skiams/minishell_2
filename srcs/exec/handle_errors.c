/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:15:12 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/20 15:12:28 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_infile_error(char *argv, t_cmds *cmds, t_data *data)
{
	perror(argv);
	if (cmds->infile != -1)
		close(cmds->infile);
	if (cmds->argc == 1)
		ft_waitpid_only_one_cmd(cmds);
	else
		ft_waitpid(cmds);
	ft_free_tab(cmds->cmd_path);
	ft_clean_all(data);
	exit (1);
}

void	ft_handle_outfile_error(char *argv, t_cmds *cmds, t_data *data)
{
	perror(argv);
	if (cmds->outfile != -1)
		close(cmds->outfile);
	if (cmds->argc == 1)
		ft_waitpid_only_one_cmd(cmds);
	else
		ft_waitpid(cmds);
	ft_free_tab(cmds->cmd_path);
	ft_clean_all(data);
	exit (1);
}

void	ft_handle_pipe_error(t_cmds *cmds)
{
	ft_putstr_fd("pipe failed\n", 2);
	ft_close_processes(cmds);
	ft_free_tab(cmds->cmd_path);
//	ft_clean_all(data);
	exit (1);
}

void	ft_handle_fork_error(t_cmds *cmds)
{
	ft_putstr_fd("fork failed\n", 2);
	ft_close_processes(cmds);
	waitpid(cmds->pid, NULL, 0);
	ft_free_tab(cmds->cmd_path);
//	ft_clean_all(data);
	exit (1);
}

void	ft_handle_close_error(t_cmds *cmds)
{
	ft_putstr_fd("close failed\n", 2);
	ft_free_tab(cmds->cmd_path);
	close(cmds->outfile);
//	ft_free_tab(cmds->cmd_path);
//	ft_clean_all(data);
	ft_close_processes(cmds);
	exit (1);
}

void	ft_handle_dup2_error(t_cmds *cmds)
{
	ft_putstr_fd("dup2 failed\n", 2);
	ft_free_tab(cmds->cmd_path);

	if (cmds->infile != -1 && close(cmds->infile) == -1)
		ft_putstr_fd("infile close failed\n", 2);
	if (cmds->outfile != -1 && close(cmds->outfile) == -1)
		ft_putstr_fd("outfile close failed\n", 2);
	if (cmds->prev_pipe[0] != -1 && close(cmds->prev_pipe[0]) == -1)
		ft_putstr_fd("prev_pipe[0] close failed\n", 2);
	if (cmds->prev_pipe[1] != -1 && close(cmds->prev_pipe[1]) == -1)
		ft_putstr_fd("prev_pipe[1] close failed\n", 2);
	if (cmds->curr_pipe[0] != -1 && close(cmds->curr_pipe[0]) == -1)
		ft_putstr_fd("curr_pipe[0] close failed\n", 2);
	if (cmds->curr_pipe[1] != -1 && close(cmds->curr_pipe[1]) == -1)
		ft_putstr_fd("curr_pipe[1] close failed\n", 2);
	exit (1);
}
