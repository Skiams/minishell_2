/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:00:04 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/24 15:26:37 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_c(char *s1, char *s2, char c)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!res)
		return (NULL);
	while (s1[j] != '\0')
		res[i++] = s1[j++];
	res[i++] = c;
	j = 0;
	while (s2[j] != '\0')
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	**ft_lst_to_tab(t_data *data)
{
	int		i;
	int		j;
	t_env	*tmp;
	char	**tab;

	tmp = data->env;
	i = 0;
	j = -1;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	tab = malloc(sizeof(char **) * (i + 1));
	if (!tab)
		return (ft_exit_code(12, ADD), NULL);
	tmp = data->env;
	while (j++ < i && tmp)
	{
		tab[j] = ft_strjoin_c(tmp->var, tmp->value, '=');
		if (!tab[j])
			return (ft_exit_code(12, ADD), NULL);
		tmp = tmp->next;
	}
	return (tab);
}

static bool	ft_lstinit_env(t_env **env, char *var, char *value)
{
	t_env	*new_env_var;

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
	if (!env)
		return (NULL);
	while (env && env[i])
	{
		j = 0;
		k = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		tmp_var = ft_substr(env[i], k, j);
		if (!tmp_var)
			return (NULL);
		j++;
		k = j;
		while (env[i][j] != '\0')
			j++;
		tmp_value = ft_substr(env[i], k, (j - k));
		if (!tmp_value)
			return (ft_exit_code(12, ADD), NULL);
		if (!ft_lstinit_env(&data->env, tmp_var, tmp_value)
			|| !tmp_var || !tmp_value)
			ft_exit_code(12, ADD);
		// est-ce qu'il faut exit ou pas la ?
		i++;
	}
	return (data->env);
}
