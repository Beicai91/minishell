/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:08:26 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 11:08:36 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*safe_malloc(size_t size, t_type type, t_cmd *cmd)
{
	void	*p;

	p = NULL;
	if (type == CHAR)
		p = malloc(sizeof(char) * size);
	else if (type == EXEC)
		p = malloc(sizeof(t_execcmd) * size);
	else if (type == REDIR)
		p = malloc(sizeof(t_redircmd) * size);
	else if (type == HEREDOC)
		p = malloc(sizeof(t_heredoc) * size);
	else if (type == NODE)
		p = malloc(sizeof(t_list) * size);
	else if (type == STRING_ARRAY)
		p = malloc(sizeof(char *) * size);
	else if (type == QFLAG)
		p = malloc(sizeof(t_qflag) * size);
	if (!p)
	{
		perror("Malloc");
		free_memory(cmd);
		lastfree_restore();
		exit(1);
	}
	return (p);
}

char	*safe_malloc2(size_t size, t_type type, t_cmd *left_cmd,
		t_cmd *right_cmd)
{
	void	*p;

	p = NULL;
	if (type == PIPE)
		p = malloc(sizeof(t_pipecmd) * size);
	else if (type == LIST)
		p = malloc(sizeof(t_listcmd) * size);
	else if (type == AND)
		p = malloc(sizeof(t_and) * size);
	else if (type == OR)
		p = malloc(sizeof(t_or) * size);
	if (!p)
	{
		printf("Memory allocation problem.");
		free_memory(left_cmd);
		free_memory(right_cmd);
		lastfree_restore();
		exit(1);
	}
	else
		return (p);
}
