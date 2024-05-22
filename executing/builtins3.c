/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:08 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 18:22:31 by bcai             ###   ########.fr       */
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
	free_tree(cmd, m);
	lastfree_restore();
	printf("exit\n");
	exit(m->exit_status);
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

void	builtin_pwd(t_cmd *cmd, t_m *m)
{
	char	*buffer;
	size_t	size;
	char	*cwd;

	size = 1024;
	while (1)
	{
		buffer = safe_malloc(size, CHAR, cmd);
		cwd = getcwd(buffer, size);
		if (cwd)
		{
			printf("%s\n", cwd);
			free(buffer);
			break ;
		}
		else
			resize_or_free(buffer, m, &size);
	}
}
