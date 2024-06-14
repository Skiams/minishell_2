/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:14:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/13 20:35:17 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_read_here_doc(t_data *data, t_cmds *cmds, int *count)
{
	*count += 1;
	if (*count == cmds->here_doc_count)
	{
		if (dup2(cmds->hd_read, 0) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->hd_read) == -1)
			ft_handle_close_error(data, cmds);
	}
}

void	ft_handle_output_and_append(t_data *data, t_cmds *cmds, t_redir *redir)
{
	int	flag;

	if (redir->type == APPEND)
		flag = O_APPEND;
	else
		flag = O_TRUNC;
	cmds->outfile = open(redir->path, O_WRONLY | O_CREAT | flag, 0755);
	if (cmds->outfile == -1)
		ft_handle_file_error(data, cmds, redir);
	else
	{
		if (dup2(cmds->outfile, 1) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->outfile) == -1)
			ft_handle_close_error(data, cmds);
	}
}

/*
 * Pourquoi ce else ?
 *
 * Si ton infile n'existe pas, tu vas dans ft_handle_file_error()
 * et la deux options :
 * 	1 - tu es sur un built-in
 * 	2 - tu n'es pas sur un built-in
 * Mais si ton infile existe, donc s'il n'est pas a -1,
 * donc si tu as pu l'ouvrir
 * Tu veux passer a l'etape d'apres qui est de dup2 ton infile sur 0
 * Soit de faire en sorte que ta commande ne lise plus la data
 * depuis l'entree standard (0)
 * Mais depuis ton infile
 * Une fois qu'on a lu l'info, on n'a plus besoin de cet infile, donc on le close
 */
void	ft_open_input(t_data *data, t_cmds *cmds, t_redir *tmp)
{
	cmds->infile = open(tmp->path, O_RDONLY, 0755);
	if (cmds->infile == -1)
		ft_handle_file_error(data, cmds, tmp);
	else
	{
		if (dup2(cmds->infile, 0) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->infile) == -1)
			ft_handle_close_error(data, cmds);
	}
}

void	ft_handle_input_no_built_in(t_data *data, t_cmds *cmds, t_redir *tmp)
{
	if (access(tmp->path, F_OK) == 0)
		ft_open_input(data, cmds, tmp);
	else
		ft_handle_file_error(data, cmds, tmp);
}

int	ft_handle_input(t_data *data, t_cmds *cmds, t_redir *tmp)
{
	if (ft_is_a_built_in(cmds->cmd))
	{
		if (access(tmp->path, F_OK) == -1
			|| access(tmp->path, R_OK) == -1 || access(tmp->path, W_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(tmp->path);
			ft_exit_code(1, ADD);
			return (0);
		}
	}
	else
		ft_handle_input_no_built_in(data, cmds, tmp);
	return (1);
}