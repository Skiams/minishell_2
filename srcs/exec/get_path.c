/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:12:16 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/05 18:17:38 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strncmp(char **env, char *str, int n)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		j = 0;
		k = 0;
		while (env[i][j] == str[k] && k <= n)
		{
			j += 1;
			k += 1;
			if (k == n)
				return (&env[i][j]);
		}
		i += 1;
	}
	return (NULL);
}

void	ft_get_path(t_pipex *pipex, char **env)
{
	pipex->env_path = ft_strncmp(env, "PATH=", 5);
	if (pipex->env_path)
	{
		pipex->cmd_path = ft_split(pipex->env_path);
		if (!pipex->cmd_path)
			return ;
	}
	else
		pipex->cmd_path = NULL;
}
