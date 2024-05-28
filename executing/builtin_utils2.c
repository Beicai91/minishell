/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:00:39 by bcai              #+#    #+#             */
/*   Updated: 2024/05/22 10:04:28 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*join_three_parts(char *first_part, char *var_value, char *rest)
{
	char	*firstpart_varvalue;
	char	*value;

	firstpart_varvalue = ft_strjoin(first_part, var_value);
	value = ft_strjoin(firstpart_varvalue, rest);
	free(firstpart_varvalue);
	return (value);
}

static char	*get_newvalue(char *start, char *target, char *end)
{
	t_envvar	*envvar;
	int			i;
	t_strvars	strvars;

	strvars.first_part = ft_substr(start, 0, target - start);
	i = 0;
	while (target[i] && target[i] != ' ' && target[i] != '"' && target[i] != 39)
		i++;
	strvars.var_name = ft_substr(target + 1, 0, i - 1);
	envvar = get_envvar(strvars.var_name);
	strvars.rest = ft_substr(target + i, 0, end - target - i);
	if (envvar == NULL)
		strvars.new = ft_strjoin(strvars.first_part, strvars.rest);
	else
		strvars.new = join_three_parts(strvars.first_part, \
			envvar->value, strvars.rest);
	free(strvars.first_part);
	free(strvars.var_name);
	free(strvars.rest);
	return (strvars.new);
}

char	*expand_value(char *start, char *target)
{
	char	*value;
	char	*end;

	end = start + ft_strlen(start) - 1;
	while (*target && *(target + 1))
	{
		value = get_newvalue(start, target, end);
		target = value;
		while (*target && (*target != '$' || (*target == '$' && (*(target
							+ 1) == ' ' || *(target + 1) == '"'))))
			target++;
		start = value;
		end = value + ft_strlen(value) - 1;
	}
	return (value);
}

char	*handle_expansion(char *start, t_cmd *cmd, t_m *m)
{
	int		dollarsign;
	char	*temp;
	char	*value;
	char	*target;

	//test
	printf("Enter into handle_expansion\n");
	//
	dollarsign = 0;
	temp = start;
	target = NULL;
	//test
	printf("temp = firstletter %c\n", *temp);
	//
	while (*temp && *temp != '"')
	{
		if (*temp == '$' && *(temp + 1) != ' ' && *(temp + 1) != '"')
		{
			dollarsign = 1;
			target = temp;
			break ;
		}
		temp++;
	}
	if (!*temp)
		builtin_error(cmd, m, "Missing closing quote for env var value");
	if (dollarsign == 0)
		value = ft_substr(start, 0, ft_strlen(start) - 1);
	else
		value = expand_value(start, target);
	return (value);
}

char	*get_value(char *arg, char *quote_letter, t_cmd *cmd, t_m *m)
{
	char	*value;

	if (*(quote_letter) == '"')
		value = handle_expansion(quote_letter + 1, cmd, m);
	else if (*quote_letter == 39)
	{
		if (arg[ft_strlen(arg) - 1] != 39)
			builtin_error(cmd, m,
				"Missing closing quote for environment variable's value");
		value = ft_substr(quote_letter + 1, 0, ft_strlen(quote_letter + 1) - 1);
	}
	else
		value = ft_substr(quote_letter, 0, ft_strlen(quote_letter));
	return (value);
}
