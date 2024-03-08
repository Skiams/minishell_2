/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:18:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/08 15:58:24 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	ft_first_check(t_data *data)
// {
// 	// if (ft_is_only_space(str) == true)
// 	// 	return un truc d'erreur t'sais;	
// 	// if (!str)
// 	// 	return un truc d'erreur t'sais;
// }

static void	ft_parsing(char *str, t_data *data)
{
	if (str)
		add_history(str);
	//ft_first_check(data);
	ft_tokenization(data);
	print_tokens(data->token_list);
	//ft_set_cmd(data, data->token_list);
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
		ft_parsing(data.input, &data);
		ft_free_data(&data);
	}
	return (0);
}
