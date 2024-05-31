/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:12:16 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/31 19:01:06 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_lstsize_env(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	if (!env)
		return (0);
	while (env != NULL)
	{
		env = env->next;
		i += 1;
	}
	env = tmp;
	return (i);
}

static char	**ft_return_tab_size(int size)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

char	**ft_return_mini_env(t_data *data, t_env *env)
{
	int		i;
	int		size;
	char	*var;
	char	*val;
	t_env	*tmp;

	tmp = env;
	i = 0;
	size = ft_lstsize_env(env);
	data->mini_env = ft_return_tab_size(size);
	if (!data->mini_env)
		return (NULL);
	data->mini_env[size] = NULL;
	while (env != NULL)
	{
		var = ft_strjoin(env->var, "=");
		val = ft_strjoin(var, env->value);
		if (!ft_strcmp(env->var, "PATH"))
			data->mini_env[i] = ft_fill_tab(val);
		else
			data->mini_env[i] = ft_fill_tab_colon(val);
		if (!data->mini_env[i])
			return (ft_free_tab(data->mini_env));
		ft_free_ptr(var);
		ft_free_ptr(val);
		i += 1;
		env = env->next;
	}
	env = tmp;
	return (data->mini_env);
}	

static char	*ft_strncmp_exec(t_data *data, char *str, int n)
{
	int	i;
	int	j;
	int	k;

	dprintf(2, " -> %s\n", __func__);
	i = 0;
	ft_return_mini_env(data, data->env);
	if (!data->mini_env)
		return (NULL);
	while (data->mini_env[i])
	{
		j = 0;
		k = 0;
		while (data->mini_env[i][j] == str[k] && k <= n)
		{
			j += 1;
			k += 1;
			if (k == n)
				return (&data->mini_env[i][j]);
		}
		i += 1;
	}
	return (NULL);
}

void	ft_get_path(t_data *data, t_cmds *cmds)
{
	cmds->env_path = ft_strncmp_exec(data, "PATH=", 5);
	if (cmds->env_path)
	{
		cmds->cmd_path = ft_split_exec(cmds->env_path);
		if (!cmds->cmd_path)
			return ;
	}
	else
		cmds->cmd_path = NULL;
}
