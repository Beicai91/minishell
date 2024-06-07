/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:54:03 by bcai              #+#    #+#             */
/*   Updated: 2024/06/05 23:07:27 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	add_content_node(t_execcmd *ecmd, char *s_tkn, char *e_tkn, t_cmd *cmd)
{
	t_list	*node;
	size_t	i;
	int		escape_flag;
	size_t	size;

	node = (t_list *)safe_malloc(1, NODE, cmd);
	node->next = NULL;
	size = e_tkn - s_tkn + 2;
	escape_flag = 0;
	i = 0;
	while (i < size)
	{
		if (s_tkn[i] == '\\')
			escape_flag = 1;
		i++;
	}
	if (escape_flag == 1)
		size--;
	node->content = safe_malloc(size, CHAR, cmd);
	ft_strlcpy_special(node->content, s_tkn, size);
	ft_lstadd_back(&(ecmd->cmdargs), node);
}

void	populate_cmdargs(t_execcmd *ecmd, char *s_tkn, char *e_tkn, t_cmd *cmd)
{
	t_qflag	*flag_node;
	t_qflag	*cq_node;

	add_content_node(ecmd, s_tkn, e_tkn, cmd);
	flag_node = (t_qflag *)malloc(sizeof(t_qflag) * 1);
	if (!flag_node)
		return ;
	flag_node->quote_flag = 0;
	flag_node->next = NULL;
	add_qflag(&(ecmd->qflags), flag_node);
	cq_node = (t_qflag *)malloc(sizeof(t_qflag) * 1);
	if (!cq_node)
		return ;
	if ((*(e_tkn + 1) == 34 && *(e_tkn + 2) != ' ') || (*(e_tkn + 1) == 39
			&& *(e_tkn + 2) != ' '))
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
	if ((*(e_tkn + 1) == 34 && *(e_tkn + 2) != ' ') || (*(e_tkn + 1) == 39
			&& *(e_tkn + 2) != ' '))
		cq_node->quote_flag = 1;
	else
		cq_node->quote_flag = 0;
	cq_node->next = NULL;
	add_qflag(&(ecmd->cqflags), cq_node);
}
