/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:50:46 by bcai              #+#    #+#             */
/*   Updated: 2024/06/06 13:03:50 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_list(t_redircmd *rcmd, t_cmd *cmd, t_m *m, t_inout **list)
{
	build_redir_list(cmd, m, list);
	if (rcmd->cmd->type == AND || rcmd->cmd->type == OR)
		traverse_tree2(rcmd->cmd, m);
	else if (rcmd->cmd->type != EXEC)
		traverse_tree(rcmd->cmd, m);
	else
		parselist_execute(rcmd->cmd, m);
}

void	redir_heredoc(t_cmd *cmd, t_m *m)
{
	t_redircmd	*rcmd;
	t_heredoc	*heredoc;

	if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (rcmd->fd == 0)
			redir_list(rcmd, cmd, m, &(m->in));
		else if (rcmd->fd == 1)
			redir_list(rcmd, cmd, m, &(m->out));
	}
	else if (cmd->type == HEREDOC)
	{
		m->position = ON_HEREDOC;
		heredoc = (t_heredoc *)cmd;
		build_redir_list(cmd, m, &(m->in));
		if (heredoc->cmd->type != EXEC)
			traverse_tree(heredoc->cmd, m);
		else
			parselist_execute(heredoc->cmd, m);
	}
	free_list(&(m->out));
	free_list(&(m->in));
	m->position = ON_MAIN;
}

void	unlink_heredoc_file(t_m *m)
{
	t_inout	*in_temp;

	in_temp = m->in;
	while (in_temp != NULL)
	{
		if (in_temp->is_hd == 1)
			unlink(in_temp->file_name);
		in_temp = in_temp->next;
	}
}

void	parselist_execute(t_cmd *cmd, t_m *m)
{
	t_execcmd	*ecmd;

	ecmd = (t_execcmd *)cmd;
	m->out_cpy = dup(STDOUT_FILENO);
	if (m->out != NULL)
		inlist_execution_loop(m, ecmd);
	else
		inlist_execution(ecmd, m);
	if (g_sig_indicator != 0)
		g_sig_indicator = 0;
	close(m->out_cpy);
	unlink_heredoc_file(m);
	m->redir_out = 0;
}

void	inlist_execution_loop(t_m *m, t_execcmd *ecmd)
{
	int		fd;
	t_inout	*to_free;

	m->redir_out = 1;
	while (m->out->next != NULL)
	{
		fd = open(m->out->file_name, m->out->mode, 0666);
		close(fd);
		to_free = m->out;
		m->out = m->out->next;
		free(to_free->file_name);
		free(to_free);
	}
	fd = open(m->out->file_name, m->out->mode, 0666);
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
