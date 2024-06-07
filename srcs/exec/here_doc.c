/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:19:04 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/06 17:25:29 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_close_hd_in_fork(t_cmds *head_cmds, t_cmds *cmds)
// {
// 	t_redir	*head;
// 	t_cmds	*tmp;

// 	tmp = head_cmds;
// 	while (tmp != NULL && tmp != cmds)
// 	{
// 		head = tmp->redir;
// 		while (head != NULL)
// 		{
// 			if (head->type == HEREDOC)
// 				close(tmp->hd_read);
// 			head = head->next;
// 		}
// 		tmp = tmp->next;
// 	}
// }

// static void	ft_generate_hd_name(t_data *data, t_cmds *cmds, t_redir *redir)
// {
// 	cmds->tmp_file = ft_strjoin_exec(data, ".hd_", redir->path);
// 	cmds->index = ft_itoa(cmds->i);
// 	cmds->name = ft_strjoin_exec(data, cmds->tmp_file, cmds->index);
// 	ft_free_ptr(cmds->tmp_file);
// 	ft_free_ptr(cmds->index);
// 	cmds->i += 1;
// }

// static void	ft_write_in_here_doc(t_data *data, t_cmds *cmds, t_redir *redir)
// {
// 	char	*line;
// 	char	*str;
// 	char	*delimiter;

// 	delimiter = ft_strdup_exec(data, redir->path);
// 	while (1)
// 	{
// 		ft_handle_sig_heredoc();
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (!ft_strcmp(line, delimiter))
// 			break ;
// 		str = ft_strjoin_exec(data, line, "\n");
// 		ft_putstr_fd(str, cmds->hd_write);
// 		free(str);
// 		free(line);
// 	}
// 	free(line);
// 	free(delimiter);
// }

// static void	ft_handle_hd_child(t_data *data, t_cmds *cmds, t_redir *redir,
// 	t_cmds *headcmds)
// {
// 	ft_close_hd_in_fork(headcmds, cmds);
// 	close(cmds->hd_read);
// 	ft_write_in_here_doc(data, cmds, redir);
// 	if (close(cmds->hd_write) == -1)
// 		ft_handle_file_error(data, cmds, redir);
// 	ft_clean_all(data);
// 	exit(0);
// }

// void	ft_exec_here_doc(t_data *data, t_cmds *cmds, t_redir *redir,
// 		t_cmds *headcmds)
// {
// 	pid_t	pid;
// 	int		status;

// 	ft_generate_hd_name(data, cmds, redir);
// 	if (cmds->hd_read)
// 		close (cmds->hd_read);
// 	cmds->hd_read = open(cmds->name, O_CREAT | O_RDONLY | O_TRUNC, 0755);
// 	cmds->hd_write = open(cmds->name, O_CREAT | O_WRONLY | O_TRUNC, 0755);
// 	unlink(cmds->name);
// 	ft_free_ptr(cmds->name);
// 	pid = fork();
// 	if (pid == 0)
// 		ft_handle_hd_child(data, cmds, redir, headcmds);
// 	waitpid(pid, &status, 0);
// 	ft_handle_signal(1);
// 	if (close(cmds->hd_write) == -1)
// 		ft_handle_file_error(data, cmds, redir);
// }

// static void	ft_waitpid_hd(t_data *data)
// {
// 	int	status;
	
// 	while (wait(&status) > 0)
// 	{
// 		if (WIFSIGNALED(status)) 
// 		{
// 			ft_exit_code(WTERMSIG(status) + 128, ADD);
// 			if (WTERMSIG(status) == 2)
// 			{
// 				ft_clean_all(data);
// 				exit (ft_exit_code(0, GET));
// 			}
// 		}
// 	}
// }

static bool    quit_da_cmd(int *pid)
{
    waitpid(*pid, pid, 0);
    if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (ft_exit_code(130, ADD), true);
    return (false);
}

void	ft_close_hd_in_fork(t_cmds *head_cmds, t_cmds *cmds)
{
	t_redir	*head;
	t_cmds	*tmp;

	dprintf(2,"\t->%s\n", __func__);
	tmp = head_cmds;
	while (tmp != NULL && tmp != cmds)
	{
		head = tmp->redir;
		while (head != NULL)
		{
			if (head->type == HEREDOC)
			{
				close(tmp->hd_read);
				if (tmp->hd_write != -1)
					close(tmp->hd_write);
			}
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

static void	ft_write_in_here_doc(t_data *data, t_cmds *cmds, t_redir *redir, t_cmds *headcmds)
{
	char	*line;
	char	*str;
	char	*delimiter;
	(void)headcmds;

	delimiter = ft_strdup_exec(data, redir->path);
	while (1)
	{
		line = readline("> ");
		if (g_sig_exit == 2)
        {
			free(line);
			free(delimiter);
			//ft_close_hd_in_fork(headcmds, NULL);
            ft_clean_all(data);
            exit(2);
        }
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
	ft_handle_sig_heredoc();
	ft_close_hd_in_fork(headcmds, cmds);
	//close(cmds->hd_read);
	ft_write_in_here_doc(data, cmds, redir, headcmds);
	if (close(cmds->hd_write) == -1)
		ft_handle_file_error(data, cmds, redir);
	ft_clean_all(data);
	exit(0);
}

bool	ft_exec_here_doc(t_data *data, t_cmds *cmds, t_redir *redir,
		t_cmds *headcmds)
{
	pid_t	pid;
	//int		status;

	ft_generate_hd_name(data, cmds, redir);
	if (cmds->hd_read)
		close (cmds->hd_read);
	cmds->hd_read = open(cmds->name, O_CREAT | O_RDONLY | O_TRUNC, 0755);
	cmds->hd_write = open(cmds->name, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	unlink(cmds->name);
	ft_free_ptr(cmds->name);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		ft_handle_hd_child(data, cmds, redir, headcmds);
	if (quit_da_cmd(&pid))
		return (dprintf(2, "on return false\n"), (false));
	if (close(cmds->hd_write) == -1)
		ft_handle_file_error(data, cmds, redir);
	g_sig_exit = 0;
	ft_handle_signal(1);
	return (true);
}
