/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:00:04 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/19 13:36:22 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_lstinit_env(t_env **env, char *var, char *value)
{
	t_env *new_env_var;

	new_env_var = ft_lstnew_env(var, value);
	ft_lstadd_back_env(env, new_env_var);
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
		ft_lstinit_env(&data->env, tmp_var, tmp_value);
		i++;
	}
	return (data->env);
}
