/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:08 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 18:49:56 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(t_cmd *cmd, t_m *m)
{
	(void)cmd;
	(void)m;
	print_envvars();
}

static void	excessive_args_check(t_cmd *cmd, t_m *m, char **cmd_args)
{
	if (cmd_args[2] != NULL)
	{
		printf("exit\nbash: too many arguments\n");
		free_tree(cmd, m);
		lastfree_restore();
		exit(1);
	}
}

void	builtin_exit(t_cmd *cmd, t_m *m)
{
	char	**cmd_args;
	int	i;

	i = -1;
	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	if (cmd_args[1] != NULL)
	{
		if (cmd_args[1][0] == '-')
			i++;
		while (cmd_args[1][++i])
		{
			if (!ft_isdigit(cmd_args[1][i]))
			{
				printf("exit\nbash: exit: %s: numeric argument required\n", cmd_args[1]);
				exit(255);
			}
		}
		m->exit_status = ft_atoi(cmd_args[1]);
	}
	excessive_args_check(cmd, m, cmd_args);
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
