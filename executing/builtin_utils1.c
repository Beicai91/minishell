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
	t_gl	*gl;

	gl = get_gl();
	if (*cmd_args[*i] == '\0')
	{
		//test
		//printf("skip this\n");
		//
		(*i)++;
	}
	else
	{
		if (cqflags->quote_flag == 1)
		{
			//test
			//printf("cqflag %d\nready to write %s\n", cqflags->quote_flag, cmd_args[*i]);
			//
			write(1, cmd_args[*i], ft_strlen(cmd_args[*i]));
		}
		else
		{
			write(1, cmd_args[*i], ft_strlen(cmd_args[*i]));
			write(1, " ", 1);
		}
		(*i)++;
		/*
		if (cmd_args[*i + 1] && *cmd_args[*i + 1] == '\0')
		{
			//printf("%s", cmd_args[*i]);
			write(1, cmd_args[*i], ft_strlen(cmd_args[*i]));
			(*i)++;
		}
		else
		{
			if (gl->consec_quotes == 0 || gl->quoted == 0)
			{
				//test
				//printf("gl->consec_quotes %d\n", gl->consec_quotes);
				//printf("gl->quoted %d\n", gl->quoted);
				//
				write(1, cmd_args[*i], ft_strlen(cmd_args[*i]));
				write(1, " ", 1);
			}
			else
				write(1, cmd_args[*i], ft_strlen(cmd_args[*i]));
			(*i)++;
		}*/
	}
}
