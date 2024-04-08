/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:18:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/08 19:38:02 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sig_exit;

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
	if (ft_check_syntax(data) != 0)
		return (false);
	//ft_check_expand(data);
	//ft_set_cmd(data, data->token_list);
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)env;
	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	data.env = ft_get_env(&data, env);
	// if (env)
	// 	data.env = ft_get_env(&data, env);
	// else
	// 	data.env = NULL;
	// if (ft_exit_code(0, GET) == 1)
	// 	return (ft_free_data(&data), 1);
	// a rajouter pour le get_env ?
	while (1)
	{
		data.input = readline("minishell: ");
		// if (!data.input)
		// 				(ft_putstr_fd("exit\n", 1), exit(1));
		ft_parsing(data.input, &data);
		// if (ft_parsing(data.input, &data))
			// 	//gogo gadgeto exe;
		print_tokens(data.token_list);
		ft_free_data(&data);
	}
	ft_clean_all(&data);
	return (ft_exit_code(0, GET));
}
