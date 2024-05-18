/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:08:48 by bcai              #+#    #+#             */
/*   Updated: 2024/05/18 21:22:52 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig, siginfo_t *siginfo, void *context)
{
	(void)sig;
	(void)siginfo;
	(void)context;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	printf("\nminishell$ ");
}

void	handle_sigint_heredoc(int sig, siginfo_t *siginfo, void *context)
{
	(void)sig;
	(void)siginfo;
	(void)context;
	g_sig_indicator = 1;
}

void	signal_tracking(struct sigaction *sa, t_m *m)
{
	init_global_var();
	if (m->position == ON_MAIN)
	{
		sigemptyset(&(sa->sa_mask));
		sa->sa_flags = SA_SIGINFO;
		sa->sa_sigaction = handle_sigint;
		sigaction(SIGINT, sa, NULL);
		sigemptyset(&(sa->sa_mask));
		sa->sa_flags = 0;
		sa->sa_handler = SIG_IGN;
		sigaction(SIGQUIT, sa, NULL);
	}
	else if (m->position == ON_HEREDOC)
	{
		sigemptyset(&(sa->sa_mask));
		sa->sa_flags = SA_SIGINFO;
		sa->sa_sigaction = handle_sigint_heredoc;
		sigaction(SIGINT, sa, NULL);
		sigemptyset(&(sa->sa_mask));
		sa->sa_flags = 0;
		sa->sa_handler = SIG_IGN;
		sigaction(SIGQUIT, sa, NULL);
	}
}
