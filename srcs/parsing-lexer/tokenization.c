/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:54:22 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/22 18:53:54 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_add_sep(t_token **token_lst, int type, char *str, int i)
{
	int		len;
	char	*value;
	t_token	*new_token;

	if (type == HEREDOC || type == APPEND)
		len = 2;
	else
		len = 1;
	value = ft_substr(str, i, len);
	if (!value)
		return (ft_exit_code(12, ADD), -1);
	i += len;
	new_token = ft_lstnew_token(value, type);
	if (!new_token)
		return (ft_exit_code(12, ADD), -1);
	ft_lstadd_back_token(token_lst, new_token);
	return (i);
}

int	ft_add_word(t_data *data, t_token **token_lst, char *str, int i)
{
	int		len;
	int		start;
	int		start_quote;
	char	*value;
	t_token	*new_token;
	int		dollar_nb;

	dollar_nb = 0;
	start = i;
	len = 0;
	while (str[i] && !ft_is_sep(str, i))
	{
		if (str[i] && (str[i] == '\'' || str[i] == '"'))
		{
			start_quote = i;
			i = ft_check_end_quotes(str, i, str[i]);
			if (i == 0)
				return (ft_error_quotes(), -1);
			else
				len += i - start_quote;
		}
		else
		{
			i++;
			len++;
		}
	}
	value = ft_substr(str, start, len);
	if (!value)
		return (ft_exit_code(12, ADD), -1);
	dollar_nb = ft_check_dollar(value);
	while (dollar_nb-- > 0)
	{
		value = ft_expand(data, value);
		dprintf(2, "value de la boucle = %s\n", value);
	}
	new_token = ft_lstnew_token(value, WORD);
	if (!new_token)
		return (ft_exit_code(12, ADD), -1);
	ft_lstadd_back_token(token_lst, new_token);
	return (i);
}

int	ft_add_token(t_data *data, char *str, int type, int i)
{
	if (type > 0 && type < 6)
		i = ft_add_sep(&data->token_list, type, str, i);
	else if (type == 6)
		i = ft_add_word(data, &data->token_list, str, i);
	else
		i++;
	return (i);
}

bool	ft_tokenization(t_data *data)
{
	int		i;
	int		token_tp;
	char	*str;

	token_tp = 0;
	i = 0;
	str = ft_del_edge_spaces(data->input);
	if (!str)
		return (false);
	while (str[i] != '\0')
	{
		token_tp = ft_define_token_type(str, i);
		i = ft_add_token(data, str, token_tp, i);
		if (i == -1)
			return (ft_free_ptr(str), false);
	}
	ft_free_ptr(str);
	return (true);
}


// static char	*ft_replace_var_exp(t_data *data, char *str)
// {
// 	t_env	*tmp;
// 	char	*expanded_value;
	
// 	tmp = data->env;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(str, tmp->var) == 0)
// 		{
// 			expanded_value = ft_substr(tmp->value, 0, ft_strlen(tmp->value));
// 			if (!expanded_value)
// 				return (ft_exit_code(12, ADD), NULL);
// 			else
// 				return (free(str), expanded_value);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }
// char	*ft_expand_value(t_data *data, char *str, int *i)
// {
// 	int		len;
// 	int		start;
// 	char	*var;
// 	char	*expanded_value;
	
// 	(*i)++;
// 	len = 0;
// 	start = *i;
// 	dprintf(2, "on est dans expand value\n");
// 	while (str[*i] && str[*i] != '$' && str[*i] != '\'' && str[*i] != '"')
// 	{
// 		(*i)++;
// 		len++;
// 	}
// 	dprintf(2, "expand avant substr\n");
// 	var = ft_substr(str, start, len);
// 	if (!var)
// 		return (ft_exit_code(12, ADD), NULL);
// 	dprintf(2, "var a check = %s\n", var);
// 	if (ft_var_is_in_env(data, var))
// 	{
// 		expanded_value = ft_replace_var_exp(data, var);
// 		if (!expanded_value)
// 			return (ft_exit_code(12, ADD), NULL);
// 	}
// 	else
// 	{
// 		free(var);
// 		expanded_value = malloc(sizeof(char));
// 		expanded_value[0] = '\0';
// 		dprintf(2, "dernier else de l'export\n");
// 	}
// 	dprintf(2, "expanded value = %s\n", expanded_value);
// 	return (expanded_value);
// }

