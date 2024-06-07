/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_andor2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:23:37 by bcai              #+#    #+#             */
/*   Updated: 2024/06/06 14:28:16 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	inlist_execution_loop2(t_m *m, t_execcmd *ecmd)
{
	int		fd;
	t_inout	*to_free;

	m->redir_out = 1;
	while (m->out->next != NULL)
	{
		fd = open(m->out->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		close(fd);
		to_free = m->out;
		m->out = m->out->next;
		free(to_free->file_name);
		free(to_free);
	}
	fd = open(m->out->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	m->fd_outfile = fd;
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close_fds(m->out_cpy, fd);
		return ;
	}
	inlist_execution(ecmd, m);
	restore_inout(m->out_cpy, 1, m);
	close(fd);
}

void	parselist_execute2(t_cmd *cmd, t_m *m)
{
	t_execcmd	*ecmd;

	ecmd = (t_execcmd *)cmd;
	m->out_cpy = dup(STDOUT_FILENO);
	if (m->out != NULL)
		inlist_execution_loop2(m, ecmd);
	else
		inlist_execution(ecmd, m);
	if (g_sig_indicator != 0)
		g_sig_indicator = 0;
	close(m->out_cpy);
	unlink_heredoc_file(m);
	m->redir_out = 0;
}
