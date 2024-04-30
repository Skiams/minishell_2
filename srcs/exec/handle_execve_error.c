#include "../../includes/minishell.h"

void	ft_handle_execve_error(t_data *data, t_cmds *cmds)
{
	ft_putstr_fd("Attention tout le monde ! Je fail ! Avec une ou plusieurs commandes\n", 2); 
	ft_putstr_fd("minishell: ", 2); 
	perror(cmds->right_path);
	free(cmds->right_path);
	while (cmds && cmds != NULL)
	{
		ft_free_tab(cmds->cmd_path);
		cmds = cmds->next;
	}
	ft_clean_all(data);
	ft_exit_code(1, ADD);
	exit (1);
}
