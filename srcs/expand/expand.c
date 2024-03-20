/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:08:34 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/20 23:42:44 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_check_env_var(char *tmp_var, t_env *env)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_var, tmp_env->var, ft_strlen(tmp_var)) == 0)
			return (true);
		tmp_env = tmp_env->next;
	}
	return (false);
}
void	ft_check_expand(t_data *data)
{
	int		i;
	int		j;
	char	*tmp_var;
	t_token	*token;
	
	token = data->token_list;
	dprintf(2, "on est dans le check expand\n");
	while (token)
	{
		i = 0;
		dprintf(2, "token type = %d, value = %s\n", token->type, token->value);
		while (token->value[i] != '\0')
		{
			//dprintf(2, "on parcourt la value du token\n");
			if (token->value[i] == '$')
			{
				dprintf(2, "on est tombe sur le $\n");
				i++;
				j = i;
				while (token->value[i] != '\0' && token->value[i] != '$')
					i++;
				tmp_var = ft_substr(token->value, j, i - j);
				dprintf(2, "tmp_var = %s\n", tmp_var);
				if (ft_check_env_var(tmp_var, data->env) == true)
				{
					dprintf(2, "ca a trouve la variable %s\n", tmp_var);
				}
			}
			else
				i++;
		}
		token = token->next;
	}
}
