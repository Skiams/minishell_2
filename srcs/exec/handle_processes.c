/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/24 07:00:40 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_exit_properly2(t_data *data, t_cmds *cmds)
{
        ft_free_tab(cmds->cmd_path);
        ft_free_tab(data->mini_env);
        ft_clean_all(data);
        ft_exit_code(0, GET);
        exit (1);
}

void	ft_exec_cmds(t_data *data, t_cmds *cmds, char **env)
{
	/*t_data	*tmp;

	tmp = data;
	int	i =0;
	while (data->mini_env[i])
		dprintf(2, "mini_env\t%s\n", data->mini_env[i++]);
	data = tmp;
*/
	(void)env;
	// ici, c'est non, ca fait tout peter
//	close(cmds->here_doc);
	dprintf(2, "je passe dans exec_cmds\n");
	dprintf(2, "\n\ndans exec_cmds  => %d\n\n", cmds->here_doc);
	if (!cmds->args)
        {
            ft_dup_stdin_stdout(data, cmds);
            ft_handle_redir_without_cmd(data, cmds);
            ft_dup2_and_close_stdin_stdout(data, cmds);
			ft_exit_properly2(data, cmds);
        }
	if (cmds->redir)
	{
		dprintf(2, "je passe dans exec_cmds et j'ai un argument\n");
		//dprintf(2, "dans exec_cmds() cmds->name %s\n", cmds->name);
		ft_handle_redir(data, cmds);
		// ici ca ne change rien
	//	close(cmds->here_doc);
	//	dprintf(2, "dans exec_cmds() cmds->name %s\n", cmds->name);
	}
	if (ft_is_a_built_in(cmds->cmd))
	{
		ft_exec_built_in(data, cmds);
		ft_exit_properly2(data, cmds);
	}
	dprintf(2, "coucou, je suis la\n");
	cmds->right_path = ft_get_cmd_path(data, cmds, cmds->cmd, cmds->args);
	dprintf(2, "\n\nLe fucking right path : %s\n", cmds->right_path);
// ca ne sert a rien, cmds->here_doc n'est pas a -1 ici
dprintf(2, "\n\ndans exec_cmds  => %d\n\n", cmds->here_doc);
	if (cmds->here_doc > 0)
	{
		dprintf(2, "coucou, j'existe encore\n");
		close(cmds->here_doc);
		//if (cmds->here_doc)
		//	dprintf(2, "CLOSE FAIL\n");
	}
	execve(cmds->right_path, cmds->args, data->mini_env);
	ft_handle_execve_error(data, cmds);

}

void     ft_handle_first_cmd(t_data *data, t_cmds *cmds)
{
	if (close(cmds->prev_pipe[0]) == -1)
		ft_handle_close_error(data, cmds);
	if (dup2(cmds->curr_pipe[1], 1) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->curr_pipe[1]) == -1)
		ft_handle_close_error(data, cmds);
}

void	ft_handle_last_cmd(t_data *data, t_cmds *cmds)
{
	if (close(cmds->curr_pipe[1]) == -1)
		ft_handle_close_error(data, cmds);
	if (dup2(cmds->prev_pipe[0], 0) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->prev_pipe[0]) == -1)
		ft_handle_close_error(data, cmds);
}

void	ft_handle_processes(t_data *data, t_cmds *cmds, char **env)
{
	(void)env;
	if (cmds && !cmds->prev)
		ft_handle_first_cmd(data, cmds);
	else if (cmds->next == NULL)
		ft_handle_last_cmd(data, cmds);
	else
	{
		if (dup2(cmds->prev_pipe[0], STDIN_FILENO) == -1)
			ft_handle_dup2_error(data, cmds);
		if (dup2(cmds->curr_pipe[1], STDOUT_FILENO) == -1)
			ft_handle_dup2_error(data, cmds);
	}
	ft_waitpid(cmds);
	ft_exec_cmds(data, cmds, NULL);
	//ft_exec_cmds(data, cmds, data->env);
}
