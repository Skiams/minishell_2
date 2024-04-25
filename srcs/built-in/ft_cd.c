#include "../../includes/minishell.h"

void	ft_cd(t_cmds *cmds, t_data *data)
{
	(void)data;
	char    *working_dir;
//	char    *last_dir;
//	char    *new_dir;

	if (!cmds->args[1])
	{
        	working_dir = getcwd(NULL, 0);
		free(working_dir);
		working_dir = NULL;
	}
	else if (cmds->args[1])
	{
//		if (!ft_strcmp(cmds->args[1], "~"))
		chdir(cmds->args[1]);
	}		
}

