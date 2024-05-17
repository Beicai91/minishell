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

	execcmd = (t_execcmd *)cmd;
	execcmd->m = m;
	if (m->heredoc_flag == 1 && execcmd->cmdargs == NULL)
	{
		execcmd->cmd_args = safe_malloc(2, STRING_ARRAY, m->final_tree);
		execcmd->cmd_args[0] = ft_strdup("cat");
		execcmd->cmd_args[1] = NULL;
		return ;
	}
	i = 0;
	while (execcmd->cmd_args && execcmd->cmd_args[i] != NULL
		&& execcmd->single_quote == 0)
	{
		temp = replace_d(execcmd, i);
		execcmd->cmd_args[i] = temp;
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

void	check_name_equal_value(char **temp, int *stop_flag)
{
	char		*tmp;
	int			i;
	char		*name;
	t_envvar	*env_vars;
	int			exist_flag;

	exist_flag = 0;
	tmp = *temp;
	i = 0;
	while (tmp[i + 1] != ' ' && tmp[i + 1] != '$' && tmp[i + 1] != '\0')
		i++;
	name = ft_substr(tmp + 1, 0, i);
	env_vars = getter();
	while (env_vars != NULL)
	{
		if (ft_strcmp(env_vars->value, name) == 0)
			exist_flag = 1;
		env_vars = env_vars->next;
	}
	free(name);
	if (exist_flag == 1)
		*temp = *temp + i + 1;
	else
		*stop_flag = 1;
}
