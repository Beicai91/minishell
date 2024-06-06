/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:08 by bcai              #+#    #+#             */
/*   Updated: 2024/05/30 09:51:52 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_envvar_util(char *key, char *value, t_m *m)
{
	t_envvar	*temp;

	temp = get_envvar(key);
	if (temp && temp->is_exported == 1)
		update_envvars(key, value, 1);
	else if (temp && temp->is_exported == 0 && m->export_hidden == 1)
		update_envvars(key, value, 1);
	else if (temp && temp->is_exported == 0 && m->export_hidden == 0)
		update_envvars(key, value, 0);
	else
		update_envvars(key, value, 0);
}

void	no_value_after_equal2(int *i, char **cmd_args, char *equal, t_m *m)
{
	char	*key;
	char	*value;

	key = ft_substr(cmd_args[*i], 0, equal - cmd_args[*i]);
	if (cmd_args[*i + 1] && !ft_strchr(cmd_args[*i + 1], '='))
	{
		value = ft_strdup(cmd_args[*i + 1]);
		*i = *i + 1;
	}
	else
		value = ft_strdup("");
	m->export_hidden = 0;
	update_envvar_util(key, value, m);
}

void	print_and_update_status(char *arg, t_m *m)
{
	printf("minishell: %s: command not found\n", arg);
	m->exit_status = 127;
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
		if (ft_isdigit(cmd_args[i][0]) || ft_strchr("~@%*^", cmd_args[i][0]))
			print_and_update_status(cmd_args[i++], m);
		equal = ft_strchr(cmd_args[i], '=');
		if (!*(equal + 1))
			no_value_after_equal2(&i, cmd_args, equal, m);
		else
		{
			key = ft_substr(cmd_args[i], 0, equal - cmd_args[i]);
			value = get_value(cmd_args[i], equal + 1, cmd, m);
			update_envvar_util(key, value, m);
		}
		i++;
	}
}
