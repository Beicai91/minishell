/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.heredoc3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:18:59 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 17:19:03 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inlist_execution_util(t_execcmd *ecmd, t_m *m, t_inout **in_temp)
{	
	if (*in_temp == NULL)
	{
		traverse_tree((t_cmd *)ecmd, m);
		return (1);
	}
	while ((*in_temp)->next != NULL)
	{
		if (open((*in_temp)->file_name, (*in_temp)->mode, 0666) < 0)
		{
			printf("minishell$ %s:No such file or directory\n", \
				(*in_temp)->file_name);
			return (1);
		}
		(*in_temp) = (*in_temp)->next;
	}
	return (0);
}

void	inlist_execution(t_execcmd *ecmd, t_m *m)
{
	t_inout	*in_temp;
	int		fd;
	int		fdin_cpy;

	in_temp = m->in;
	if (inlist_execution_util(ecmd, m, &in_temp) == 1)
		return ;
	fdin_cpy = dup(STDIN_FILENO);
	fd = open(in_temp->file_name, in_temp->mode, 0666);
	if (fd < 0)
	{
		printf("minishell$ %s:No such file or directory\n", in_temp->file_name);
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close_fds(fdin_cpy, fd);
		perror("dup2:");
		return ;
	}
	close(fd);
	traverse_tree((t_cmd *)ecmd, m);
	restore_inout(fdin_cpy, 0, m);
	close(fdin_cpy);
}
