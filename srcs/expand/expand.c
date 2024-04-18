/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:08:34 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/18 20:02:31 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// bool	ft_expand(t_data *data)
// {
	
// }

// static bool	ft_replace_env_var(t_data *data, t_token *token, char *new_value)
// {
// }


// bool	ft_check_expand(t_data *data)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp_var;
// 	t_token	*tmp;

// 	tmp = data->token_list;
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (tmp->value[i] != '\0')
// 		{
// 			if (tmp->value[i] == '$')
// 			{
// 				i++;
// 				j = i;
// 				while (tmp->value[i] != '\0'
// 					&& tmp->value[i] != '$')
// 					i++;
// 				tmp_var = ft_substr(tmp->value, j, i - j);
// 				if (!tmp_var)
// 					return (ft_exit_code(12, ADD), false);
// 				dprintf(2, "tmp_var = %s\n", tmp_var);
// 				if (ft_var_is_in_env(data, tmp_var))
// 					;
// 			}
// 			else
// 				i++;
// 		}
// 		tmp = tmp->next;
// 	}
// }
