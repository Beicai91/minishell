/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_init2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:56:17 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 11:33:02 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipecmd	*pipecmd_init(t_cmd *left_cmd, t_cmd *right_cmd)
{
	t_pipecmd	*pipecmd;

	pipecmd = (t_pipecmd *)safe_malloc2(1, PIPE, left_cmd, right_cmd);
	pipecmd->type = PIPE;
	pipecmd->left = left_cmd;
	pipecmd->right = right_cmd;
	return (pipecmd);
}

t_listcmd	*listcmd_init(t_cmd *left_cmd, t_cmd *right_cmd)
{
	t_listcmd	*listcmd;

	listcmd = (t_listcmd *)safe_malloc2(1, LIST, left_cmd, right_cmd);
	listcmd->type = LIST;
	listcmd->left = left_cmd;
	listcmd->right = right_cmd;
	return (listcmd);
}

t_and	*andcmd_init(t_cmd *left_cmd, t_cmd *right_cmd)
{
	t_and	*andcmd;

	andcmd = (t_and *)safe_malloc2(1, AND, left_cmd, right_cmd);
	andcmd->type = AND;
	andcmd->left = left_cmd;
	andcmd->right = right_cmd;
	return (andcmd);
}

t_or	*orcmd_init(t_cmd *left_cmd, t_cmd *right_cmd)
{
	t_or	*orcmd;

	orcmd = (t_or *)safe_malloc2(1, OR, left_cmd, right_cmd);
	orcmd->type = OR;
	orcmd->left = left_cmd;
	orcmd->right = right_cmd;
	return (orcmd);
}
