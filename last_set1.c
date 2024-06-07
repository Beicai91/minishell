/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_set1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:57:24 by bcai              #+#    #+#             */
/*   Updated: 2024/06/05 23:02:53 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exec(t_cmd *cmd, t_m *m)
{
	t_execcmd	*execcmd;
	int			i;
	char		*temp;
	t_qflag		*qflag;

	execcmd = (t_execcmd *)cmd;
	if (m->heredoc_flag == 1 && execcmd->cmdargs == NULL)
		return ;
	i = 0;
	qflag = ((t_execcmd *)cmd)->qflags;
	while (execcmd->cmd_args && execcmd->cmd_args[i] != NULL)
	{
		if (qflag->quote_flag == 0 || qflag->quote_flag == 34)
		{
			temp = replace_dollar(execcmd->cmd_args[i], m);
			execcmd->cmd_args[i] = temp;
		}
		qflag = qflag->next;
		i++;
	}
}

void	parse_left_right(t_cmd *left, t_cmd *right, t_m *m)
{
	last_set(left, m);
	last_set(right, m);
}

void	set_redir(t_m *m, t_redircmd *rcmd)
{
	char	*new_filename;

	new_filename = replace_dollar(rcmd->file, m);
	free(rcmd->file);
	rcmd->file = NULL;
	rcmd->file = new_filename;
	last_set(rcmd->cmd, m);
}

void	last_set(t_cmd *cmd, t_m *m)
{
	int	type;

	if (cmd == NULL)
		return ;
	type = cmd->type;
	if (type == EXEC)
		set_exec(cmd, m);
	else if (type == REDIR)
		set_redir(m, (t_redircmd *)cmd);
	else if (type == HEREDOC)
	{
		m->heredoc_flag = 1;
		((t_heredoc *)cmd)->envp = m->envp;
		last_set((((t_heredoc *)cmd)->cmd), m);
	}
	else if (type == PIPE)
		parse_left_right(((t_pipecmd *)cmd)->left, ((t_pipecmd *)cmd)->right,
			m);
	else if (type == LIST)
		parse_left_right(((t_listcmd *)cmd)->left, ((t_listcmd *)cmd)->right,
			m);
	else if (type == AND)
		parse_left_right(((t_and *)cmd)->left, ((t_and *)cmd)->right, m);
	else if (type == OR)
		parse_left_right(((t_or *)cmd)->left, ((t_or *)cmd)->right, m);
}

void	get_strlen(char *temp, int *i)
{
	*i = 0;
	while (temp[*i] && temp[*i + 1] != 39 && temp[*i + 1] != '/' && temp[*i + 1] != ' ' && temp[*i
			+ 1] != '"' && temp[*i + 1] != '\0' && ft_strchr("!@#$%^", temp[*i
				+ 1]) == 0)
		(*i)++;
	//test
	printf("after updating, temp[i] %c\n", temp[*i]);
	//
}
