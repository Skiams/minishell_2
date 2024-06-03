/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:14:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/03 15:08:14 by eltouma          ###   ########.fr       */
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

	if (cmds->redir->type == APPEND)
		flag = O_APPEND;
	else
		flag = O_TRUNC;
	cmds->outfile = open(cmds->redir->path, O_WRONLY | O_CREAT | flag, 0755);
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

void	ft_handle_input(t_data *data, t_cmds *cmds, t_redir *tmp)
{
	int	i;

	i = 0;
	if (access(tmp->path, F_OK) == 0)
		ft_open_input(data, cmds, tmp);
	else if (ft_is_a_built_in(cmds->cmd))
	{	
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp->path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		if (cmds->args[i])
		{
			while (cmds->args[i])
			{
				free(cmds->args[i]);
				cmds->args[i] = NULL;
				i += 1;
			}
		}
	}
	else
		ft_handle_file_error(data, cmds, tmp);
}

void	ft_handle_redir(t_data *data, t_cmds *cmds)
{
	t_redir	*tmp;
	int		count;

	tmp = cmds->redir;
	count = 0;
	while (tmp != NULL)
	{
		if (tmp->type == APPEND)
			ft_handle_output_and_append(data, cmds, tmp);
		if (tmp->type == HEREDOC)
			ft_read_here_doc(data, cmds, &count);
		if (tmp->type == RED_IN)
			ft_handle_input(data, cmds, tmp);
		if (tmp->type == RED_OUT)
			ft_handle_output_and_append(data, cmds, tmp);
		tmp = tmp->next;
	}
	ft_close_hd_in_fork(data->cmd_list, NULL);
	ft_clear_redirlst(&cmds->redir, &ft_free_ptr);
}
