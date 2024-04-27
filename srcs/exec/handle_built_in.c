/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:28:03 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/22 14:18:48 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_built_in(t_data *data, t_cmds *cmds)
{
	if (!ft_strcmp(cmds->cmd, "echou"))
		ft_echo(cmds->args);
	if (!ft_strcmp(cmds->cmd, "pwd"))
		ft_pwd(cmds);
	if (!ft_strcmp(cmds->cmd, "exit"))
		ft_exit(data, cmds);
	if (!ft_strcmp(cmds->cmd, "env"))
		ft_env(data);
	if (!ft_strcmp(cmds->cmd, "export"))
		ft_export(data, cmds->args);
	if (!ft_strcmp(cmds->cmd, "cd"))
		ft_cd(cmds, data);
}

int	ft_is_a_built_in(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "echou"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "cd"))
		return (1);
	return (0);
}
