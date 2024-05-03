/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:54:22 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/03 15:22:39 by skiam            ###   ########.fr       */
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
	char	*exp_value;
	t_token	*new_token;

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
	if (!(exp_value = ft_remove_quotes(ft_expand(data, value))))
		return (ft_free_ptr(value), -1);
	ft_free_ptr(value);
	new_token = ft_lstnew_token(exp_value, WORD);
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
