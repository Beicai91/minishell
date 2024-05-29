/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:45:20 by bcai              #+#    #+#             */
/*   Updated: 2024/05/24 16:54:04 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_error(t_cmd *cmd, t_m *m, char *msg)
{
	printf("%s\n", msg);
	free_tree(cmd, m);
	check_exit_status(-1, m);
	lastfree_restore();
	exit(1);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0 || ft_strchr(cmd, '='))
		return (1);
	else
		return (0);
}

void	print_helper(char **cmd_args, int *i, t_qflag *cqflags)
{
	if (*cmd_args[*i] == '\0')
		(*i)++;
	else
	{
		if (cqflags->quote_flag == 1)
			write(1, cmd_args[*i], ft_strlen(cmd_args[*i]));
		else
		{
			write(1, cmd_args[*i], ft_strlen(cmd_args[*i]));
			write(1, " ", 1);
		}
		(*i)++;
	}
}

void	update_eles(int *n_flag, t_qflag **cqflags, int *i)
{
	*n_flag = 1;
	*cqflags = (*cqflags)->next;
	(*i)++;
}

void	build_envvar_list(t_envvar *envvars, t_list **envcpy)
{
	char	*temp;

	while (envvars != NULL)
	{
		if (*(envvars->value) == '\0')
			temp = strdup(envvars->key);
		else
		{
			temp = ft_strjoin(envvars->key, "=\"");
			temp = join_free(temp, envvars->value);
			temp = join_free(temp, "\"");
		}
		build_files_list(envcpy, temp);
		free(temp);
		temp = NULL;
		envvars = envvars->next;
	}
}