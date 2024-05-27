#include "../minishell.h"

// change eva
void	update_working_history(t_m *m)
{
	t_execcmd	*ecmd;
	char		**array;
ecmd = NULL;
	array = NULL;

	if (does_file_history_exist() == 0)
	{
		array[0] = ft_strdup("touch");
		array[1] = ft_strdup("history.txt");
		array[2] = NULL;
		ecmd->cmd_args = array;
		free_2darray(array);
		execute_simple_command(ecmd, m);	
		free(ecmd);
		ecmd = NULL;
	}
	else
		load_history(m);
}

void	load_history(t_m *m)
{
	int		fd;
	char	*line;
	char	*new_line;

	(void)m;
	fd = open("history.txt", O_RDONLY);
	if (fd < 0 || fd > 4095)
	{
		printf("Error: failed to load the history file\n");
		return ;
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		new_line = remove_line_break(line);
		add_history(new_line);
		free(new_line);
		new_line = NULL;
	}
	close(fd);
}

char	*remove_line_break(char *line)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(line));//since we remove \n so the size we allocate should be the original_size - 1, so the length
	if (!new)
		return (NULL);
	while (line[i] != '\n')
	{
		new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	free(line);
	return (new);
}

int	does_file_history_exist(void)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
		return (2);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (pattern_match(entry->d_name, "history.txt"))
		{
			closedir(dir);
			return (1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

void	update_history_file(t_m *m)
{
	int	fd;

	fd = open("history.txt", O_RDWR | O_APPEND, 0666);
	write(fd, m->input, ft_strlen(m->input));
	write(fd, "\n", 1);
	close(fd);
}