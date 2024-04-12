/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:34:32 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/12 19:43:19 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	set_new_cmd(t_data *data, t_token **token_lst)
{
	t_cmds	*new_cmd;

	if (!(*token_lst)->prev || (*token_lst)->type == PIPE)
	{
		new_cmd = lst_new_cmd();
		if (!new_cmd)
			return (false);
		lst_add_back_cmd(&data->cmd_list, new_cmd);
		if ((*token_lst)->type == PIPE)
			(*token_lst) = (*token_lst)->next;
	}
	return (true);
}

// bool	ft_get_cmds(t_data *data, t_token **token_lst)
// {
	
// }

// char	**ft_get_cmds(t_data *data)
// {
// 	char	**tab;
// 	t_token	*tmp;
// 	int		i;
// 	int		j;
// 	char	*str;

// 	tmp = data->token_list;
// 	if (!tmp)
// 		return (NULL);
// 	i = 1;
// 	j = 0;
// 	while (tmp)
// 	{
// 		if (tmp->type == PIPE)
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	tab = malloc(sizeof(char **) * (i + 1));
// 	if (!tab)
// 		return (ft_exit_code(12, ADD), NULL);
// 	tmp = data->token_list;
// 	while (j < i && tmp)
// 	{
// 		tab[j] = ft_substr(tmp->value, 0, ft_strlen(tmp->value));
// 		if (!tab[j])
// 			return (ft_exit_code(12, ADD), NULL);
// 		while (tmp->next && tmp->type != PIPE && tmp->next->type != PIPE)
// 		{
// 			str = ft_strjoin_c(tab[j], tmp->next->value, 32);
// 			if (!str)
// 				return (ft_exit_code(12, ADD), NULL);
// 			free(tab[j]);
// 			tab[j] = str;
// 			tmp = tmp->next;
// 		}
// 		if (tmp->next != NULL && tmp->next->type == PIPE)
// 			tmp = tmp->next->next;
// 		else
// 			tmp = tmp->next;
// 		j++;
// 	}
// 	tab[j] = NULL;
// 	return (tab);
// }
