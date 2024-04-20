/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/20 15:27:17 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_no_file_or_dir(char *argv)
{
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit (127);
}

void	ft_handle_directory(t_pipex *pipex, char *argv, char **path)
{
	ft_free(pipex, argv, path, "Is a directory\n");
	exit (126);
}

void	ft_handle_rights(t_pipex *pipex, char *argv, char **path, char *tmp2)
{
	if (tmp2)
		free (tmp2);
	ft_free(pipex, argv, path, "Permission denied\n");
	exit (126);
}

void	ft_handle_rights2(t_data *data, t_cmds *cmds, char *cmd, char **args, char *tmp2)
{
	(void)args;
	if (tmp2)
		free (tmp2);
	ft_free2(data, cmds, cmd, "Permission denied\n");
	exit (ft_exit_code(126, ADD));
}

void	ft_handle_no_file_or_dir2(t_data *data, t_cmds *cmds, char *cmd, char **args)
{
	(void)args;
	ft_free2(data, cmds, cmd, ": No such file or directory 😮\n");
	exit (ft_exit_code(127, ADD));
}

void	ft_handle_directory2(t_data *data, t_cmds *cmds, char *cmd, char **args)
{
	(void)args;
	ft_free2(data, cmds, cmd, "Is a directory\n");
	exit (ft_exit_code(126, ADD));
}
