/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:31:57 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/05 23:06:28 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy_special(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	k;

	if (dstsize < 1)
		return (ft_strlen(src));
	i = 0;
	k = 0;
	while (src[k] && i < dstsize - 1)
	{
		if (src[k] == '\\')
			k++;
		dst[i] = src[k];
		i++;
		k++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

t_cmd	*parsepipe(char **start, char *end, t_m *m)
{
	t_cmd	*cmd;
	t_cmd	*right_cmd;

	cmd = parseexec(start, end, m);
	if (**start == '|' && *(*start + 1) != '|')
	{
		if (((t_execcmd *)cmd)->cmdargs == NULL)
		{
			printf("minishell: syntax error: unexpected token.\n");
			free_memory(cmd);
			return (NULL);
		}
		(*start)++;
		if (*start == end)
		{
			printf("minishell: syntax error: unexpected end of file.");
			free_memory(cmd);
			return (NULL);
		}
		right_cmd = parsepipe(start, end, m);
		cmd = (t_cmd *)pipecmd_init(cmd, right_cmd);
		if (right_cmd == NULL)
			return (NULL);
	}
	return (cmd);
}
