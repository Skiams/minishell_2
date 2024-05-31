/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/31 14:51:10 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_rights(t_data *data, t_cmds *cmds, char *cmd, char *tmp2)
{
	dprintf(2, "-> %s\n", __func__);
	if (tmp2)
		free (tmp2);
	ft_free(data, cmds, cmd, "Permission denied\n");
	exit (ft_exit_code(126, ADD));
}

void	ft_handle_no_file_or_dir(t_data *data, t_cmds *cmds, char *cmd)
{
	dprintf(2, "-> %s\n", __func__);
	ft_free(data, cmds, cmd, ": No such file or directory 😮\n");
	exit (ft_exit_code(127, ADD));
}

void	ft_handle_directory(t_data *data, t_cmds *cmds, char *cmd, char **args)
{
	(void)args;
	dprintf(2, "-> %s\n", __func__);
	ft_free(data, cmds, cmd, "Is a directory\n");
	exit (ft_exit_code(126, ADD));
}
