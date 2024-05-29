/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_set2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:08:01 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/05/17 13:28:22 by eprzybyl         ###   ########.fr       */
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
	execcmd->m = m;
	if (m->heredoc_flag == 1 && execcmd->cmdargs == NULL)
		return ;
	i = 0;
	qflag = ((t_execcmd *)cmd)->qflags;
	while (execcmd->cmd_args && execcmd->cmd_args[i] != NULL)
	{
		//test
		printf("in last_set, cmd_args %s\nqflag %d\n", execcmd->cmd_args[i], qflag->quote_flag);
		//
		if (qflag->quote_flag == 0 || qflag->quote_flag == 34)
		{
			temp = replace_d(execcmd, i);
			execcmd->cmd_args[i] = temp;
		}
		qflag = qflag->next;
		i++;
	}
}

char	*get_newstr2(char *temp, char *e_cpy, t_execcmd *ecmd, char *first_part)
{
	t_strvars	v;

	if (*(temp + 1) == '?')
	{
		v.var_value = ft_itoa(ecmd->m->exit_status);
		v.new = minishell_strjoin(first_part, v.var_value, NULL);
		free(v.var_value);
		v.rest = m_sub(temp + 2, 0, e_cpy - temp - 1, NULL);
	}
	else
	{
		get_strlen(temp, &(v.i));
		v.var_value = getvalue_freename(ecmd->cmdargs, ft_substr(temp, 1, v.i));
		v.new = minishell_strjoin(first_part, v.var_value, NULL);
		if (*(v.var_value) == '\0')
			free(v.var_value);
		if (!*temp)
			v.rest = strdup("");
		else
			v.rest = m_sub(temp + v.i + 1, 0, e_cpy - temp - v.i, NULL);
	}
	free(first_part);
	v.new = join_free_all(v.new, v.rest, NULL);
	return (v.new);
}
