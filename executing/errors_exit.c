/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:38 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 10:06:14 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_error(int error_code, char *str, t_m *m, t_cmd *cmd)
{
	if (cmd)
		free_tree(cmd, m);
	if (m->path != NULL)
		free(m->path);
	printf("Error: %s\n", str);
	m->exit_status = error_code;
}

void	report_error(int error_code, char *str, t_m *m, t_cmd *cmd)
{
	if (cmd)
		free_tree(cmd, m);
	(void)error_code;
	(void)cmd;
	if (m->path != NULL)
		free(m->path);
	printf((const char *)stderr, "Error: %s\n", str);
}

void	check_exit_status(int status, t_m *m)
{
	if (m->path != NULL)
	{
		free(m->path);
		m->path = NULL;
	}
	if (WIFEXITED(status))
		m->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		m->exit_status = -WTERMSIG(status);
	else
		m->exit_status = -1;
}

void	free_2darray(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i] != NULL)
		{
			//test
			printf("freeing %s\n", arr[i]);
			//
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	close_fds(int fdin_cpy, int fd)
{
	close(fdin_cpy);
	close(fd);
}
