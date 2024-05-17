/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:01:30 by bcai              #+#    #+#             */
/*   Updated: 2023/11/02 12:34:44 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*join_free_multi(char *substorage, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(substorage, buffer);
	free(substorage);
	substorage = NULL;
	return (temp);
}

char	*read_store_check_multi(char *buffer, int fd, char *substorage)
{
	ssize_t	bytes_read;

	if (!substorage)
		substorage = ft_strdup("");
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(substorage);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (bytes_read == 0)
		{
			substorage = join_free_multi(substorage, buffer);
			break ;
		}
		substorage = join_free_multi(substorage, buffer);
		if (ft_strchr(substorage, '\n'))
			break ;
	}
	return (substorage);
}

char	*free_cut_multi(char *substorage, unsigned int index, size_t len)
{
	char	*temp;

	temp = ft_substr(substorage, index, len);
	free(substorage);
	(substorage) = NULL;
	return (temp);
}

char	*clear_line_multi(char **substorage)
{
	char	*temp;
	char	*line;

	if (*(*substorage) == '\0')
	{
		free(*substorage);
		*substorage = NULL;
		return (NULL);
	}
	temp = (*substorage);
	while (*temp)
	{
		if (*temp == '\n')
		{
			line = ft_substr((*substorage), 0, temp - (*substorage) + 1);
			(*substorage) = free_cut_multi(*substorage, temp - (*substorage)
					+ 1, ft_strlen(temp + 1));
			return (line);
		}
		temp++;
	}
	line = ft_substr((*substorage), 0, ft_strlen(*substorage));
	free(*substorage);
	*substorage = NULL;
	return (line);
}

char	*multi_gnl(int fd)
{
	static char	*storage[OPEN_MAX];
	char		*buffer;
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	else if (read(fd, 0, 0) < 0)
	{
		free(storage[fd]);
		storage[fd] = NULL;
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	storage[fd] = read_store_check_multi(buffer, fd, storage[fd]);
	line = clear_line_multi(&(storage[fd]));
	free(buffer);
	buffer = NULL;
	return (line);
}
