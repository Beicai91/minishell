/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:04:02 by bcai              #+#    #+#             */
/*   Updated: 2024/05/27 16:14:33 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_m					m;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	initial_setup(&m, envp);
	while (1)
	{
		signal_tracking(&sa, &m);
		m.input = readline("minishell$ ");

		if (!m.input)
			exit(1);
		add_history(m.input);
		//update_history_file(&m);
		m.input = expand_input_check(m.input, &m);
		partial_reinit_m(&m);
		m.final_tree = parsecmd(m.input);
		if (m.final_tree != NULL)
		{
			last_set(m.final_tree, &m);
			runcmd(m.final_tree, &m);
		}
		free(m.input);
	}
}
