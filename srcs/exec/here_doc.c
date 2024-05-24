/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <eltouma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:19:04 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/24 07:34:34 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_here_doc(t_cmds *cmds)
{
	t_redir	*tmp;

	tmp = cmds->redir;
	while (tmp != NULL)
	{
		if (tmp->type == 2)
			cmds->here_doc_count += 1;
		tmp = tmp->next;
	}
	return (cmds->here_doc_count);
}

void	ft_is_max_here_doc_nb_reached(t_data *data, t_cmds *cmds)
{
	t_cmds	*tmp;

	tmp = cmds;
	while (cmds != NULL)
	{
		cmds->here_doc_count = ft_count_here_doc(cmds);
		if (cmds->here_doc_count > 16)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("maximun here-doc count exceeded\n", 2);
			ft_exit_properly(data, cmds);
		}
		cmds = cmds->next;
	}
	cmds = tmp;
}

void	ft_restore_stdin(t_data *data, t_cmds *cmds)
{
	if (cmds->cmd && !ft_is_a_built_in(cmds->cmd))
	{
		ft_dup_stdin_stdout(data, cmds);
		ft_putstr_fd("> ", cmds->dev_stdin);
		ft_dup2_and_close_stdin_stdout(data, cmds);
	}
	else
		ft_putstr_fd("> ", cmds->dev_stdin);
}

// implementer les signaux
void	ft_exec_here_doc(t_data *data, t_cmds *cmds, t_redir *redir) //, t_heredoc *heredoc)
{
	char	*line;
	char	*delimiter;
	pid_t   pid;
	int     status;
	int	i = 0;
	//generate 2 fd (read & W) for the heredoc
	cmds->tmp_file = ft_strjoin(".hd_", redir->path);
	cmds->index = ft_itoa(i);
	cmds->name = ft_strjoin(cmds->tmp_file, cmds->index);
	ft_free_ptr(cmds->tmp_file);
	ft_free_ptr(cmds->index);
	i += 1;
	if (cmds->here_doc){
		dprintf(2, "JE SUIS LE PREMIER HERE_DOC\n");
		close (cmds->here_doc);//secure
	}
	cmds->here_doc = open(cmds->name, O_CREAT | O_RDONLY | O_TRUNC, 0755);
//	close (cmds->here_doc);//safe
	cmds->fd_w = open(cmds->name, O_WRONLY | O_TRUNC, 0755);
	//make the file invisible for everybody
	unlink(cmds->name);
	ft_free_ptr(cmds->name);

    // Ajoutez cette ligne pour fermer le descripteur de fichier après la redirection
   // close(cmds->here_doc);

    // Remettez cmds->here_doc à -1 après sa fermeture
   // cmds->here_doc = -1;
	pid = fork();

	if (pid == 0) //child-> ecrit dans le heredoc
	{

		if (cmds->here_doc != -1)
		{
			dprintf(2, "closing write in exec here doc child");
			close (cmds->here_doc);//safe
		}
		//cmds->here_doc = -1;
		delimiter = ft_strjoin(redir->path, "\n");
		while (1)
		{
			//		ft_restore_stdin(data, cmds);
			ft_putstr_fd("> ", 0);
			line = get_next_line(0);
			if (!line)
				break ;
			if (!ft_strcmp(line, delimiter))
				break ;
			ft_putstr_fd(line, cmds->fd_w);
			free(line);

		}
		free(line); 
		free(delimiter);
		if (close(cmds->fd_w) == -1){
			dprintf(2, "closing read in exec here doc child");
			ft_handle_close_error(data, cmds);
		}
		cmds->fd_w = -1;
		//		free(cmds->name);
		ft_clean_all(data); //risque de double free ?
		exit(0);
	}
	//parent:

	int return_status;

	return_status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status))
		return_status = 1;
	if (close(cmds->fd_w) == -1 || return_status)
		ft_handle_close_error(data, cmds);
	cmds->fd_w = -1;
}
