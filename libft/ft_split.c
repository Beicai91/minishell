/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:20:03 by bcai              #+#    #+#             */
/*   Updated: 2023/12/01 14:56:43 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static void	*ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return (NULL);
}

static int	count_strings(char const *s, char c)
{
	char	*p;
	int		count;

	p = (char *)s;
	count = 0;
	while (*p)
	{
		while (*p && *p == c)
			p++;
		if (*p)
			count++;
		while (*p && *p != c)
			p++;
	}
	return (count);
}

static int	get_len(char *s_moved, char c)
{
	int	len;

	len = 0;
	while (s_moved[len] && s_moved[len] != c)
		len++;
	return (len);
}

static char	*get_word(char *s_moved, char c)
{
	char	*word;
	int		len;

	len = get_len(s_moved, c);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s_moved, len + 1);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	char	*ps;
	int		i;

	ptr = malloc(sizeof(char *) * (count_strings(s, c) + 1));
	if (!ptr)
		return (NULL);
	ps = (char *)s;
	i = -1;
	while (*ps && count_strings(s, c) > 0)
	{
		while (*ps && *ps == c)
			ps++;
		if (*ps)
			ptr[++i] = get_word(ps, c);
		if (!ptr[i])
			return (ft_free(ptr));
		while (*ps && *ps != c)
			ps++;
	}
	ptr[i + 1] = NULL;
	return (ptr);
}
/*
int	main(int argc, char *argv[])
{
	(void)argc;

	char	**ptr;

	ptr = ft_split(argv[1], argv[2][0]);
	int	i;
	i = 0;
	while (ptr[i])
	{
		printf("%s\n", ptr[i]);
		i++;
	}
	free (ptr);
	return (0);
}*/
