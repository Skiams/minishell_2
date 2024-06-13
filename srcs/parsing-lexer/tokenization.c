/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:54:22 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/12 22:28:41 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_add_word_bis(char *str, int *i, int *len)
{
	int	start_quote;

	while (str[*i] && !ft_is_sep(str, *i))
	{
		if (str[*i] && (str[*i] == '\'' || str[*i] == '"'))
		{
			start_quote = *i;
			*i = ft_check_end_quotes(str, *i, str[*i]);
			if (*i == 0)
				return (ft_error_quotes(), -1);
			else
				*len += *i - start_quote;
		}
		else
		{
			(*i)++;
			(*len)++;
		}
	}
	return (0);
}

static int	ft_add_word_tri(t_token **token_lst, char *exp_value, char *value)
{
	t_token	*new_token;

	if (!exp_value)
		return (ft_free_ptr(value), ft_exit_code(12, ADD), -1);
	ft_free_ptr(value);
	if (ft_expand_code(0, GET) == 1 && ft_check_space_expand(exp_value))
	{
		if (!ft_add_exp_token(token_lst, exp_value) && ft_exit_code(0,
				GET) == 12)
			return (-1);
	}
	else
	{
		new_token = ft_lstnew_token(exp_value, WORD);
		if (!new_token)
			return (ft_exit_code(12, ADD), -1);
		ft_lstadd_back_token(token_lst, new_token);
	}
	ft_expand_code(0, ADD);
	return (0);
}

static int	ft_add_word(t_data *data, t_token **token_lst, char *str, int i)
{
	int		len;
	int		start;
	char	*value;
	char	*exp_value;
	t_token	*tmp;

	start = i;
	len = 0;
	tmp = ft_lstlast_token(*token_lst);
	if (ft_add_word_bis(str, &i, &len) == -1)
		return (ft_exit_code(2, ADD), -1);
	value = ft_substr(str, start, len);
	if (!value)
		return (ft_exit_code(12, ADD), -1);
	if (tmp && tmp->type == HEREDOC)
	{
		exp_value = ft_remove_quotes(value, 0);
		if (!exp_value)
			return (ft_free_ptr(value), free(exp_value), -1);
	}
	else
		exp_value = ft_remove_quotes(ft_expand(data, value), 1);
	if (ft_add_word_tri(token_lst, exp_value, value) == -1)
		return (-1);
	return (i);
}

static int	ft_add_token(t_data *data, char *str, int type, int i)
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
