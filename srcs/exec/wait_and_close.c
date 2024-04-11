/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/11 21:01:36 by eltouma          ###   ########.fr       */
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
