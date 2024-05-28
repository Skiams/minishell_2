/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:14:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/24 23:04:12 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_redir_without_cmd(t_data *data, t_cmds *cmds)
{
	t_redir	*tmp;

	tmp = cmds->redir;
	dprintf(2, "je suis dans handle_redir_without_cmd\n");
	while (cmds->redir != NULL)
	{
		dprintf(2, "je suis dans le while de handle_redir_without_cmd\n");
		if (cmds->redir->type == 1)
		{
			dprintf(2, "je suis dans une redir de type 1\n");
			ft_handle_append(data, cmds);
		}
		if (cmds->redir->type == 3)
		{
			dprintf(2, "je suis dans une redir de type 3");
			if (!cmds->cmd)
			{
				dprintf(2, " et JE N'AI PAS DE commande\n");
				if (access(cmds->redir->path, F_OK) == 0)
				{
					dprintf(2, "Ouais je passe la ouais !\n");
					ft_handle_input_redir(data, cmds);
				}
				else 
				{       
					ft_putstr_fd(cmds->redir->path, 2);
					ft_putstr_fd(": LALALA No such file or directory\n", 2);
				}
			}
		}
		if (cmds->redir->type == 4)
		{
			dprintf(2, "je suis dans une redir de type 4\n");
			ft_handle_output_redir(data, cmds);
		}
		cmds->redir = cmds->redir->next;
	}
	cmds->redir = tmp;
	ft_clear_redirlst(&cmds->redir, &ft_free_ptr);
}

void	ft_handle_redir(t_data *data, t_cmds *cmds)
{
	t_redir	*tmp;
	int	i = 1;

	tmp = cmds->redir;
	dprintf(2, "il y a %d here_doc\n", cmds->here_doc_count);
	dprintf(2, "je suis dans handle_redir\n");

	while (cmds->redir != NULL)
	{
		if (cmds->redir->type == APPEND)
			ft_handle_append(data, cmds);
		if (cmds->redir->type == HEREDOC)
		{
			cmds->here_doc = open("/dev/stdin", O_CREAT | O_RDONLY, 0755);
			dprintf(2, "on est sur le dernier heredoc\n\n");
			if (dup2(cmds->here_doc, 0) == -1)
				ft_handle_dup2_error(data, cmds);
			if (close(cmds->here_doc) == -1)
				ft_handle_close_error(data, cmds);
		}
		if (cmds->redir->type == RED_IN)
		{
			dprintf(2, "je suis dans une redir de type 3\n");
			if (access(cmds->redir->path, F_OK) == 0)
				ft_handle_input_redir(data, cmds);
			else if (ft_is_a_built_in(cmds->cmd))
			{	
				ft_putstr_fd(cmds->redir->path, 2);
				ft_putstr_fd(": LALALA No such file or directory\n", 2);
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
				ft_handle_infile_error(data, cmds);
		}
		if (cmds->redir->type == RED_OUT)
			ft_handle_output_redir(data, cmds);
		cmds->redir = cmds->redir->next;
	}
	cmds->redir = tmp;
	ft_clear_redirlst(&cmds->redir, &ft_free_ptr);
}

void	ft_handle_append(t_data *data, t_cmds *cmds)
{
	// Revoir comment avait fait Ismael pour refacto
	cmds->outfile = open(cmds->redir->path, O_WRONLY | O_CREAT | O_APPEND, 0755);
	if (cmds->outfile == -1)
		ft_handle_outfile_error(data, cmds);
	if (dup2(cmds->outfile, 1) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->outfile) == -1)
		ft_handle_close_error(data, cmds);
}

/*
 * Pourquoi ce else ?
 *
 * Si ton infile n'existe pas, tu vas dans ft_handle_infile_error() et la deux options :
 * 	1 - tu es sur un built-in
 * 	2 - tu n'es pas sur un built-in
 * Mais si ton infile existe, donc s'il n'est pas a -1, donc si tu as pu l'ouvrir
 * Tu veux passer a l'etape d'apres qui est de dup2 ton infile sur 0
 * Soit de faire en sorte que ta commande ne lise plus la data depuis l'entree standard (0)
 * Mais depuis ton infile
 * Une fois qu'on a lu l'info, on n'a plus besoin de cet infile, donc on le close
 */
void	ft_handle_input_redir(t_data *data, t_cmds *cmds)
{
	cmds->infile = open(cmds->redir->path, O_RDONLY, 0755);
	if (cmds->infile == -1)
	{
		dprintf(2, "Je passe LAA\n");
		ft_handle_infile_error(data, cmds);
	}
	else
	{
		if (dup2(cmds->infile, 0) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->infile) == -1)
			ft_handle_close_error(data, cmds);
	}
}

void	ft_handle_output_redir(t_data *data, t_cmds *cmds)
{
	cmds->outfile = open(cmds->redir->path, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (cmds->outfile == -1)
		ft_handle_infile_error(data, cmds);
	else
	{
		if (dup2(cmds->outfile, 1) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->outfile) == -1)
			ft_handle_close_error(data, cmds);
	}
}
