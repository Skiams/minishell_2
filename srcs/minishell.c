/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:18:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/13 18:40:11 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static bool	ft_first_check(t_data *data)
// {
// 	if (ft_is_only_space(str) == true)
// 		return un truc d'erreur t'sais;	
// 	if (!str)
// 		return un truc d'erreur t'sais;
// }

static bool	ft_parsing(char *str, t_data *data)
{
	if (str)
		add_history(str);
	// if (ft_first_check(str))
	// 	return (false);
	if (!ft_tokenization(data))
		return (false);
	if (!check_syntax(data, str))
		return (false);
	print_tokens(data->token_list);
	//ft_set_cmd(data, data->token_list);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	while (1)
	{
		data.input = readline("entre un truc batard : ");
		if (ft_parsing(data.input, &data))
			// if (ft_set_cmd(&data, data.token_list))
			// 	//gogo gadgeto exe;
		ft_free_data(&data);
	}
	return (0);
}
