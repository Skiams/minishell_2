/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/20 14:28:11 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(t_data *data, t_cmds *tmp, char *cmd, char *error)
{
	t_cmds	*cmds;

	cmds = tmp;
	ft_putstr_fd("ft_free\n\n", 2);
	if (cmds->name)
	{
		free(cmds->name);
		dprintf(2, "oui, jai une tab\n");
	}
	//if (!cmds->redir || cmds->redir->type != 2)
//	{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
//	}
	while (cmds && cmds != NULL)
	{
		ft_free_tab(cmds->cmd_path);
		cmds->cmd_path = NULL;
		cmds = cmds->next;
	}
	dprintf(2, "on est avant le clean all de ft free\n");
	ft_clean_all(data);
}


char	*ft_get_absolute_path(t_data *data, t_cmds *cmds, char *cmd, char **args)
{
	char	*tmp;
	(void)data;

	tmp = ft_strjoin(cmd, "/");
	if (!tmp)
		return (NULL);
	if (access(tmp, F_OK) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": IIIIII  No such file or directory\n", 2);
		free(tmp);
		ft_free_tab(args);
		ft_free_tab(cmds->cmd_path);
		exit (126);
	}
	free(tmp);
	return (ft_strdup(cmd));
}

static int	ft_is_a_directory(char *argv)
{
	char	*tmp;

	tmp = ft_strjoin(argv, "/");
	if (!tmp)
		return (1);
	if (access(tmp, F_OK) == 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

static char	*ft_handle_path(t_data *data, t_cmds *cmds, char *cmd, int i)
{
	char	*tmp;
	char	*tmp2;
	
	while (cmds->cmd_path && cmds->cmd_path[i])
	{
		tmp = ft_strjoin(cmds->cmd_path[i++], "/");
		if (!tmp)
			return (NULL);
		tmp2 = ft_strjoin(tmp, cmd);
		if (!tmp2)
			return (free(tmp), NULL);
		free(tmp);
		if (access(tmp2, F_OK) == 0)
		{
			if (access(tmp2, X_OK) == 0)
				return (tmp2);
			else
				ft_handle_rights(data, cmds, cmd, tmp2);
		}
		free(tmp2);
	}
	ft_free(data, cmds, cmd, "IIIII command not found\n");
	exit (ft_exit_code(127, ADD));
}

char	*ft_get_cmd_path(t_data *data, t_cmds *cmds, char *cmd, char **args)
{
	int	i;

	i = 0;
	if (access(cmd, F_OK) == -1 && ft_strchr(cmd, '/'))
		ft_handle_no_file_or_dir(data, cmds, cmd, args);
	if (access(cmd, F_OK) == 0 && (ft_strchr(cmd, '/')
			|| (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
			|| (cmd[0] == '.' && cmd[1] == '/')))
	{
		if (ft_is_a_directory(cmd))
			ft_handle_directory(data, cmds, cmd, args);
		if (access(cmd, X_OK) != 0)
			ft_handle_rights(data, cmds, cmd, NULL);
		else
			return (ft_get_absolute_path(data, cmds, cmd, args));
		return (NULL);
	}
	return (ft_handle_path(data, cmds, cmd, i));
}
