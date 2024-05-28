/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:53:14 by bcai              #+#    #+#             */
/*   Updated: 2024/05/24 16:37:07 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getvalue_freename(t_list *cmdargs, char *var_name)
{
	char	*var_value;

	(void)cmdargs;
	//if (ft_strncmp(cmdargs->content, "echo", 4) == 0)
		var_value = get_current_envvar(var_name);
	//else
		//var_value = get_exported_envvar(var_name);
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

char	*get_exported_envvar(char *key)
{
	t_envvar	*target;
	char		*value;

	value = NULL;
	target = get_envvar(key);
	if (!target)
		value = ft_strdup("");
	else if (target->is_exported == 0)
	{
		if (!*(target->value))
			value = target->value;
		else
			value = ft_strdup("");
	}
	else if (target->is_exported == 1)
		value = target->value;
	return (value);
}
