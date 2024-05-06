#include "../../includes/minishell.h"

static bool	ft_add_value_cd(t_data *data, char *var, char *value)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(var, tmp->var) == 0)
		{
			ft_free_ptr(tmp->value);
			tmp->value = ft_strdup(value);
			if (!tmp->value)
				return (ft_exit_code(12, ADD), false);
			ft_free_ptr(value);
			if (tmp->next)
				tmp = tmp->next;
			return (true);
		}
		tmp = tmp->next;
	}
	return (true);
}

static void    ft_print_cd_error(char **args)
{
    ft_putstr_fd("minishell: cd: ", 2);
    if (args[2])
        ft_putstr_fd("string not in pwd: ", 2);
    else
    {
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putstr_fd(args[1], 2);
    ft_putstr_fd("\n", 2);
}

static bool	ft_new_pwds(t_data *data, int code)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ft_exit_code(1, ADD), false);
	pwd = ft_strdup(cwd);
	if (!pwd)
		return (ft_exit_code(12, ADD), false);
	if (ft_var_is_in_env(data, "OLDPWD") && code == OLDPWD)
	{
		if (!ft_add_value_cd(data, "OLDPWD", pwd))
			return (false);
	}
    else if (ft_var_is_in_env(data, "PWD") && code == PWD)
    {
		if (!ft_add_value_cd(data, "PWD", pwd))
			return (false);
	}
	return (true);
}

static int	ft_change_dir(t_data *data, int code)
{
	char	*new_dir;
    int     exit_code;

    exit_code = 0;
	new_dir = NULL;
	if (code == HOME)
	{
		if (!ft_new_pwds(data, OLDPWD))
            return(ft_exit_code(0, GET));
        if (!ft_var_is_in_env(data, "HOME"))
            return (ft_putstr_fd("minishell: cd: HOME is not set\n", 2), 1);
		new_dir = ft_var_is_exp(data, "HOME");
		if (!new_dir)
			return (ft_exit_code(12, ADD));
	}
    else if (code == PREV)
    {
        if (!ft_var_is_in_env(data, "OLDPWD"))
            return (ft_putstr_fd("minishell: cd: OLDPWD is not set\n", 2), 1);
        new_dir = ft_var_is_exp(data, "OLDPWD");
        if (!new_dir)
            return (ft_exit_code(12, ADD));
		ft_putstr_fd(new_dir, 1);
		ft_putstr_fd("\n", 1);
		if (!ft_new_pwds(data, OLDPWD))
            return(ft_exit_code(0, GET));
    }
    exit_code = chdir(new_dir);
    if (exit_code == 0 && !ft_new_pwds(data, PWD))
        return (ft_free_ptr(new_dir), ft_exit_code(0, GET));
    return(ft_free_ptr(new_dir), ft_exit_code(exit_code, ADD));
}

int	ft_cd(t_cmds *cmds, t_data *data)
{
	int		exit_code;

    exit_code = 0;
	if (!cmds->args[1] || ft_strcmp(cmds->args[1], "~") == 0)
		exit_code = ft_change_dir(data, HOME);
	else if (ft_strcmp(cmds->args[1], "-") == 0)
		exit_code = ft_change_dir(data, PREV);
    else if (ft_args_nb(cmds) > 2)
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        exit_code = 1;
    }
    else
    {
		if (!ft_new_pwds(data, OLDPWD))
            return(ft_exit_code(0, GET));
        exit_code = chdir(cmds->args[1]);
        if (exit_code < 0)
            exit_code *= -1;
        if (exit_code != 0)
            ft_print_cd_error(cmds->args);
        else if (!ft_new_pwds(data, PWD))
            return(ft_exit_code(0, GET));
    }
	return (ft_exit_code(exit_code, ADD));
}
