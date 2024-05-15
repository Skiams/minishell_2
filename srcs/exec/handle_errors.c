/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:15:12 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/15 18:12:21 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit_properly(t_data *data, t_cmds *cmds)
{
//	print_cmds(cmds);
	ft_free_tab(cmds->cmd_path);
	ft_clean_all(data);
	ft_exit_code(1, ADD);
	dprintf(2, "\n\n");
//	print_cmds(cmds);
// Attention le code de sortie est le bon pour le max de here_doc atteint, mais a voir s'il faut le changer pour d' autres erreurs
	exit (2);
}

/*
 * Pourquoi on a besoin de fork si on est sur un built-in ?
 *
 * Parce que tu as besoin que ton process ne quitte pas ton programme
 * s'il n'a pas reussi a ouvrir l'infile (donc si l'infile == -1)
 * Il te faut donc un enfant qui va close 0 et 1 qui on ete ouvert
 * 	-> cf ft_is_only_one_cmd(), si on a un built-in 
 * Puis qui va quitter prorement sans executer le built-in
 * ni quitter le programme
 * C'est pour ca que dans is_only_one_cmd()
 * le built-in ne s'execute que si on a un infile
 * Donc si l'infile != -1
 */
void	ft_handle_infile_error(t_data *data, t_cmds *cmds)
{
	perror(cmds->redir->path);
	if (ft_is_a_built_in(cmds->cmd) || !cmds->cmd)
	{
		cmds->pid = fork();
		if (cmds->pid == -1)
			ft_handle_fork_error(data, cmds);
		if (cmds->pid == 0)
		{
			if (cmds->list_size == 1)
				ft_dup2_and_close_stdin_stdout(data, cmds);
			ft_exit_properly(data, cmds);
		}
		ft_waitpid_only_one_cmd(cmds);
	}
	else
	{
		if (cmds->list_size == 1)
		{
			dprintf(2, "COUCOU, NOUS SOMMES LA\n");
			ft_waitpid_only_one_cmd(cmds);
		}
		else
			ft_waitpid(cmds);
		ft_exit_properly(data, cmds);
	}
}

void	ft_handle_outfile_error(t_data *data, t_cmds *cmds)
{
	perror(cmds->redir->path);
	if (cmds->outfile != -1)
		close(cmds->outfile);
	if (cmds->list_size == 1)
		ft_waitpid_only_one_cmd(cmds);
	else
		ft_waitpid(cmds);
	ft_exit_properly(data, cmds);
}

void	ft_handle_pipe_error(t_data *data, t_cmds *cmds)
{
	ft_putstr_fd("pipe failed\n", 2);
	ft_close_processes(cmds);
	ft_exit_properly(data, cmds);
}

void	ft_handle_fork_error(t_data *data, t_cmds *cmds)
{
	ft_putstr_fd("fork failed\n", 2);
	ft_close_processes(cmds);
	waitpid(cmds->pid, NULL, 0);
	ft_exit_properly(data, cmds);
}

void	ft_handle_close_error(t_data *data, t_cmds *cmds)
{
	ft_putstr_fd("close failed\n", 2);
	ft_free_tab(cmds->cmd_path);
	close(cmds->outfile);
	ft_close_processes(cmds);
	ft_exit_properly(data, cmds);
/*
	ft_free_tab(cmds->cmd_path);
	ft_clean_all(data);
	ft_close_processes(cmds);
	ft_exit_code(1, ADD);
	exit (1);
*/
}
