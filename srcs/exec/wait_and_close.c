/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/19 19:44:20 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close_processes(t_pipex *pipex)
{
	close(pipex->prev_pipe[0]);
	close(pipex->prev_pipe[1]);
	close(pipex->curr_pipe[0]);
	close(pipex->curr_pipe[1]);
}

void	ft_waitpid(t_pipex *pipex)
{
	int	status;

	ft_close_processes(pipex);
	while (errno != ECHILD)
	{
		if (pipex->pid1 == waitpid(-1, &status, 0))
		{
			if (WIFEXITED(status))
				pipex->code_status = WEXITSTATUS(status);
		}
	}
}

void	ft_close_processes2(t_cmds *cmds)
{
	(void) cmds; 
	close(cmds->prev_pipe[0]);
	close(cmds->prev_pipe[1]);
	close(cmds->curr_pipe[0]);
	close(cmds->curr_pipe[1]);
}

void	ft_waitpid2(t_cmds *cmds)
{
	int	status;

	ft_close_processes2(cmds);
	while (errno != ECHILD)
	{
		if (cmds->pid1 == waitpid(-1, &status, 0))
		{
			if (WIFEXITED(status))
				ft_exit_code(WEXITSTATUS(status), ADD);
		}
		cmds = cmds->next;
	}
}

void	ft_waitpid_only_one_cmd(t_cmds *cmds)
{
	int	status;

	while (errno != ECHILD)
	{
		if (cmds->pid1 == waitpid(-1, &status, 0))
		{
			if (WIFEXITED(status))
				ft_exit_code(WEXITSTATUS(status), ADD);
		}
	}
}
