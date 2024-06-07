/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:51:05 by bcai              #+#    #+#             */
/*   Updated: 2024/05/30 16:32:24 by bcai             ###   ########.fr       */
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

void	prepare_heredoc_file(t_heredoc *heredoc)
{
	open(heredoc->delimiter, O_RDWR | O_CREAT | O_TRUNC, 0666);
	heredoc->tmp_file = ft_strdup(heredoc->delimiter);
}

void	build_redir_list(t_cmd *cmd, t_m *m, t_inout **list)
{
	t_inout	*new_node;

	(void)m;
	new_node = NULL;
	new_node = (t_inout *)malloc(sizeof(t_inout) * 1);
	if (!new_node)
		return ;
	new_node->next = NULL;
	if (cmd->type == REDIR)
	{
		new_node->file_name = ft_strdup(((t_redircmd *)cmd)->file);
		new_node->mode = ((t_redircmd *)cmd)->mode;
		new_node->is_hd = 0;
		new_node->hdcmd = NULL;
	}
	else if (cmd->type == HEREDOC)
	{
		prepare_heredoc_file((t_heredoc *)cmd);
		new_node->file_name = ft_strdup(((t_heredoc *)cmd)->tmp_file);
		new_node->mode = O_RDONLY;
		new_node->is_hd = 1;
		new_node->hdcmd = (t_heredoc *)cmd;
	}
	add_node(list, new_node);
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
