/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:51:05 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 10:58:48 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	restore_inout(int fd_cpy, int in_out, t_m *m)
{
	if (in_out == 1)
	{
		if (dup2(fd_cpy, STDOUT_FILENO) == -1)
		{
			perror("dup2 ");
			free_tree(m->final_tree, m);
			close(fd_cpy);
			return ;
		}
	}
	else
	{
		if (dup2(fd_cpy, STDIN_FILENO) == -1)
		{
			perror("dup2 ");
			free_tree(m->final_tree, m);
			close(fd_cpy);
			return ;
		}
	}
}

void	add_node(t_inout **list, t_inout *new_node)
{
	if (*list == NULL)
		*list = new_node;
	else
	{
		new_node->next = *list;
		*list = new_node;
	}
}

void	build_redir_list(t_cmd *cmd, t_m *m, t_inout **list)
{
	t_inout	*new_node;

	new_node = NULL;
	new_node = (t_inout *)malloc(sizeof(t_inout) * 1);
	if (!new_node)
	{
		free_tree(m->final_tree, m);
		return ;
	}
	new_node->next = NULL;
	if (cmd->type == REDIR)
	{
		new_node->file_name = ft_strdup(((t_redircmd *)cmd)->file);
		new_node->mode = ((t_redircmd *)cmd)->mode;
	}
	else if (cmd->type == HEREDOC)
	{
		execute_heredoc_command((t_heredoc *)cmd, m);
		new_node->file_name = ft_strdup(((t_heredoc *)cmd)->tmp_file);
		new_node->mode = O_RDONLY;
	}
	add_node(list, new_node);
}

void	execute_heredoc_command(t_heredoc *heredoc, t_m *m)
{
	if (m->pipe_flag == 1)
		restore_inout(m->fdout_cpy, 1, m);
	m->heredoc_fd = open("heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	heredoc->tmp_file = ft_strdup("heredoc_tmp");
	if (heredoc->is_quoted == 1)
		no_line_expansion(heredoc, m->heredoc_fd, m);
	else
		expand_line(heredoc, m->heredoc_fd, m);
	close(m->heredoc_fd);
	if (m->pipe_flag == 1)
		dup2(m->pfd[1], STDOUT_FILENO);
}

void	free_list(t_inout **list)
{
	t_inout	*temp;

	while (*list != NULL)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp->file_name);
		free(temp);
	}
	return ;
}
