/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/17 16:26:54 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(t_pipex *pipex, char *argv, char **path, char *error)
{
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_free_tab(path);
	ft_free_tab(pipex->cmd_path);
}

void	ft_free2(t_cmds *cmds, char *argv, char **path, char *error)
{
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_free_tab(path);
	ft_free_tab(cmds->cmd_path);
}

char	*ft_get_absolute_path(t_pipex *pipex, char *argv, char **path)
{
	char	*tmp;

	tmp = ft_strjoin(argv, "/");
	if (!tmp)
		return (NULL);
	if (access(tmp, F_OK) == 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(tmp);
		ft_free_tab(path);
		ft_free_tab(pipex->cmd_path);
		exit (126);
	}
	free(tmp);
	return (ft_strdup(argv));
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

char	*ft_handle_path(t_pipex *pipex, char *argv, char **path, int i)
{
	char	*tmp;
	char	*tmp2;

	if (pipex->is_here_doc)
		i += 1;
	while (pipex->cmd_path && pipex->cmd_path[i])
	{
		tmp = ft_strjoin(pipex->cmd_path[i++], "/");
		if (!tmp)
			return (NULL);
		tmp2 = ft_strjoin(tmp, argv);
		if (!tmp2)
			return (free(tmp), NULL);
		free(tmp);
		if (access(tmp2, F_OK) == 0)
		{
			if (access(tmp2, X_OK) == 0)
				return (tmp2);
			else
				ft_handle_rights(pipex, argv, path, tmp2);
		}
		free(tmp2);
	}
	ft_free(pipex, argv, path, "command not found\n");
	exit (127);
}

char	*ft_handle_path2(t_cmds *cmds, char *argv, char **path, int i)
{
	char	*tmp;
	char	*tmp2;

/*
	ft_printf(1, "ft_handle_path2()\n");
	ft_printf(1, "ft_handle_path2(), i vaut:\t%d\n\n", i);
	ft_printf(1, "FT_HANDLE_PATH2\targv\t%s\n", argv);
//	if (cmds->is_here_doc)
//		i += 1;
	int	j = 0;
	  while (cmds->cmd_path[j])
        {
                ft_printf(1, "cmds->cmd_path[%d]:\t%s\n", j, cmds->cmd_path[j]);
                j += 1;
        }
*/
	while (cmds->cmd_path && cmds->cmd_path[i])
	{
//		ft_printf(1, "while loop\n");
		tmp = ft_strjoin(cmds->cmd_path[i++], "/");
		if (!tmp)
			return (NULL);
		tmp2 = ft_strjoin(tmp, argv);
		if (!tmp2)
			return (free(tmp), NULL);
		free(tmp);
		if (access(tmp2, F_OK) == 0)
		{
			if (access(tmp2, X_OK) == 0)
				return (tmp2);
			else
				ft_handle_rights2(cmds, argv, path, tmp2);
		}
		free(tmp2);
	}
	ft_printf(1, "je passe ici\n");
	ft_free2(cmds, argv, path, "command not found\n");
	exit (127);
}

char	*ft_get_cmd_path2(t_cmds *cmds, char *argv, char **path)
{
	int	i;

	(void)path;
//	(void)pipex;
	(void)cmds;
	i = 0;
	if (access(argv, F_OK) == -1 && ft_strchr(argv, '/'))
//		ft_handle_no_file_or_dir(argv);
		ft_printf(1, "premier if\n");
	if (access(argv, F_OK) == 0 && (ft_strchr(argv, '/')
			|| (argv[0] == '.' && argv[1] == '.' && argv[2] == '/')
			|| (argv[0] == '.' && argv[1] == '/')))
	{
		ft_printf(1, "deuxieme if\n");
		return (NULL);
	/*	if (ft_is_a_directory(argv))
			ft_handle_directory(cmds, argv, path);
		if (access(argv, X_OK) != 0)
			ft_handle_rights(cmds, argv, path, NULL);
		else
			return (ft_get_absolute_path(cmds, argv, path));
	*/
	}
	ft_printf(1, "aucun des deux if\n");
	ft_printf(1, "argv\t%s\n", argv);
	int	j =0;
	while(path[j])
	{
		ft_printf(1, "path[%d]:\t%s\n", j, path[j]);
		j += 1;
	}
//	return (NULL);
	return (ft_handle_path2(cmds, argv, path, i));
}

char	*ft_get_cmd_path(t_pipex *pipex, char *argv, char **path)
{
	int	i;

	i = 0;
	if (access(argv, F_OK) == -1 && ft_strchr(argv, '/'))
		ft_handle_no_file_or_dir(argv);
	if (access(argv, F_OK) == 0 && (ft_strchr(argv, '/')
			|| (argv[0] == '.' && argv[1] == '.' && argv[2] == '/')
			|| (argv[0] == '.' && argv[1] == '/')))
	{
		if (ft_is_a_directory(argv))
			ft_handle_directory(pipex, argv, path);
		if (access(argv, X_OK) != 0)
			ft_handle_rights(pipex, argv, path, NULL);
		else
			return (ft_get_absolute_path(pipex, argv, path));
	}
	return (ft_handle_path(pipex, argv, path, i));
}
