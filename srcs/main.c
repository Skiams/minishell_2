/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:18:15 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/14 21:13:53 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

int			g_sig_exit;

static bool	ft_parsing(char *str, t_data *data)
{
	if (str)
		add_history(str);
	if (ft_is_only_spacetab(str))
		return (false);
	if (!ft_tokenization(data))
		return (false);
	if (ft_check_syntax(data) != 0)
		return (false);
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
static t_env	*ft_no_env(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!ft_lstinit_env(&data->env, "SHLVL", "1"))
		return (ft_exit_code(12, ADD), NULL);
	if (!ft_lstinit_env(&data->env, "PWD", pwd))
		return (ft_exit_code(12, ADD), NULL);
	if (!ft_lstinit_env(&data->env, "_", "/usr/bin/env"))
		return (ft_exit_code(12, ADD), NULL);
	return (data->env);
}

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
	// ft_init_struct(&data_env, data.cmd_list, data.token_list,
	//	data.cmd_list->redir);
	if (env)
	{
		dprintf(2, "l'env existe\n");
		data.env = ft_get_env(&data, env);
	}
	else
	{
		dprintf(2, "on est bien dans le no env\n");
		data.env = ft_no_env(&data);
	}
	if (ft_exit_code(0, GET) == 12)
		return (ft_free_data(&data), 12);
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
			ft_exec(&data, data.cmd_list, env);
		else if (ft_exit_code(0, GET) == 12)
			break ;
//		print_tokens(data.token_list);
		/*
				ft_putstr_fd("⚠️ ⚠️ ⚠️  Supprimer print_tokens() et print_cmds() pour tester les redirections sinon ca peut generer des leaks ou segfault\n",
					1);
				print_tokens(data.token_list);
				print_cmds(data.cmd_list);
		*/
		//print_tokens(data.token_list);
		//	print_cmds(data.cmd_list);
		dprintf(2, "Coucou, on a perdu l'entree standard\n");
		ft_free_data(&data);
	}
	ft_clean_all(&data);
	return (ft_exit_code(0, GET));
}
