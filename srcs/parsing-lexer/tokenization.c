/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:54:22 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/09 16:06:45 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_add_sep(t_token **token_lst, int type, char *str, int i)
{
	int		len;
	char	*value;
	t_token	*new_token;

	if (type == HEREDOC || type == APPEND || type == IN_AND_OUT)
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
	char	*exp_value;
	t_token	*new_token;
	t_token	*tmp;

	start = i;
	len = 0;
	tmp = ft_lstlast_token(*token_lst);
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
	if (!(value = ft_substr(str, start, len)))
		return (ft_exit_code(12, ADD), -1);
	if (tmp && tmp->type == HEREDOC)
	{
		exp_value = ft_remove_quotes(value, 0);
		if (!exp_value)
			return (ft_free_ptr(value), -1);
	}
	else
		exp_value = ft_remove_quotes(ft_expand(data, value), 1);
	if (!exp_value)
		return (ft_free_ptr(value), -1);
	//dprintf(2, "exp value = %s\n", exp_value);
//	dprintf(2, "expand code = %d\n", ft_expand_code(0, GET));
	ft_free_ptr(value);
	if (ft_expand_code(0, GET) == 1 && ft_check_space_expand(exp_value))
	{
		dprintf(2, "on est dans le exp token\n");
		if (!ft_add_exp_token(token_lst, exp_value) && ft_exit_code(0, GET) == 12)
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
	return (i);
}

int	ft_add_token(t_data *data, char *str, int type, int i)
{
	if (type > 0 && type < 7)
		i = ft_add_sep(&data->token_list, type, str, i);
	else if (type == 7)
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
		dprintf(2, "token_tp = %i\n", token_tp);
		i = ft_add_token(data, str, token_tp, i);
		if (i == -1)
			return (ft_free_ptr(str), false);
	}
	ft_free_ptr(str);
	return (true);
}
