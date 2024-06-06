/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:56 by bcai              #+#    #+#             */
/*   Updated: 2024/06/04 18:50:08 by eprzybyl         ###   ########.fr       */
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
	struct sigaction	sa;

	minishell_envp(m);
	find_path(m);
	find_executable_path(m, ecmd);
	m->pid = fork_check(m);
	if (m->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(m->path, ecmd->cmd_args, m->minishell_envp) == -1)
		{
			execve_error_message(ecmd);
			exit(127);
		}
	}
	else
	{
		signal_tracking(&sa, m);
		waitpid(m->pid, &m->exit_status, 0);
		check_exit_status(m->exit_status, m);
		free_2darray(m->minishell_envp);
	}
}

void	find_executable_path(t_m *m, t_execcmd *ecmd)
{
	if (ft_strchr(ecmd->cmd_args[0], '/'))
		m->path = ft_strdup(ecmd->cmd_args[0]);
	else
	{
		m->i = 0;
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
	free_2darray(m->envp_path);
	m->envp_path = NULL;
}

void	builtin_exec(t_cmd *cmd, t_m *m)
{
	if (is_builtin(((t_execcmd *)cmd)->cmd_args[0]) == 1)
		run_builtin(cmd, m);
	else
	{
		m->position = ON_EXEC;
		execute_simple_command((t_execcmd *)cmd, m);
		m->position = ON_MAIN;
	}
}
