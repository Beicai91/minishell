/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:56 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 10:47:03 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_path(t_m *m)
{
	m->i = 0;
	while (m->envp[m->i] != NULL)
	{
		if (ft_strncmp(m->envp[m->i], "PATH=", 5) == 0)
			m->path = m->envp[m->i];
		m->i++;
	}
	if (!m->path)
		return ;
	m->envp_path = ft_split(m->path, ':');
	if (!m->envp_path)
	{
		printf("Error: Failed to split PATH variable.\n");
		return ;
	}
}

void	execute_simple_command(t_execcmd *ecmd, t_m *m)
{
	find_path(m);
	if (ft_strchr(ecmd->cmd_args[0], '/'))
		m->path = ft_strdup(ecmd->cmd_args[0]);
	else
	{
		m->i = 0;
		find_executable_path(m, ecmd);
	}
	free_2darray(m->envp_path);
	m->envp_path = NULL;
	m->pid = fork_check(m);
	if (m->pid == 0)
	{
		if (execve(m->path, ecmd->cmd_args, m->envp) == -1)
		{
			printf("Error: Execve failed.\n");
			exit(127);
		}
	}
	else
	{
		waitpid(m->pid, &m->exit_status, 0);
		check_exit_status(m->exit_status, m);
	}
}

void	find_executable_path(t_m *m, t_execcmd *ecmd)
{
	while (m->envp_path[m->i] != NULL)
	{
		m->temp_path = ft_strjoin(m->envp_path[m->i], "/");
		m->path = ft_strjoin(m->temp_path, ecmd->cmd_args[0]);
		free(m->temp_path);
		m->temp_path = NULL;
		if (!m->path)
		{
			lastfree_restore();
			exit(127);
		}
		if (access(m->path, X_OK) == 0)
			break ;
		free(m->path);
		m->path = NULL;
		m->i++;
	}
}