// int	ft_add_sep(t_token **token_lst, int type, char *str, int i)
// {
// 	int		len;
// 	char	*value;
// 	t_token	*new_token;

// 	if (type == HEREDOC || type == APPEND)
// 		len = 2;
// 	else
// 		len = 1;
// 	value = ft_substr(str, i, len);
// 	if (!value)
// 		return (ft_exit_code(12, ADD), -1);
// 	i += len;
// 	new_token = ft_lstnew_token(value, type);
// 	if (!new_token)
// 		return (ft_exit_code(12, ADD), -1);
// 	ft_lstadd_back_token(token_lst, new_token);
// 	return (i);
// }

// int	ft_add_word(t_data *data, t_token **token_lst, char *str, int i)
// {
// 	int		len;
// 	int		start;
// 	int		start_quote;
// 	char	*value;
// 	char	*expanded_value;
// 	char	*tmp_value;
// 	t_token	*new_token;

// 	start = i;
// 	len = 0;
// 	while (str[i] && !ft_is_sep(str, i))
// 	{
// 		if (str[i] && (str[i] == '\'' || str[i] == '"'))
// 		{
// 			start_quote = i;
// 			i = ft_check_end_quotes(str, i, str[i]);
// 			if (i == 0)
// 				return (ft_error_quotes(), -1);
// 			else
// 				len += i - start_quote;
// 		}
// 		else if (str[i] == '$')
// 		{
// 			dprintf(2, "on a trouve un $\n");
// 			if (i != 0)
// 			{
// 				dprintf(2, "i != 0\n");
// 				if (str[i - 1] != 32 && str[i - 1] != 9 && !ft_is_sep(str, i - 1))
// 				{
// 					tmp_value = ft_substr(str, start, len);
// 					if (!tmp_value)
// 						return (ft_exit_code(12, ADD), -1);
// 				}
// 			}
// 			expanded_value  = ft_expand_value(data, str, &i);
// 			dprintf(2, "expanded value apres ft_expand = %s\n", expanded_value);
// 			if (!expanded_value)
// 			{
// 				if (tmp_value)
// 					free(tmp_value);
// 				return (-1);
// 			}
// 			expanded_value = ft_strjoin(tmp_value, expanded_value);
// 			if (!expanded_value)
// 				return (ft_exit_code(12, ADD), -1);
// 		}
// 		else
// 		{
// 			i++;
// 			len++;
// 		}
// 	}
// 	value = ft_substr(str, start, len);
// 	if (!value)
// 		return (ft_exit_code(12, ADD), -1);
// 	new_token = ft_lstnew_token(value, WORD);
// 	if (!new_token)
// 		return (ft_exit_code(12, ADD), -1);
// 	ft_lstadd_back_token(token_lst, new_token);
// 	return (i);
// }

// int	ft_add_token(t_data *data, char *str, int type, int i)
// {
// 	if (type > 0 && type < 6)
// 		i = ft_add_sep(&data->token_list, type, str, i);
// 	else if (type == 6)
// 		i = ft_add_word(data, &data->token_list, str, i);
// 	else
// 		i++;
// 	return (i);
// }

// bool	ft_tokenization(t_data *data)
// {
// 	int		i;
// 	int		token_tp;
// 	char	*str;

// 	token_tp = 0;
// 	i = 0;
// 	str = ft_del_edge_spaces(data->input);
// 	if (!str)
// 		return (false);
// 	while (str[i] != '\0')
// 	{
// 		token_tp = ft_define_token_type(str, i);
// 		i = ft_add_token(data, str, token_tp, i);
// 		if (i == -1)
// 			return (ft_free_ptr(str), false);
// 	}
// 	ft_free_ptr(str);
// 	return (true);
// }
