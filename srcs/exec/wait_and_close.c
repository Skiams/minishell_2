/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/11 17:49:46 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close_processes(t_cmds *cmds)
{
	close(cmds->prev_pipe[0]);
	close(cmds->prev_pipe[1]);
	close(cmds->curr_pipe[0]);
	close(cmds->curr_pipe[1]);
}

void	ft_waitpid(t_cmds *cmds)
{
	int	status;

	ft_close_processes(cmds);
	//cmds->pid = waitpid(-1, &status, 0);
	//while (cmds->pid > 0)
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			ft_exit_code(WEXITSTATUS(status), ADD);
		else if (WIFSIGNALED(status) && g_sig_exit != 0) 
		{
			ft_exit_code(WTERMSIG(status) + 128, ADD);
			if (WTERMSIG(status) == 2)
				ft_putstr_fd("\n", 2);
			if (WTERMSIG(status) == 3)
				ft_putstr_fd("(QuitCore Dump)\n", 2);
		}
		//cmds->pid = waitpid(-1, &status, 0);
	}
}

void	ft_waitpid_only_one_cmd(t_cmds *cmds)
{
	int	status;

	// cmds->pid = waitpid(-1, &status, 0);
	(void) 	cmds;
	//while (cmds->pid > 0)
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			ft_exit_code(WEXITSTATUS(status), ADD);
		else if (WIFSIGNALED(status) && g_sig_exit != 0)
		{
			ft_exit_code(WTERMSIG(status) + 128, ADD);
			if (WTERMSIG(status) == 2)
				ft_putstr_fd("\n", 2);
			if (WTERMSIG(status) == 3)
				ft_putstr_fd("(QuitCore Dump)\n", 2);
		}
		// cmds->pid = waitpid(-1, &status, 0);
	}
}
