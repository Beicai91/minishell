/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:53:14 by bcai              #+#    #+#             */
/*   Updated: 2024/06/05 23:02:24 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getvalue_freename(char *var_name)
{
	char	*var_value;

	var_value = get_current_envvar(var_name);
	free(var_name);
	return (var_value);
}

char	*get_current_envvar(char *key)
{
	t_envvar	*target;
	char		*value;

	value = NULL;
	target = get_envvar(key);
	if (!target)
		value = ft_strdup("");
	else
		value = target->value;
	return (value);
}

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
	int		i;
	int		j;
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
	while (i - j > 0)
	{
		add_flagnode(&(ecmd->qflags));
		add_flagnode(&(ecmd->cqflags));
		i--;
	}
}
