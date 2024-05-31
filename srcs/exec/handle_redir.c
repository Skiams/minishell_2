/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:14:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/31 18:45:08 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_read_here_doc(t_data *data, t_cmds *cmds, int *count)
{
	*count += 1;
	if (*count == cmds->here_doc_count)
	{
		if (dup2(cmds->here_doc, 0) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->here_doc) == -1)
			ft_handle_close_error(data, cmds);
	}
	fprintf(stderr, "{{{{%i}}}}[%i]\n", cmds->here_doc, cmds->here_doc_count);
}

void	ft_handle_redir(t_data *data, t_cmds *cmds)
{
	t_redir	*tmp;
	int		count;

	tmp = cmds->redir;
	count = 0;
	dprintf(2, " -> %s\n", __func__);
	while (tmp != NULL)
	{
		if (tmp->type == APPEND)
			ft_handle_output_and_append_redir(data, cmds);
		if (tmp->type == HEREDOC)
			ft_read_here_doc(data, cmds, &count);
		if (tmp->type == RED_IN)
			ft_handle_input_redir(data, cmds);
		if (tmp->type == RED_OUT)
			ft_handle_output_and_append_redir(data, cmds);
		tmp = tmp->next;
	}
	ft_clear_redirlst(&cmds->redir, &ft_free_ptr);
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
void	ft_open_input_redir(t_data *data, t_cmds *cmds)
{
	cmds->infile = open(cmds->redir->path, O_RDONLY, 0755);
	if (cmds->infile == -1)
		ft_handle_file_error(data, cmds);
	else
	{
		if (dup2(cmds->infile, 0) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->infile) == -1)
			ft_handle_close_error(data, cmds);
	}
}

void	ft_handle_input_redir(t_data *data, t_cmds *cmds)
{
	int	i;

	i = 0;
	if (access(cmds->redir->path, F_OK) == 0)
		ft_open_input_redir(data, cmds);
	else if (ft_is_a_built_in(cmds->cmd))
	{	
		ft_putstr_fd(cmds->redir->path, 2);
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
		ft_handle_file_error(data, cmds);
}

void	ft_handle_output_and_append_redir(t_data *data, t_cmds *cmds)
{
	int	flag;

	if (cmds->redir->type == APPEND)
		flag = O_APPEND;
	else
		flag = O_TRUNC;
	cmds->outfile = open(cmds->redir->path, O_WRONLY | O_CREAT | flag, 0755);
	if (cmds->outfile == -1)
		ft_handle_file_error(data, cmds);
	else
	{
		if (dup2(cmds->outfile, 1) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->outfile) == -1)
			ft_handle_close_error(data, cmds);
	}
}
