/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:45:50 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 10:04:35 by bcai             ###   ########.fr       */
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

void	builtin_export(t_cmd *cmd, t_m *m)
{
	char	**cmd_args;
	char	*key;
	char	*value;
	char	*equal;
	int		i;

	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	if (cmd_args[1] == NULL)
		builtin_error(cmd, m, "Expected argument to \"export\"");
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
