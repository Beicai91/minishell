/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:08 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 10:04:39 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(t_cmd *cmd, t_m *m)
{
	(void)cmd;
	(void)m;
	print_envvars();
}

void	builtin_exit(t_cmd *cmd, t_m *m)
{
	char	**cmd_args;

	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	if (cmd_args[1] != NULL)
		m->exit_status = ft_atoi(cmd_args[1]);
	printf("Operation terminated\n");
	free_tree(cmd, m);
	lastfree_restore();
	exit(m->exit_status);
}
