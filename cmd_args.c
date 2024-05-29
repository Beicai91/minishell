/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:54:03 by bcai              #+#    #+#             */
/*   Updated: 2024/05/24 16:23:41 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_flagnode(t_qflag **flags)
{
	t_qflag	*flag_node;

	flag_node = safe_malloc(1, QFLAG, NULL);
	flag_node->quote_flag = 0;
	flag_node->next = NULL;
	add_qflag(flags, flag_node);
}

void	check_exec_flags(t_execcmd *ecmd)
{
	int	i;
	int	j;
	int	count;
	char	**cmd_args;
	t_qflag	*tmp;

	if (ecmd->cmd_args == NULL)
		return ;
	i = 0;
	cmd_args = ecmd->cmd_args;
	while (cmd_args[i] != NULL)
		i++;
	j = 0;
	tmp = ecmd->qflags;
	while (tmp != NULL)
	{
		j++;
		tmp = tmp->next;
	}
	count = i - j;
	while (count > 0)
	{
		add_flagnode(&(ecmd->qflags));
		add_flagnode(&(ecmd->cqflags));
		count--;
	}
}

void	get_cmd_args(t_execcmd *execcmd, t_cmd *cmd)
{
	int		len;
	t_list	*temp;
	int		i;

	execcmd->cmdargs = check_wildcard(execcmd->cmdargs);
	len = ft_lstsize(execcmd->cmdargs);
	if (len != 0)
	{
		execcmd->cmd_args = safe_malloc(len + 1, STRING_ARRAY, cmd);
		temp = execcmd->cmdargs;
		i = 0;
		while (temp != NULL)
		{
			execcmd->cmd_args[i++] = temp->content;
			temp = temp->next;
		}
		execcmd->cmd_args[i] = NULL;
	}
	check_exec_flags(execcmd);
}

void	populate_cmdargs(t_execcmd *ecmd, char *s_tkn, char *e_tkn, t_cmd *cmd)
{
	t_list	*node;
	t_qflag	*flag_node;
	t_qflag	*cq_node;

	node = (t_list *)safe_malloc(1, NODE, cmd);
	node->next = NULL;
	node->content = safe_malloc(e_tkn - s_tkn + 2, CHAR, cmd);
	ft_strlcpy(node->content, s_tkn, e_tkn - s_tkn + 2);
	ft_lstadd_back(&(ecmd->cmdargs), node);
	flag_node = (t_qflag *)malloc(sizeof(t_qflag) * 1);
	if (!flag_node)
		return ;
	flag_node->quote_flag = 0;
	flag_node->next = NULL;
	add_qflag(&(ecmd->qflags), flag_node);
	cq_node = (t_qflag *)malloc(sizeof(t_qflag) * 1);
	if (!cq_node)
		return ;
	if ((*(e_tkn + 1) == 34 && *(e_tkn + 2) != ' ' ) \
		|| (*(e_tkn + 1) == 39 && *(e_tkn + 2) !=  ' ' ))
		cq_node->quote_flag = 1;
	else
		cq_node->quote_flag = 0;
	cq_node->next = NULL;
	add_qflag(&(ecmd->cqflags), cq_node);
}

void	cmdargs_quote(t_execcmd *ecmd, char *s_tkn, char *e_tkn, char **start)
{
	t_list	*node;
	t_qflag	*flag_node;
	t_qflag	*cq_node;

	node = (t_list *)safe_malloc(1, NODE, NULL);
	node->content = safe_malloc(e_tkn - s_tkn + 2, CHAR, NULL);
	ft_strlcpy(node->content, s_tkn, e_tkn - s_tkn + 2);
	node->next = NULL;
	ft_lstadd_back(&(ecmd->cmdargs), node);
	(*start)++;
	flag_node = safe_malloc(1, QFLAG, NULL);
	if (ecmd->tkn_type == 34)
		flag_node->quote_flag = 34;
	else
		flag_node->quote_flag = 39;
	flag_node->next = NULL;
	add_qflag(&(ecmd->qflags), flag_node);
	cq_node = safe_malloc(1, QFLAG, NULL);
	if ((*(e_tkn + 1) == 34 && *(e_tkn + 2) != ' ' ) \
		|| (*(e_tkn + 1) == 39 && *(e_tkn + 2) !=  ' ' ))
		cq_node->quote_flag = 1;
	else
		cq_node->quote_flag = 0;
	cq_node->next = NULL;
	add_qflag(&(ecmd->cqflags), cq_node);
}
