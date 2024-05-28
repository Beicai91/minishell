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
}

void	populate_cmdargs(t_execcmd *ecmd, char *s_token, char *e_token,
		t_cmd *cmd)
{
	t_list	*node;
	t_qflag	*flag_node;
	t_qflag	*cq_node;

	node = (t_list *)safe_malloc(1, NODE, cmd);
	//test
	//printf("in populate_cmdargs e_token %c\n", *e_token);
	//
	node->next = NULL;
	node->content = safe_malloc(e_token - s_token + 2, CHAR, cmd);//before + 1
	ft_strlcpy(node->content, s_token, e_token - s_token + 2);//before + 1
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
	
	if ((*(e_token + 1) == 34 && *(e_token + 2) == 34 && *(e_token + 3) != ' ') || (*(e_token + 1) == 39 && *(e_token + 2) == 39 && *(e_token + 3) != ' '))
		cq_node->quote_flag = 1;
	else
		cq_node->quote_flag = 0;
	cq_node->next = NULL;
	add_qflag(&(ecmd->cqflags), cq_node);
	//test
	//printf("cmad_args %s\n cq_flag %d\n", node->content, cq_node->quote_flag);
	//
}

void	cmdargs_quote(t_execcmd *ecmd, char *s_token,
		char *e_token, char **start)
{
	t_list	*node;
	t_qflag	*flag_node;
	t_qflag	*cq_node;
	t_gl	*gl;

	gl = get_gl();
	//gl->quoted = 1;
	node = (t_list *)safe_malloc(1, NODE, NULL);
	//test
	printf("in cmdargs_quote, e_token %c\n", *e_token);
	//
	node->content = safe_malloc(e_token - s_token + 2, CHAR, NULL);
	ft_strlcpy(node->content, s_token, e_token - s_token + 2);
	node->next = NULL;
	ft_lstadd_back(&(ecmd->cmdargs), node);
	(*start)++;
	flag_node = (t_qflag *)malloc(sizeof(t_qflag) * 1);
	if (!flag_node)
		return ;
	if (ecmd->tkn_type == 34)
		flag_node->quote_flag = 34;
	else
		flag_node->quote_flag = 39;
	flag_node->next = NULL;
	add_qflag(&(ecmd->qflags), flag_node);
	cq_node = (t_qflag *)malloc(sizeof(t_qflag) * 1);
	if (!cq_node)
		return ;
	if (*(e_token + 2) == 39 || *(e_token + 2) == 34)
		cq_node->quote_flag = 1;
	else
		cq_node->quote_flag = 0;
	cq_node->next = NULL;
	add_qflag(&(ecmd->cqflags), cq_node);
	//test
	printf("cmad_args %s\n cq_flag %d\n", node->content, cq_node->quote_flag);
	//
}
