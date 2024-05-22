/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:45:50 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 12:23:53 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_value_case(char *arg)
{
	char		*key;
	char		*value;
	t_envvar	*target;

	key = ft_strdup(arg);
	target = get_envvar(key);
	if (!target)
	{
		value = ft_strdup("");
		update_envvars(key, value, 0);
	}
	else
	{
		value = ft_strdup(target->value);
		update_envvars(key, value, 1);
	}
}

void	export_all(t_m *m)
{
	t_list	*envcpy;
	t_gl	*gl;
	t_envvar	*envvars;
	char	*temp;

	gl = get_gl();
	envvars = gl->env_vars;
	envcpy = NULL;
	while (envvars != NULL)
	{
		temp = ft_strjoin(envvars->key, "=\"");
		temp = join_free(temp, envvars->value);
		temp = join_free(temp, "\"");
		build_files_list(&envcpy, temp);
		envvars = envvars->next;
	}
	sort_array(&envcpy, m);
	while (envcpy != NULL)
	{
		printf("declare -x %s\n", envcpy->content);
		free(envcpy->content);
		envcpy = envcpy->next;
	}
	free_t_list(&envcpy);
}

void	builtin_export(t_cmd *cmd, t_m *m)
{
	char	**cmd_args;
	char	*key;
	char	*value;
	char	*equal;
	int		i;

	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	if (cmd_args[1] == NULL)
		export_all(m);
		//builtin_error(cmd, m, "Expected argument to \"export\"");
	i = 0;
	while (cmd_args[++i] != NULL)
	{
		equal = ft_strchr(cmd_args[i], '=');
		if (!equal)
			no_value_case(cmd_args[i]);
		else
		{
			key = ft_substr(cmd_args[i], 0, equal - cmd_args[i]);
			value = get_value(cmd_args[i], equal + 1, cmd, m);
			update_envvars(key, value, 1);
		}
	}
}

void	set_envvar(t_cmd *cmd, t_m *m)
{
	char	**cmd_args;
	int		i;
	char	*value;
	char	*key;
	char	*equal;

	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	i = 0;
	while (cmd_args[i] != NULL)
	{
		equal = ft_strchr(cmd_args[i], '=');
		key = ft_substr(cmd_args[i], 0, equal - cmd_args[i]);
		value = get_value(cmd_args[i], equal + 1, cmd, m);
		if (get_envvar(key))
			update_envvars(key, value, 1);
		else
			update_envvars(key, value, 0);
		i++;
	}
}

void	builtin_unset(t_cmd *cmd, t_m *m)
{
	char	**cmd_args;
	int		i;

	(void)m;
	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	i = 1;
	while (cmd_args[i] != NULL)
	{
		remove_envvar(cmd_args[i]);
		i++;
	}
}
