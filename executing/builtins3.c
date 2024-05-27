/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:08 by bcai              #+#    #+#             */
/*   Updated: 2024/05/24 13:44:08 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(t_cmd *cmd, t_m *m)
{
	(void)cmd;
	(void)m;
	print_envvars();
}

static void	is_numeric(t_cmd *cmd, t_m *m, char *arg_one)
{
	int	i;

	i = -1;
	if (arg_one[0] == '-')
		i++;
	while (arg_one[++i])
	{
		if (!ft_isdigit(arg_one[i]))
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n", arg_one);
			free_tree(cmd, m);
			free_2darray(m->minishell_envp);
			lastfree_restore();
			exit(255);
		}
	}
}

void	builtin_exit(t_cmd *cmd, t_m *m)
{
	char	**cmd_args;

	cmd_args = ((t_execcmd *)cmd)->cmd_args;
	if (cmd_args[1] == NULL)
	{
		free_tree(cmd, m);
		//test
		printf("ready to free minishell_envp\n");
		//
		free_2darray(m->minishell_envp);
		lastfree_restore();
		printf("exit\n");
		exit(m->exit_status);
	}
	else
	{
		is_numeric(cmd, m, cmd_args[1]);
		if (cmd_args[2] != NULL)
		{
			printf("exit\nminishell: exit: too many arguments\n");
			return ;
		}
		m->exit_status = ft_atoi(cmd_args[1]);
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
