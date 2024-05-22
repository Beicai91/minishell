/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:56 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 10:00:37 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_path(t_m *m)
{
	t_envvar	*temp;

	temp = getter();
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, "PATH", 4) == 0)
			m->path = temp->value;
		temp = temp->next;
	}
	if (!m->path)
		return ;
	m->envp_path = ft_split(m->path, ':');
	if (!m->envp_path)
	{
		printf("Error: Failed to split PATH variable\n");
		return ;
	}
}

void	execve_error_message(t_execcmd *ecmd)
{
	if (ecmd->path_prob == 1)
		printf("minishell: %s: No such file or directory\n", ecmd->cmd_args[0]);
	else
		printf("minishell: %s: command not found\n", ecmd->cmd_args[0]);
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
			execve_error_message(ecmd);
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
	if (!m->path)
		ecmd->path_prob = 1;
	while (m->envp_path && m->envp_path[m->i] != NULL)
	{
		m->temp_path = ft_strjoin(m->envp_path[m->i], "/");
		m->path = ft_strjoin(m->temp_path, ecmd->cmd_args[0]);
		free(m->temp_path);
		m->temp_path = NULL;
		if (access(m->path, X_OK) == 0)
			break ;
		free(m->path);
		m->path = NULL;
		m->i++;
	}
}
