/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:19:04 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/05 19:39:49 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close_hd_in_fork(t_cmds *head_cmds, t_cmds *cmds)
{
	t_redir	*head;
	t_cmds	*tmp;

	tmp = head_cmds;
	while (tmp != NULL && tmp != cmds)
	{
		head = tmp->redir;
		while (head != NULL)
		{
			if (head->type == HEREDOC)
				close(tmp->hd_read);
			head = head->next;
		}
		tmp = tmp->next;
	}
}

static void	ft_generate_hd_name(t_data *data, t_cmds *cmds, t_redir *redir)
{
	cmds->tmp_file = ft_strjoin_exec(data, ".hd_", redir->path);
	cmds->index = ft_itoa(cmds->i);
	cmds->name = ft_strjoin_exec(data, cmds->tmp_file, cmds->index);
	ft_free_ptr(cmds->tmp_file);
	ft_free_ptr(cmds->index);
	cmds->i += 1;
}

static void	ft_write_in_here_doc(t_data *data, t_cmds *cmds, t_redir *redir)
{
	char	*line;
	char	*str;
	char	*delimiter;

	delimiter = ft_strdup_exec(data, redir->path);
	while (1)
	{
		ft_handle_sig_heredoc();
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, delimiter))
			break ;
		str = ft_strjoin_exec(data, line, "\n");
		ft_putstr_fd(str, cmds->hd_write);
		free(str);
		free(line);
	}
	free(line);
	free(delimiter);
}

static void	ft_handle_hd_child(t_data *data, t_cmds *cmds, t_redir *redir,
	t_cmds *headcmds)
{
	ft_close_hd_in_fork(headcmds, cmds);
	close(cmds->hd_read);
	ft_write_in_here_doc(data, cmds, redir);
	if (close(cmds->hd_write) == -1)
		ft_handle_file_error(data, cmds, redir);
	ft_clean_all(data);
	exit(0);
}

void	ft_exec_here_doc(t_data *data, t_cmds *cmds, t_redir *redir,
		t_cmds *headcmds)
{
	pid_t	pid;
	int		status;

	ft_generate_hd_name(data, cmds, redir);
	if (cmds->hd_read)
		close (cmds->hd_read);
	cmds->hd_read = open(cmds->name, O_CREAT | O_RDONLY | O_TRUNC, 0755);
	cmds->hd_write = open(cmds->name, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	unlink(cmds->name);
	ft_free_ptr(cmds->name);
	pid = fork();
	if (pid == 0)
		ft_handle_hd_child(data, cmds, redir, headcmds);
	waitpid(pid, &status, 0);
	ft_handle_signal(1);
	if (close(cmds->hd_write) == -1)
		ft_handle_file_error(data, cmds, redir);
}
