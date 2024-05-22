/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/22 12:17:09 by eltouma          ###   ########.fr       */
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
	while ((cmds->pid = waitpid(-1, &status, 0)) > 0)
	{
		if (WIFEXITED(status))
			ft_exit_code(WEXITSTATUS(status), ADD);
	}
}

void	ft_waitpid_only_one_cmd(t_cmds *cmds)
{
	int	status;

	while ((cmds->pid = waitpid(-1, &status, 0)) > 0)
	{
		if (WIFEXITED(status))
			ft_exit_code(WEXITSTATUS(status), ADD);
	}
}
