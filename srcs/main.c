/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:18:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/24 17:50:37 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

int	g_sig_exit;

static bool	ft_parsing(char *str, t_data *data)
{
	if (str)
		add_history(str);
	if (ft_is_only_spacetab(str) == true)
		return (false);
	if (!ft_tokenization(data))
		return (false);
	if (ft_check_syntax(data) != 0)
		return (false);
	//if (!ft_expand(data))
	//	return (false);
	if (!ft_get_cmds(data, &data->token_list))
		return (false);
	return (true);
}

// void	ft_init_struct(t_env *env, t_cmds *cmds, t_token *token, t_redir *redir)
// {
// /*	t_env	env;
// 	t_redir	redir;
// 	t_cmds	cmds;
// 	t_token	token;
// */
// //	ft_memset(data, 0, sizeof(t_data));
// 	ft_memset(env, 0, sizeof(t_env));
// 	ft_memset(redir, 0, sizeof(t_redir));
// 	ft_memset(cmds, 0, sizeof(t_cmds));
// 	ft_memset(token, 0, sizeof(t_token));
// }

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	// t_env	data_env;
	// t_redir	redir;
	// t_cmds	cmds;
	// t_token	token;


	(void)argv;
	g_sig_exit = 0;
	if (argc != 1)
		ft_print_wrong_param();
	ft_memset(&data, 0, sizeof(t_data));
	// ft_init_struct(&data_env, data.cmd_list, data.token_list, data.cmd_list->redir);
	if (env)
		data.env = ft_get_env(&data, env);
	else
		data.env = NULL;
	if (ft_exit_code(0, GET) == 12)
		return (ft_free_data(&data), 12);
	// a rajouter pour le get_env ?
	while (1)
	{
		ft_handle_signal();
		data.input = readline("1️⃣   minishell$ ");
		if (!data.input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (ft_parsing(data.input, &data))
			ft_exec(&data, data.cmd_list, env, data.cmd_list->redir);
		else if (ft_exit_code(0, GET) == 12)
			break ;
//		print_tokens(data.token_list);
//		print_cmds(data.cmd_list);
		ft_free_data(&data);
	}
	ft_clean_all(&data);
	return (ft_exit_code(0, GET));
}
