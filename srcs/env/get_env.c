/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:00:04 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/08 20:59:36 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	**ft_lstenv_to_tab(t_env *env)
// {
// 	int	i;

// 	i = 0;
// 	while (env)
// 	{
		
// 	}
// }

static bool	ft_lstinit_env(t_env **env, char *var, char *value)
{
	t_env *new_env_var;

	new_env_var = ft_lstnew_env(var, value);
	if (!new_env_var)
		return (false);
	ft_lstadd_back_env(env, new_env_var);
	return (true);
}
t_env	*ft_get_env(t_data *data, char **env)
{
	char	*tmp_var;
	char	*tmp_value;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (env[i])
	{
		j = 0;
		k = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		tmp_var = ft_substr(env[i], k, j);
		j++;
		k = j;
		while (env[i][j] != '\0')
			j++;
		tmp_value = ft_substr(env[i], k, (j - k));
		if (!ft_lstinit_env(&data->env, tmp_var, tmp_value) || !tmp_var || !tmp_value)
			ft_exit_code(1, ADD);
		// est-ce qu'il faut exit ou pas la ?
		i++;
	}
	return (data->env);
}
