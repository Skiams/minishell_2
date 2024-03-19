/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:54:22 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/19 18:54:49 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_check_dollar(t_env *env, t_token *token_lst)
{
	int	i;

	i = 0;
	while (token_lst->value[i] != '\0')
	{
		if (token_lst->value[i] == '$')
		{
			while (token_lst->value[i] != '\0')
			{
				
			}
		}
	}
}
void	ft_replace_token_var(t_env *env, t_token *token_lst)
{
	char	*tmp_var;

	
	while (token_lst)
	{
		if (token_lst->value[0] == '$' && )
	}
}
int		ft_add_sep(t_token **token_lst, int type, char *str, int i)
{
	int		len;
	char	*value;
	t_token	*new_token;

	if (type == HEREDOC || type == APPEND)
		len = 2;
	else
		len = 1;
	value = ft_substr(str, i, len);
	i += len;
	new_token = ft_lstnew_token(value, type);
	ft_lstadd_back_token(token_lst, new_token);
	return (i);
}

int	ft_add_word(t_token **token_lst, char *str, int i)
{
	int		len;
	int		start;
	char	*value;
	t_token	*new_token;

	start = i;
	len = 0;
	if (str[i] && (str[i] == '\'' || str[i] == '"'))
	{
		i = ft_check_end_quotes(str, i, str[i]);
		if (i == 0)
			return (ft_error_quotes(), -1);
		len = i - start;
	}
	else
	{
		while (str[i] && !ft_is_sep(str, i)
			&& (str[i] != '\'' && str[i] != '"'))
		{
			i++;
			len++;
		}
	}
	//dprintf(2, "len = %d\n", len);
	value = ft_substr(str, start, len);
	//dprintf(2, "value = %s\n", value);
	new_token = ft_lstnew_token(value, WORD);
	ft_lstadd_back_token(token_lst, new_token);
	return (i);
}

int	ft_add_token(t_data *data, char *str, int type, int i)
{
	if (type > 0 && type < 6)
		i = ft_add_sep(&data->token_list, type, str, i);
	else if (type == 6)
		i = ft_add_word(&data->token_list, str, i);
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
	while (str[i] != '\0')
	{
		token_tp = ft_define_token_type(str, i);
		i = ft_add_token(data, str, token_tp, i);
		//dprintf(2, "index = %d\n", i);
		//dprintf(2, "token type = %d\n", token_tp);
		print_tokens(data->token_list);
		if (i == -1)
			return (false);
	}
	ft_free_ptr(str);
	return (true);
}