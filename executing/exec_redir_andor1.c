/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_andor1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:03:14 by bcai              #+#    #+#             */
/*   Updated: 2024/06/06 14:24:03 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	traverse_lr2(t_cmd *left, t_cmd *right, t_m *m)
{
	traverse_tree2(left, m);
	traverse_tree2(right, m);
}

void	traverse_lr_and2(t_cmd *left, t_cmd *right, t_m *m)
{
	traverse_tree2(left, m);
	if (m->exit_status == 0)
		traverse_tree2(right, m);
}

void	traverse_lr_or2(t_cmd *left, t_cmd *right, t_m *m)
{
	traverse_tree2(left, m);
	if (m->exit_status != 0)
		traverse_tree2(right, m);
}

void	traverse_tree2(t_cmd *cmd, t_m *m)
{
	if (cmd->type == EXEC)
	{
		if (((t_execcmd *)cmd)->cmd_args == NULL)
			return ;
		parselist_execute2(cmd, m);
	}
	else if (cmd->type == REDIR)
		redir_heredoc(cmd, m);
	else if (cmd->type == HEREDOC)
		redir_heredoc(cmd, m);
	else if (cmd->type == PIPE)
		execute_pipe_command((t_pipecmd *)cmd, m);
	else if (cmd->type == LIST)
		traverse_lr2(((t_listcmd *)cmd)->left, ((t_listcmd *)cmd)->right, m);
	else if (cmd->type == AND)
		traverse_lr_and2(((t_and *)cmd)->left, ((t_and *)cmd)->right, m);
	else if (cmd->type == OR)
		traverse_lr_or2(((t_or *)cmd)->left, ((t_or *)cmd)->right, m);
	else
		return ;
}
