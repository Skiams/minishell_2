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

/*
void	ft_exec_here_doc(t_pipex *pipex, char **argv)
{
	char	*line;
	char	*delimiter;

	if (!ft_strcmp(argv[1], "here_doc"))
	{
		pipex->here_doc = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0755);
		if (pipex->here_doc == -1)
			ft_handle_file_error(&argv[1], pipex);
		pipex->is_here_doc = 1;
		delimiter = ft_strjoin(argv[2], "\n");
		while (1)
		{
			ft_putstr_fd("> ", 0);
			line = get_next_line(0);
			if (!ft_strcmp(line, delimiter))
				break ;
			ft_putstr_fd(line, pipex->here_doc);
			free(line);
		}
		free(line);
		free(delimiter);
		if (close(pipex->here_doc) == -1)
			ft_handle_file_error(&argv[1], pipex);
	}
}
*/
