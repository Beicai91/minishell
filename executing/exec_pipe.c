/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:47:11 by bcai              #+#    #+#             */
/*   Updated: 2024/05/30 17:01:21 by bcai             ###   ########.fr       */
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
	if (pcmd->left->type == 9 || pcmd->right->type == 9)
	{
		waitpid(m->pid_left, &m->exit_status, 0);
		check_exit_status(m->exit_status, m);
	}
	m->pid_right = fork_check(m);
	if (m->pid_right == 0)
	{
		pipe_right_exec(m, pcmd);
		exit(0);
	}
	close(m->pfd[0]);
	close(m->pfd[1]);
	m->pipe_left_flag = 0;
	m->pipe_right_flag = 0;
	waitpid(m->pid_right, &m->exit_status, 0);
	check_exit_status(m->exit_status, m);
}

void	pipe_left_exec(t_m *m, t_pipecmd *pcmd)
{
	m->pipe_left_flag = 1;
	m->fdout_cpy = dup(STDOUT_FILENO);
	close(m->pfd[0]);
	dup2(m->pfd[1], STDOUT_FILENO);
	traverse_tree(pcmd->left, m);
	restore_inout(m->fdout_cpy, 1, m);
	close(m->pfd[1]);
	close(m->fdout_cpy);
}

void	pipe_right_exec(t_m *m, t_pipecmd *pcmd)
{
	m->pipe_right_flag = 1;
	m->fdin_cpy = dup(STDIN_FILENO);
	close(m->pfd[1]);
	dup2(m->pfd[0], STDIN_FILENO);
	traverse_tree(pcmd->right, m);
	restore_inout(m->fdin_cpy, 0, m);
	close(m->pfd[0]);
	close(m->fdin_cpy);
}

int	fork_check(t_m *m)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error(1, "exit", m, m->final_tree);
	return (pid);
}
