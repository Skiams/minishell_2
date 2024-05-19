/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:12:16 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/19 21:18:57 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_strncmp_exec(char **env, char *str, int n)
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

void	ft_get_path(t_cmds *cmds, char **env)
{
	cmds->env_path = ft_strncmp_exec(env, "PATH=", 5);
	if (cmds->env_path)
	{
		cmds->cmd_path = ft_split_exec(cmds->env_path);
		if (!cmds->cmd_path)
			return ;
	}
	else
		cmds->cmd_path = NULL;
}
