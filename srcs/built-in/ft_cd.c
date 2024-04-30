#include "../../includes/minishell.h"

// static bool	ft_new_oldpwd(t_data *data)
// {
// 	char	*old_pwd;
// 	char	cwd[PATH_MAX];

// 	if (getcwd(cwd, PATH_MAX) == NULL)
// 		return (ft_exit_code(1, ADD), false);
// 	old_pwd = ft_strdup(cwd);
// 	if (!old_pwd)
// 		return (ft_exit_code(12, ADD), false);
// 	if (ft_var_is_in_env(data, "OLDPWD"))
// 	{
// 		if (!ft_add_value_only(data, "OLDPWD", old_pwd, 2))
// 			return (false);
// 	}
// 	return (true);
// }

// static int	ft_change_dir(t_data *data, t_env *env, int code)
// {
// 	char	*new_dir;

// 	new_dir = NULL;
// 	if (code == 1)
// 	{
// 		ft_new_oldpwd(data);
// 		new_dir = ft_var_is_exp(data, "HOME");
// 		if (!new_dir)
// 			return ()
// 	}
// }
// int	ft_cd(t_cmds *cmds, t_data *data)
// {
// 	char    *working_dir;
// 	int		exit_code;
// //	char    *last_dir;
// //	char    *new_dir;

// 	if (!cmds->args[1])
// 		exit_code = ft_change_dir(data, data->env, 1);
// 	else if (cmds->args[1])
// 	{
// //		if (!ft_strcmp(cmds->args[1], "~"))
// 		chdir(cmds->args[1]);
// 	}
// 	return (ft_exit_code(0, GET));	
// }

