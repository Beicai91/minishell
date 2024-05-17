/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:54:03 by bcai              #+#    #+#             */
/*   Updated: 2024/05/17 13:14:52 by eprzybyl         ###   ########.fr       */
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

void	populate_cmdargs(t_list **cmdargs, char *s_token, char *e_token,
		t_cmd *cmd)
{
	t_list	*node;

	node = (t_list *)safe_malloc(1, NODE, cmd);
	node->next = NULL;
	node->content = safe_malloc(e_token - s_token + 1, CHAR, cmd);
	ft_strlcpy(node->content, s_token, e_token - s_token + 1);
	ft_lstadd_back(cmdargs, node);
}

void	populate_cmdargs_singlequote(t_list **cmdargs, char *s_token,
		char *e_token, t_cmd *cmd)
{
	t_list	*node;

	node = (t_list *)safe_malloc(1, NODE, cmd);
	node->content = safe_malloc(e_token - s_token + 2, CHAR, cmd);
	ft_strlcpy(node->content, s_token, e_token - s_token + 2);
	node->next = NULL;
	ft_lstadd_back(cmdargs, node);
}

void	single_quoted_args(t_list **cmdargs, t_execcmd *ecmd, char **start,
		t_cmd *cmd)
{
	char	*s_token;
	char	*e_token;

	ecmd->single_quote = 1;
	s_token = *start + 1;
	printf("entering single quoted args\n");
	(*start)++;
	while (**start && **start != 39)
		(*start)++;
	if (!**start)
		handle_error("Missing closing quote", cmd);
	else
	{
		e_token = *start - 1;
		(*start)++;
		populate_cmdargs_singlequote(cmdargs, s_token, e_token, cmd);
	}
}

void	cmdargs_dquote(t_list **cmdargs, char *s_token,
		char *e_token, char **start)
{
	t_list	*node;

	node = (t_list *)safe_malloc(1, NODE, NULL);
	node->content = safe_malloc(e_token - s_token + 2, CHAR, NULL);
	ft_strlcpy(node->content, s_token, e_token - s_token + 2);
	node->next = NULL;
	ft_lstadd_back(cmdargs, node);
	(*start)++;
}
