/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:47:11 by bcai              #+#    #+#             */
/*   Updated: 2024/05/19 18:00:20 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pipe_command(t_pipecmd *pcmd, t_m *m)
{
	if (pipe(m->pfd) < 0)
		exit_error(1, "Problem with creating a pipe", m, m->final_tree);
	m->pid_left = fork_check(m);
	if (m->pid_left == 0)
	{
		pipe_left_exec(m, pcmd);
		exit(0);
	}
	waitpid(m->pid_left, &m->exit_status, 0);
	printf("waited and successfully \n");
	check_exit_status(m->exit_status, m);
	m->pid_right = fork_check(m);
	if (m->pid_right == 0)
	{
		pipe_right_exec(m, pcmd);
		exit(0);
	}
	close(m->pfd[0]);
	close(m->pfd[1]);
	
	waitpid(m->pid_right, &m->exit_status, 0);
	check_exit_status(m->exit_status, m);
}

void	pipe_left_exec(t_m *m, t_pipecmd *pcmd)
{
	close(m->pfd[0]);
	dup2(m->pfd[1], STDOUT_FILENO);
	close(m->pfd[1]);
	traverse_tree(pcmd->left, m);
}

void	pipe_right_exec(t_m *m, t_pipecmd *pcmd)
{
	close(m->pfd[1]);
	dup2(m->pfd[0], STDIN_FILENO);
	close(m->pfd[0]);
	traverse_tree(pcmd->right, m);
}

int	fork_check(t_m *m)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error(1, "exit", m, m->final_tree);
	return (pid);
}
