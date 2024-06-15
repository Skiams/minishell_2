/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/15 20:50:04 by skiam            ###   ########.fr       */
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
//		dprintf(2, "%s\n", __func__);
		waitpid(data->pidlist[i], &status, 0);
		if (WIFEXITED(status))
		{
//			dprintf(2, "on rentre dans le if\n");
			ft_exit_code(WEXITSTATUS(status), ADD);
		}
		else if (WIFSIGNALED(status) && g_sig_exit != 0)
		{
//			dprintf(2, "Dans le else de %s\n", __func__);
			ft_exit_code(WTERMSIG(status) + 128, ADD);
			if (WTERMSIG(status) == 2)
			{
				ft_putchar(2, '\n');
				data->pidlist[i] = -1;
				i += 1;
				break ;
			}
			if (WTERMSIG(status) == 3)
			{
//				dprintf(2, "status est a 3\n");
				ft_putstr_fd("Quit (core dumped)\n", 2);
			//		Pour eviter les conditionnals jumps
				data->pidlist[i] = -1;
				i += 1;
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
