/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:36:53 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/05/19 13:25:09 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_gl	*init_global_var(void)
{
	static t_gl		*gl;
	struct termios	orig_termios;

	if (gl)
		return (gl);
	gl = (t_gl *)malloc(sizeof(t_gl));
	if (!gl)
		return (NULL);
	tcgetattr(STDIN_FILENO, &orig_termios);
	gl->orig_termios = orig_termios;
	gl->spaces = ft_strdup(" \t\r\n\v");
	gl->signs = ft_strdup("<|>;()");
	gl->env_vars = NULL;
	return (gl);
}

t_gl	*get_gl(void)
{
	static t_gl		*gl;

	if (!gl)
		gl = init_global_var();
	return (gl);
}
