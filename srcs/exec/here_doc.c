/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:19:04 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/15 13:08:44 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_here_doc(t_data *data, t_cmds *cmds)
{
	char	*line;
	char	*delimiter;

	if (!cmds->cmd)
		cmds->here_doc = open("/dev/stdin", O_CREAT | O_TRUNC, 0755);
	else
		cmds->here_doc = open(cmds->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (cmds->here_doc == -1)
		ft_handle_infile_error(data, cmds);
	cmds->is_here_doc = 1;
	delimiter = ft_strjoin(cmds->redir->path, "\n");
	while (1)
	{
		ft_putstr_fd("> ", 0);
		line = get_next_line(0);
		if (!ft_strcmp(line, delimiter))
			break ;
		ft_putstr_fd(line, cmds->here_doc);
		free(line);
	}
	free(line);
	free(delimiter);
	if (close(cmds->here_doc) == -1)
		ft_handle_infile_error(data, cmds);
}

void    ft_handle_here_doc(t_data *data, t_cmds *cmds)
{
/*
	if (cmds->is_here_doc == 1)
	{
		cmds->here_doc = open(cmds->cmd, O_RDONLY, 0755);
		if (cmds->here_doc == -1)
			ft_handle_infile_error(data, cmds);
		if (dup2(cmds->here_doc, 0) == -1)
			ft_handle_dup2_error(data, cmds);
		if (close(cmds->here_doc) == -1)
			ft_handle_close_error(data, cmds);
		cmds->i += 1;
	}
	else
	{
*/
		if (pipe(cmds->prev_pipe) == -1)
			ft_handle_pipe_error(data, cmds);
		while (cmds->is_here_doc > 1 && cmds->is_here_doc <= 16)
		{
			if (pipe(cmds->curr_pipe) == -1)
				ft_handle_pipe_error(data, cmds);
			if (cmds->is_here_doc == 1)
			{
				cmds->here_doc = open(cmds->cmd, O_RDONLY, 0755);
				if (cmds->here_doc == -1)
					ft_handle_infile_error(data, cmds);
				if (close(cmds->prev_pipe[0]) == -1)
					ft_handle_close_error(data, cmds);
				if (dup2(cmds->curr_pipe[1], 1) == -1)
					ft_handle_dup2_error(data, cmds);
				if (close(cmds->curr_pipe[1]) == -1)
					ft_handle_close_error(data, cmds);
			}
			else if (cmds->is_here_doc == 16)
			{
				if (close(cmds->curr_pipe[1]) == -1)
					ft_handle_close_error(data, cmds);
				if (dup2(cmds->prev_pipe[0], 0) == -1)
					ft_handle_dup2_error(data, cmds);
				if (close(cmds->prev_pipe[0]) == -1)
					ft_handle_close_error(data, cmds);
				if (close(cmds->here_doc) == -1)
					ft_handle_close_error(data, cmds);
			}
			else
			{
				if (dup2(cmds->prev_pipe[0], 0) == -1)
					ft_handle_dup2_error(data, cmds);
				if (dup2(cmds->curr_pipe[1], 1) == -1)
					ft_handle_dup2_error(data, cmds);
			}
			cmds->is_here_doc += 1;
		}
//	}
	if (unlink(cmds->cmd) == -1)
	{
		free(cmds->cmd);
		ft_free_tab(cmds->cmd_path);
		ft_clean_all(data);
	}
}
