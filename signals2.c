/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:08:48 by bcai              #+#    #+#             */
/*   Updated: 2024/05/30 09:46:36 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig, siginfo_t *siginfo, void *context)
{
	(void)sig;
	(void)siginfo;
	(void)context;
	rl_replace_line("", 0);
	rl_redisplay();
	printf("\nminishell$ ");
}

void	handle_sigint_heredoc(int sig, siginfo_t *siginfo, void *context)
{
	(void)sig;
	(void)siginfo;
	(void)context;
	g_sig_indicator = 1;
	rl_done = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_exec(int sig, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	(void)sig;
	return ;
}

void	handle_sigquit_exec(int sig, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	(void)sig;
	return ;
}
