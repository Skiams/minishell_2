/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/16 21:26:13 by ahayon           ###   ########.fr       */
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

void	ft_waitpid(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < 1024 && data->pidlist[i] != -1)
	{
	//	waitpid(*pid, pid, 0);
		waitpid(data->pidlist[i], &status, 0);
		if (WIFEXITED(status))
		{
			ft_exit_code(WEXITSTATUS(status), ADD);
		}
		else if (WIFSIGNALED(status) && g_sig_exit != 0)
		{
			ft_exit_code(WTERMSIG(status) + 128, ADD);
			if (WTERMSIG(status) == 2)
			{
				dprintf(2, "WTERMSIG == 2\n");
				//ft_putchar(2, '\n');
				data->pidlist[i] = -1;
				i += 1;
				g_sig_exit = 0;
				break ;
			}
			if (WTERMSIG(status) == 3)
			{
				dprintf(2, "WTERMSIG == 3\n");
				ft_putstr_fd("Quit (core dumped)\n", 2);
				data->pidlist[i] = -1;
				i += 1;
				g_sig_exit = 0;
				break ;
			}
		}
		data->pidlist[i] = -1;
		i += 1;
	}
}

void	ft_add_pid(t_data *data, int pid)
{
	int	i;

	i = 0;
	while (i < 1024 && data->pidlist[i] != -1)
		i += 1;
	data->pidlist[i] = pid;
}
