/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:19:04 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/31 18:43:52 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// cat << a << b << c | cat << a << b << c
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
			{
				fprintf(stderr, "trying to close %i\n", tmp->here_doc);
				close(tmp->here_doc);
			}
			head = head->next;
		}
		tmp = tmp->next;
	}
}

static void	ft_generate_hd_name(t_cmds *cmds, t_redir *redir)
{
	cmds->tmp_file = ft_strjoin(".hd_", redir->path);
	cmds->index = ft_itoa(cmds->i);
	cmds->name = ft_strjoin(cmds->tmp_file, cmds->index);
	ft_free_ptr(cmds->tmp_file);
	ft_free_ptr(cmds->index);
	cmds->i += 1;
}

static void	ft_write_in_here_doc(t_cmds *cmds, t_redir *redir)
{
	char	*line;
	char	*str;
	char	*delimiter;

	delimiter = ft_strdup(redir->path);
	while (1)
	{
		ft_handle_sig_heredoc();
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, delimiter))
			break ;
		str = ft_strjoin(line, "\n");
		ft_putstr_fd(str, cmds->fd_w);
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
	close(cmds->here_doc);
	ft_write_in_here_doc(cmds, redir);
	if (close(cmds->fd_w) == -1)
		ft_handle_file_error(data, cmds);
	ft_clean_all(data);
	exit(0);
}

void	ft_exec_here_doc(t_data *data, t_cmds *cmds, t_redir *redir,
		t_cmds *headcmds)
{
	pid_t	pid;
	int		status;

	ft_generate_hd_name(cmds, redir);
	fprintf(stderr, "before %i\n", cmds->here_doc);
	if (cmds->here_doc)
		close (cmds->here_doc);
	cmds->here_doc = open(cmds->name, O_CREAT | O_RDONLY | O_TRUNC, 0755);
	fprintf(stderr, "heredoc nb %i\n", cmds->here_doc);
	cmds->fd_w = open(cmds->name, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	unlink(cmds->name);
	ft_free_ptr(cmds->name);
	pid = fork();
	if (pid == 0)
		ft_handle_hd_child(data, cmds, redir, headcmds);
	waitpid(pid, &status, 0);
	if (close(cmds->fd_w) == -1)
		ft_handle_file_error(data, cmds);
	ft_handle_signal(1);
}
