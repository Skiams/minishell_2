/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:08:34 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/19 19:18:46 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static bool ft_replace_var(t_data *data, t_token *token, char *str, int start)
// {
// 	t_env	*tmp;
// 	char	*expanded_value;
// 	int		len;
// 	int		i;
// 	size_t	j;

// 	j = 0;
// 	i = 0;
// 	tmp = data->env;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(str, tmp->var) == 0)
// 		{
// 			len = ft_strlen(token->value) - ft_strlen(str) - 1 + ft_strlen(tmp->value);
// 			expanded_value = malloc(sizeof(char) * len + 1);
// 			if (!expanded_value)
// 				return (ft_exit_code(12, ADD), false);
// 			while (i < start)
// 			{
// 				expanded_value[i] = token->value[i];
// 				i++;
// 			}
// 			while (j < ft_strlen(tmp->value))
// 			{
// 				expanded_value[i] = tmp->value[j];
// 				i++;
// 				j++;
// 			}
// 			start += ft_strlen(str) + 1;
// 			while (i < len)
// 			{
// 				expanded_value[i] = token->value[start];
// 				i++;
// 				start++;
// 			}
// 			free(token->value);
// 			token->value = malloc(sizeof(char) * len + 1);
// 			if (!token->value)
// 				return (ft_exit_code(12, ADD), false);
// 			token->value = expanded_value;
// 			//free (expanded_value);
// 			return (true);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (true);
// }

// static bool	ft_exp_no_quotes(t_data *data, t_token *token)
// {
// 	int		i;
// 	int		start;
// 	char	*tmp_str;
	
// 	tmp_str = NULL;
// 	i = 0;
// 	start = 0;
// 	while (token->value[i])
// 	{
// 		if (token->value[i] == '$')
// 		{
// 			start = i + 1;
// 			while (token->value[i] && token->value[i] != '$')
// 				i++;
// 			tmp_str = ft_substr(token->value, start, (i - start));
// 			if (!tmp_str)
// 				return (ft_exit_code(12, ADD), false);
// 			if (!ft_replace_var(data, token, tmp_str, start))
// 				return (false);
// 			else
// 				return (true);
// 		}
// 		i++;
// 	}
// 	if (tmp_str)
// 		free(tmp_str);
// 	return (true);
// }

// static bool	ft_is_quotes(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

// bool	ft_expand(t_data *data)
// {
// 	t_token	*tmp;
	
// 	tmp = data->token_list;
// 	while (tmp)
// 	{
// 		if (ft_strchr(tmp->value, '$') == 1)
// 		{
// 			// if (ft_is_quotes(tmp->value) && !ft_exp_quotes(data, tmp))
// 			// 	return (false);
// 			if (!ft_is_quotes(tmp->value) && !ft_exp_no_quotes(data, tmp))
// 				return (false);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (true);
// }

