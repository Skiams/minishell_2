/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:14:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/26 14:42:47 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_handle_redir_without_cmd(t_data *data, t_cmds *cmds)
{
	// Probleme, le texte s'affiche 2 fois pour les here_doc sans commande
	if (cmds->redir && cmds->redir->type == 2)
	{
		ft_exec_here_doc(data, cmds);
		unlink(cmds->redir->path);
	}
	else if (cmds->redir->type == 3)
	{
		if (access(cmds->redir->path, F_OK) == 0);
		else 
		{       
			ft_putstr_fd(cmds->redir->path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
	}
	else
	{
		cmds->outfile = open(cmds->redir->path, O_WRONLY | O_CREAT, 0755);
		if (cmds->outfile == -1)
			ft_handle_outfile_error(cmds, data);
		if (close(cmds->outfile) == -1)
			ft_handle_close_error(cmds);
	}
	return (ft_exit_code(0, GET));
}

void	ft_handle_redir(t_data *data, t_cmds *cmds)
{
	if (cmds->redir->type == 1)
		ft_handle_append(data, cmds);
	if (cmds->redir->type == 2)
	{
		ft_exec_here_doc(data, cmds);
		ft_handle_here_doc(data, cmds);
	}
	if (cmds->redir->type == 3)
		ft_handle_input_redir(data, cmds);
	if (cmds->redir->type == 4)
		ft_handle_output_redir(data, cmds);
}

void	ft_handle_append(t_data *data, t_cmds *cmds)
{
	// Revoir comment avait fait Ismael pour refacto
	cmds->outfile = open(cmds->redir->path, O_WRONLY | O_CREAT | O_APPEND, 0755);
	if (cmds->outfile == -1)
		ft_handle_outfile_error(cmds, data);
	if (dup2(cmds->outfile, 1) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->outfile) == -1)
		ft_handle_close_error(cmds);
}

void	ft_handle_input_redir(t_data *data, t_cmds *cmds)
{
	cmds->infile = open(cmds->redir->path, O_RDONLY, 0755);
	if (cmds->infile == -1)
		ft_handle_infile_error(cmds, data);
	if (dup2(cmds->infile, 0) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->infile) == -1)
		ft_handle_close_error(cmds);
}

void	ft_handle_output_redir(t_data *data, t_cmds *cmds)
{
	cmds->outfile = open(cmds->redir->path, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (cmds->outfile == -1)
		ft_handle_outfile_error(cmds, data);
	if (dup2(cmds->outfile, 1) == -1)
		ft_handle_dup2_error(data, cmds);
	if (close(cmds->outfile) == -1)
		ft_handle_close_error(cmds);
}
