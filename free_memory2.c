/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:56:49 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 12:21:19 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lrlist(t_cmd *cmd)
{
	t_listcmd	*listcmd;

	listcmd = (t_listcmd *)cmd;
	free_memory(listcmd->left);
	free_memory(listcmd->right);
	free(cmd);
}

void	free_lrpipe(t_cmd *cmd)
{
	t_pipecmd	*pipecmd;

	pipecmd = (t_pipecmd *)cmd;
	free_memory(pipecmd->left);
	free_memory(pipecmd->right);
	free(cmd);
}

void	free_lrand(t_cmd *cmd)
{
	t_and	*andcmd;

	andcmd = (t_and *)cmd;
	free_memory(andcmd->left);
	free_memory(andcmd->right);
	free(cmd);
}

void	free_lror(t_cmd *cmd)
{
	t_or	*orcmd;

	orcmd = (t_or *)cmd;
	free_memory(orcmd->left);
	free_memory(orcmd->right);
	free(cmd);
}
