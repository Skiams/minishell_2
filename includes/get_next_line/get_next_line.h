/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:25:35 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/20 22:52:25 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
int		ft_strchr_gnl(t_list *node);
void	ft_lstadd_back(t_list **list, char *buff);
t_list	*ft_lstlast(t_list *node);
void	ft_lstcreate(t_list **list, int fd);
char	*get_line(t_list *node);
int		ft_lstsize(t_list *node);
void	ft_strcpy(t_list *node, char *line);
void	ft_lstclean(t_list **list);
void	ft_dealloc(t_list **list, t_list *node, char *rest);
#endif
