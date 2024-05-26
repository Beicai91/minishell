/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:56:35 by bcai              #+#    #+#             */
/*   Updated: 2024/05/24 12:18:57 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_heredoc(t_cmd *cmd)
{
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)cmd;
	if (heredoc->delimiter != NULL)
		free(heredoc->delimiter);
	free_memory(heredoc->cmd);
	free(cmd);
}

void	free_redir(t_cmd *cmd)
{
	t_redircmd	*redircmd;

	redircmd = (t_redircmd *)cmd;
	if (redircmd->file != NULL)
		free(redircmd->file);
	free_memory(redircmd->cmd);
	free(cmd);
}

void	free_exec(t_cmd *cmd)
{
	t_execcmd	*execcmd;
	t_list		*temp;

	execcmd = (t_execcmd *)cmd;
	if (execcmd->cmd_args != NULL)
		free_2darray(execcmd->cmd_args);
	if (execcmd->cmd_args == NULL)
	{
		while (execcmd->cmdargs != NULL)
		{
			temp = execcmd->cmdargs;
			//test
			printf("freeing %s\n", temp->content);
			//
			free(temp->content);
			execcmd->cmdargs = execcmd->cmdargs->next;
			free(temp);
		}
	}
	free(cmd);
	cmd = NULL;
}

void	free_memory(t_cmd *cmd)
{
	int	type;

	if (cmd == NULL)
		return ;
	type = cmd->type;
	if (type == EXEC)
		free_exec(cmd);
	else if (type == REDIR)
		free_redir(cmd);
	else if (type == HEREDOC)
		free_heredoc(cmd);
	else if (type == LIST)
		free_lrlist(cmd);
	else if (type == PIPE)
		free_lrpipe(cmd);
	else if (type == AND)
		free_lrand(cmd);
	else if (type == OR)
		free_lror(cmd);
}
