/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:45:50 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 12:55:14 by eprzybyl         ###   ########.fr       */
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

void	export_all(t_m *m)
{
	t_list		*envcpy;
	t_gl		*gl;
	t_envvar	*envvars;

	gl = get_gl();
	envvars = gl->env_vars;
	envcpy = NULL;
	build_envvar_list(envvars, &envcpy);
	sort_array(&envcpy, m);
	while (envcpy != NULL)
	{
		printf("declare -x %s\n", (char *)envcpy->content);
		m->temp = envcpy;
		free(envcpy->content);
		envcpy = envcpy->next;
		free(m->temp);
	}
}

void	build_envvar_list(t_envvar *envvars, t_list **envcpy)
{
	char	*temp;

	while (envvars != NULL)
	{
		temp = ft_strjoin(envvars->key, "=\"");
		temp = join_free(temp, envvars->value);
		temp = join_free(temp, "\"");
		build_files_list(envcpy, temp);
		free(temp);
		temp = NULL;
		envvars = envvars->next;
	}
}

void	no_value_after_equal1(int *i, char **cmd_args, char *equal, t_qflag **qflags)
{
	char	*key;
	char	*value;

	key = ft_substr(cmd_args[*i], 0, equal - cmd_args[*i]);
	if (cmd_args[*i + 1] && !ft_strchr(cmd_args[*i + 1], '=') && (*qflags)->next->quote_flag != 0)
	{
		value = ft_strdup(cmd_args[*i + 1]);
		*i = *i + 1;
		*qflags = (*qflags)->next;
	}
	else
		value = ft_strdup("");
	update_envvars(key, value, 1);
}

void	value_after_equal(int i, t_cmd *cmd, t_m *m, char *equal)
{
	char	*key;
	char	*value;
	char	**cmd_args;

	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	key = ft_substr(cmd_args[i], 0, equal - cmd_args[i]);
	value = get_value(cmd_args[i], equal + 1, cmd, m);
	update_envvars(key, value, 1);
}

void	builtin_export(t_cmd *cmd, t_m *m)
{
	char	**cmd_args;
	char	*equal;
	int		i;
	t_qflag	*qflags;

	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	qflags = ((t_execcmd *)cmd)->qflags->next;
	//test
	//printf("qflag starts from %d\n", qflags->quote_flag);
	//
	if (cmd_args[1] == NULL)
		export_all(m);
	i = 0;
	while (cmd_args[++i] != NULL)
	{
		equal = ft_strchr(cmd_args[i], '=');
		if (!equal)
			no_value_case(cmd_args[i], m);
		else if (!*(equal + 1))
		{
			no_value_after_equal1(&i, cmd_args, equal, &qflags);
		}
		else
			value_after_equal(i, cmd, m, equal);
		qflags = qflags->next;
	}
}

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
		if (!*(equal + 1))
		{
			no_value_after_equal2(&i, cmd_args, equal, m);
			/*
			key = ft_substr(cmd_args[i], 0, equal - cmd_args[i]);
			if (cmd_args[i + 1] && !ft_strchr(cmd_args[i + 1], '='))
			{
				value = ft_strdup(cmd_args[i + 1]);
				i = i + 1;
			}
			else
				value = ft_strdup("");
			m->export_hidden = 0;*/
		}
		else
		{
			key = ft_substr(cmd_args[i], 0, equal - cmd_args[i]);
			value = get_value(cmd_args[i], equal + 1, cmd, m);
			update_envvar_util(key, value, m);
		}
		//update_envvar_util(key, value, m);
		i++;
	}
}


