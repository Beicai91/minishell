/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:50:46 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 17:19:07 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_list(t_redircmd *rcmd, t_cmd *cmd, t_m *m, t_inout **list)
{
	build_redir_list(cmd, m, list);
	if (rcmd->cmd->type != EXEC)
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
	m->position = ON_MAIN;
}

void	parselist_execute(t_cmd *cmd, t_m *m)
{
	t_execcmd	*ecmd;
	int			fdout_cpy;

	if (g_sig_indicator != 0)
	{
		g_sig_indicator = 0;
		unlink("heredoc_tmp");
		free_list(&(m->in));
		free_list(&(m->out));
		m->position = ON_MAIN;
		return ;
	}
	ecmd = (t_execcmd *)cmd;
	fdout_cpy = dup(STDOUT_FILENO);
	if (m->out != NULL)
		inlist_execution_loop(m, fdout_cpy, ecmd);
	else
		inlist_execution(ecmd, m);
	close(fdout_cpy);
	unlink("heredoc_tmp");
	free_list(&(m->out));
	free_list(&(m->in));
}

void	inlist_execution_loop(t_m *m, int fdout_cpy, t_execcmd *ecmd)
{
	int		fd;
	t_inout	*to_free;
//test
printf("inlist execution loop\n");
//
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
	//test
	printf("file b fd %d\n", fd);
	//
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close_fds(fdout_cpy, fd);
		return ;
	}
	close(fd);
	inlist_execution(ecmd, m);
	restore_inout(fdout_cpy, 1, m);
}
