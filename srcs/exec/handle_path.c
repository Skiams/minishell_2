/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/19 17:03:50 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(t_pipex *pipex, char *argv, char **path, char *error)
{
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_free_tab(path);
	ft_free_tab(pipex->cmd_path);
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
	int		i;
	char	*tmp;

	i = 0;
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

	while (pipex->cmd_path && pipex->cmd_path[i])
	{
		tmp = ft_strjoin(pipex->cmd_path[i], "/");
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
		i += 1;
	}
	ft_free(pipex, argv, path, "command not found\n");
	exit (127);
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
