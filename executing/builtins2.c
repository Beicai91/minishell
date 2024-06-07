/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:45:50 by bcai              #+#    #+#             */
/*   Updated: 2024/06/06 09:43:08 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	export_vars(char **cmd_args, t_cmd *cmd, t_m *m)
{
	int		i;
	char	*equal;
	t_qflag	*qflags;

	qflags = ((t_execcmd *)cmd)->qflags->next;
	i = 0;
	while (cmd_args[++i] != NULL)
	{
		equal = ft_strchr(cmd_args[i], '=');
		if (!equal)
			no_value_case(cmd_args[i], m);
		else if (!*(equal + 1))
		{
			if (no_value_after_equal1(&i, cmd_args, equal, &qflags) == 1)
				m->exit_status = 1;
		}
		else
		{
			if (value_after_equal(i, cmd, m, equal) == 1)
				m->exit_status = 1;
		}
		qflags = qflags->next;
	}
}

void	builtin_export(t_cmd *cmd, t_m *m)
{
	char	**cmd_args;

	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	if (cmd_args[1] == NULL)
		export_all(m);
	export_vars(cmd_args, cmd, m);
}
