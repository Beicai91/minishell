/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:05:12 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/06/05 23:01:13 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_blocktype(char **start)
{
	int	type;

	type = **start;
	(*start)++;
	return (type);
}
