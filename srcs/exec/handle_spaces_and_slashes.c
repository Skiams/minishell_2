/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spaces_and_slashes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/28 15:11:34 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_space_only(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 9 && str[i] <= 13) && str[i] != 32)
			return (0);
		i += 1;
	}
	return (1);
}

int	ft_is_slash_only(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 47)
			return (0);
		i += 1;
	}
	return (1);
}

/*
void	ft_handle_space_error(char **argv, t_pipex *pipex)
{
	ft_close_processes(pipex);
	ft_putstr_fd(*argv, 2);
	ft_putstr_fd(" : command not found\n", 2);
	ft_free_tab(pipex->cmd_path);
	exit (127);
}

void	ft_handle_slash_error(char **argv, t_pipex *pipex)
{
	ft_close_processes(pipex);
	ft_putstr_fd(*argv, 2);
	ft_putstr_fd(" : Is a directory\n", 2);
	ft_free_tab(pipex->cmd_path);
	exit (1);
}
*/
