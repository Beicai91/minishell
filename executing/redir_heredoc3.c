/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:18:59 by bcai              #+#    #+#             */
/*   Updated: 2024/06/04 18:45:39 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_heredoc_command(t_heredoc *heredoc, t_m *m)
{
	if (m->pipe_left_flag == 1)
		restore_inout(m->fdout_cpy, 1, m);
	if (m->pipe_right_flag == 1)
		restore_inout(m->fdin_cpy, 0, m);
	if (m->redir_out == 1)
		restore_inout(m->out_cpy, 1, m);
	m->heredoc_fd = open(heredoc->tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (heredoc->is_quoted == 1)
		no_line_expansion(heredoc, m->heredoc_fd, m);
	else
		expand_line(heredoc, m->heredoc_fd, m);
	close(m->heredoc_fd);
	if (m->pipe_left_flag == 1)
		dup2(m->pfd[1], STDOUT_FILENO);
	if (m->pipe_right_flag == 1)
		dup2(m->pfd[0], STDIN_FILENO);
	if (m->redir_out == 1)
		dup2(m->fd_outfile, STDOUT_FILENO);
}

int	inlist_execution_util(t_execcmd *ecmd, t_m *m, t_inout **in_temp)
{	
	t_inout	*second_last;

	if (*in_temp == NULL)
	{
		traverse_tree((t_cmd *)ecmd, m);
		return (1);
	}
	while (*in_temp != NULL)
	{
		if (g_sig_indicator != 0)
			return (1);
		if (open((*in_temp)->file_name, (*in_temp)->mode, 0666) < 0)
		{
			printf("minishell$ %s:No such file or directory\n", \
				(*in_temp)->file_name);
			m->stop_executing = 1;
			return (1);
		}
		if ((*in_temp)->is_hd == 1)
			execute_heredoc_command((*in_temp)->hdcmd, m);
		second_last = *in_temp;
		(*in_temp) = (*in_temp)->next;
	}
	(*in_temp) = second_last;
	return (0);
}

void	inlist_execution(t_execcmd *ecmd, t_m *m)
{
	t_inout	*in_temp;
	int		fd;
	int		fdin_cpy;

	in_temp = m->in;
	if (inlist_execution_util(ecmd, m, &in_temp) == 1)
		return ;
	fdin_cpy = dup(STDIN_FILENO);
	fd = open(in_temp->file_name, in_temp->mode, 0666);
	if (fd < 0)
	{
		printf("minishell$ %s:No such file or directory\n", in_temp->file_name);
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close_fds(fdin_cpy, fd);
		perror("dup2:");
		return ;
	}
	close(fd);
	traverse_tree((t_cmd *)ecmd, m);
	restore_inout(fdin_cpy, 0, m);
	close(fdin_cpy);
}
