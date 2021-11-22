#include "../include/minishell.h"

static short	continue_reading(int *ret, char **save)//CHECKED
{
	char	buff[BUFFER_SIZE + 1];

	*ret = read(0, buff, BUFFER_SIZE);
	if (*ret == -1)
		return (0);
	buff[*ret] = '\0';
	if (!(*save))
		*save = ft_strdup(buff);
	else
		ft_str_insert(save, buff, ft_strlen(*save));
	if (!(*save))
		return (0);
	return (1);
}

/*
** Customized GNL with free(line) when ret == 0, and a flag to free(save)
*/

static int	get_next_line(char **line, short flag)//CHECKED
{
	static char	*save = 0;
	int			ret;

	if (flag)
	{
		if (save)
			free(save);
		save = 0;
		return (42);
	}
	if (!line || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (-1);
	ret = 1;
	while (!contains_new_line(save) && ret > 0)
	{
		if (!continue_reading(&ret, &save))
			return (-1);
	}
	return (gnl_result(ret, line, &save));
}

static void	heredoc_input(char **to_fill, char *heredoc_delimiter)//CHECKED
{
	char	*line;
	int		status;

	line = 0;
	*to_fill = (char *)ft_calloc(1, sizeof(char));
	if (!(*to_fill))
	{
		printf("Malloc error\n");
		fflush(stdout);
	}
	write(1, ">", 1);
	status = get_next_line(&line, HEREDOC_CONTINUE);
	while (status > 0 && ft_strcmp(heredoc_delimiter, line) != 0)
	{
		ft_str_insert(to_fill, line, ft_strlen(*to_fill));
		ft_str_insert(to_fill, "\n", ft_strlen(*to_fill));
		free(line);
		line = 0;
		write(1, ">", 1);
		status = get_next_line(&line, HEREDOC_CONTINUE);
	}
	(void)get_next_line(0, HEREDOC_END);
	if (line)
		free(line);
	if (status == -1)
	{
		printf("GNL error\n");
		fflush(stdout);
	}
	else if (status == 0)
		write(1, HEREDOC_EOF, ft_strlen(HEREDOC_EOF));
}

int	main(int argc, char **argv)
{
	char	*to_fill;

	(void)argc;
	to_fill = 0;
	if (argv[1] == 0)
	{
		printf("argv1 introuvable\n");
		return (1);
	}
	heredoc_input(&to_fill, argv[1]);
	printf("\n\n\n>>>%s<<<\n", to_fill);
	fflush(stdout);
	free(to_fill);
	to_fill = 0;
	return (0);
}
