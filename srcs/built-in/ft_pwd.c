/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:28:40 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/15 16:20:38 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_waitpid2(t_data *data)
{
// A MODIFIER
	int     status;

	ft_close_processes(data->pipex);
	while (errno != ECHILD)
	{
                if (data->pipex->pid1 == waitpid(-1, &status, 0))
                {
                        if (WIFEXITED(status))
                                data->pipex->code_status = WEXITSTATUS(status);
                }
	}
}

int	ft_pwd(t_data *data)
{
	char	*working_dir;

	working_dir = getcwd(NULL, 0);
	if (!working_dir)
	{
		perror(working_dir);
		ft_waitpid2(data);
		exit(1);
	}
	ft_putstr_fd(working_dir, 1);
	ft_putstr_fd("\n", 1);
	free(working_dir);
	working_dir = NULL;
	return (0);
}
