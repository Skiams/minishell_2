/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:54:22 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/08 13:29:12 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	while (str[i] && !ft_is_whitespace(str, i) && !ft_is_sep(str, i))
	{
		i++;
		len++;
	}
	value = ft_substr(str, start, len);
	new_token = ft_lstnew_token(value, WORD);
	ft_lstadd_back_token(token_lst, new_token);
	return (i);
}

int	ft_add_token(t_data *data, char *str, int type, int i)
{
	dprintf(2, "i dans add token = %d\n", i);
	if (type > 0 && type < 6)
		i = ft_add_sep(&data->token_list, type, str, i);
	else
		i = ft_add_word(&data->token_list, str, i);
	dprintf(2, "i a la sortie de add token = %d\n", i - 1);
	return (i);
}

int	ft_define_token_type(char *str, int i)
{
	if (str[i] == '|')
		return (PIPE);
	if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	if (str[i] == '<')
		return (RED_IN);
	if (str[i] == '>')
		return (RED_OUT);
	else
		return (WORD);
}
