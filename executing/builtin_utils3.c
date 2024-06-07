/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:42:06 by bcai              #+#    #+#             */
/*   Updated: 2024/06/06 09:45:24 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_value_case(char *arg, t_m *m)
{
	char		*key;
	char		*value;
	t_envvar	*target;

	key = ft_strdup(arg);
	target = get_envvar(key);
	if (!target)
	{
		m->export_hidden = 1;
		value = ft_strdup("");
		update_envvars(key, value, 0);
	}
	else
	{
		value = ft_strdup(target->value);
		update_envvars(key, value, 1);
	}
}

int	no_value_after_equal1(int *i, char **cmd_args, \
	char *equal, t_qflag **qflags)
{
	char	*key;
	char	*value;

	key = ft_substr(cmd_args[*i], 0, equal - cmd_args[*i]);
	if (cmd_args[*i + 1] && !ft_strchr(cmd_args[*i + 1], '=') \
		&& (*qflags)->next->quote_flag != 0)
	{
		value = ft_strdup(cmd_args[*i + 1]);
		*i = *i + 1;
		*qflags = (*qflags)->next;
	}
	else
		value = ft_strdup("");
	return (update_envvars(key, value, 1));
}

int	value_after_equal(int i, t_cmd *cmd, t_m *m, char *equal)
{
	char	*key;
	char	*value;
	char	**cmd_args;

	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	key = ft_substr(cmd_args[i], 0, equal - cmd_args[i]);
	value = get_value(cmd_args[i], equal + 1, cmd, m);
	return (update_envvars(key, value, 1));
}
