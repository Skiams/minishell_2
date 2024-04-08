/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:08:34 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/08 20:58:43 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static bool	ft_replace_env_var(t_data *data, t_token *token, char *new_value)
// {
	
// }
// // bool	ft_check_env_var(char *tmp_var, t_token *token, t_data *data)
// // {
// // 	t_env	*tmp_env;

// // 	tmp_env = data->env;
// // 	while (tmp_env)
// // 	{
// // 		if (ft_strncmp(tmp_var, tmp_env->var, ft_strlen(tmp_var)) == 0)
// // 			ft_replace_env_var(data, token, tmp_env->value);
// // 		tmp_env = tmp_env->next;
// // 	}
// // 	return (false);
// // }
// bool	ft_check_expand(t_data *data)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp_var;
// //	t_token	*token;
	
// //	token = data->token_list;
// 	while (data->token_list)
// 	{
// 		i = 0;
// 		while (data->token_list->value[i] != '\0')
// 		{
// 			if (data->token_list->value[i] == '$')
// 			{
// 				i++;
// 				j = i;
// 				while (data->token_list->value[i] != '\0' && data->token_list->value[i] != '$')
// 					i++;
// 				tmp_var = ft_substr(data->token_list->value, j, i - j);
// 				if (!tmp_var)
// 					return (ft_exit_code(12, ADD), false);
// 				dprintf(2, "tmp_var = %s\n", tmp_var);
// 				if (ft_var_is_in_env(data, tmp_var))
// 					;
// 			}
// 			else
// 				i++;
// 		}
// 		data->token_list = data->token_list->next;
// 	}
// }
