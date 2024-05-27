#include "../minishell.h"

// change eva
void	update_working_history(t_m *m)
{
	t_execcmd	*ecmd;
	char		**array;

	array = NULL;
	array = (char **)malloc(sizeof(char *) * 3);
	ecmd = execcmd_init();
	if (does_file_history_exists() == 0)
	{
		array[0] = ft_strdup("touch");
		array[1] = ft_strdup("history.txt");
		array[2] = NULL;
		ecmd->cmd_args = array;
		execute_simple_command(ecmd, m);
	}
	else
		load_history(m);
}

void	load_history(t_m *m)
{
	int		fd;
	char	*line;

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
		m->prev_history = ft_strjoin(m->prev_history, line);
		line = remove_line_break(line);
		add_history(line);
		free(line);
		line = NULL;
	}
	close(fd);
}

char	*remove_line_break(char *line)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!new)
		return (NULL);
	while (line[i] != '\n')
	{
		new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	does_file_history_exists(void)
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

void	update_history_list(t_m *m)
{
	if (m->history[0] == '\0' || m->initial_history_check == 0)
	{
		m->initial_history_check = 1;
		m->history = ft_strjoin(m->history, m->input);
	}
	else if (m->input != NULL)
	{

		m->history = ft_strjoin(m->history, "\n");
		m->history = ft_strjoin(m->history, m->input);
	}
}

void	update_history_file(t_m *m)
{
	char	*first;

	first = ft_strdup("echo \"");
	m->history = ft_strjoin(m->prev_history, m->history);
	m->history = ft_strjoin(first, m->history);
	m->history = ft_strjoin(m->history, "\" > history.txt");
	m->final_tree = parsecmd(m->history);
	if (m->final_tree != NULL)
	{
		last_set(m->final_tree, m);
		runcmd(m->final_tree, m);
	}
}
