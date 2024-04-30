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

static void    ft_handle_dup_error(t_data *data, t_cmds *cmds)
{
	perror(cmds->cmd);
	ft_free_tab(cmds->cmd_path);
	ft_clean_all(data);
	exit(1);
}

void	ft_dup_stdin_stdout(t_data *data, t_cmds *cmds)
{
	if ((cmds->dev_stdin = dup(0)) == -1)
		ft_handle_dup_error(data, cmds);
	if ((cmds->dev_stdout = dup(1)) == -1)
		ft_handle_dup_error(data, cmds);
}

void	ft_dup2_and_close_stdin_stdout(t_data *data, t_cmds *cmds)
{
	if (dup2(cmds->dev_stdin, 0) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->dev_stdin) == -1)
		ft_handle_close_error(cmds);
	if (dup2(cmds->dev_stdout, 1) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->dev_stdout) == -1)
		ft_handle_close_error(cmds);
}
void    ft_handle_dup2_error(t_data *data, t_cmds *cmds)
{
	ft_putstr_fd("dup2 failed\n", 2);
	ft_free_tab(cmds->cmd_path);
	ft_clean_all(data);
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
