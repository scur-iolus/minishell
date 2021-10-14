/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:59:45 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/14 19:01:41 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	remove_quotation_marks(char **line)
{
	char	*ptr;
	char	**line_split;
	char	**tmp;
	size_t	i;

	// si **line est '\0' alors return ; sans rien faire d'autre
	// remplacer " entre ' ' par des ;
	line_split = ft_split(*line, '"');
	// penser à sécuriser ça (malloc)
	free(*line);
	tmp = line_split;
	i = 1;
	while (line_split[0] && line_split[i])
	{
		ptr = ft_strjoin(line_split[0], line_split[i]);
		// penser à sécuriser ça (malloc)
		free(line_split[0]);
		free(line_split[i]);
		line_split[0] = ptr;
		line_split[i] = line_split[i + 1];
		i++;
	}
	ptr = line_split[0];
	free(tmp);
	*line = ptr;
	// remplacer ; par des "
}

/*
=> supprimer les guillemets doubles (et ne pas toucher les char entre les guillemets)
Cas de figure a tester :
- pas de guillemets
- nombre pairs de guillemets
- nombre impairs de guillemets
- bcp de guillemets
- guillemets doubles entre guillemets simples

- remplir parsing.c pour decharger main()
- $$ $?
- exit n avec la fonction deja dispo
*/

static void	check_bad_characters(char *line)
{
	size_t	i;
	short	is_even;

	i = 0;
	is_even = 1;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			is_even = !is_even;
		else if (line[i] == '\\' || line[i] == ';')
			exit(1); // free tout ce qui doit etre free dans une fonction ft_error
		i++;
	}
	if (!is_even)
		exit(1); // nombre impairs de " ou de ' : free tout ce qui doit etre free dans une fonction ft_error
}


static void	remove_comment(char **line)
{
	size_t	len;
	char	*output;
	short	btwn_apo;

	len = 0;
	btwn_apo = 0;
	while ((*line)[len] && ((*line)[0] != '#'))
	{
		if ((*line)[len] == '\'')
			btwn_apo = !btwn_apo;
		if (len && (*line)[len] == '#' && (*line)[len - 1] == ' ' && !btwn_apo)
		{
			len--;
			break ;
		}
		len++;
	}
	output = calloc(len + 1, sizeof(char));
	while (len)
	{
		output[len - 1] = (*line)[len - 1];
		len--;
	}
	free(*line);
	(*line) = output;
}

void	init_data(t_data *data)
{
	data->len_line = 0;
	data->exit_status = 0;
	//free -----> data->pipe = ;
	//free -----> l_cmd = ;
}

void	reset_data(t_data *data)
{
	init_data(data);
	//free -----> data->pipe = ;
	//free -----> l_cmd = ;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*tmp;
	t_data	data;

	(void)argv;

	while (argc == 1)
	{
		init_data(&data);
		line = readline("Mishell c'est le Brésil>");
		if (ft_strlen(line) > 0)
			add_history(line);
		if (ft_strlen(line) > 0 && ft_strchr(line, (int) '#'))
			remove_comment(&line);
		check_bad_characters(line);
		tmp = line;
		line = ft_strtrim(line, " 	");
		free(tmp);
		data.env_lst = init_env(env);
		line = convert_env_var(&data, line);
		remove_quotation_marks(&line);
		printf("line vaut === %s$\n", line);

		/*
		if(!ft_strcmp("pwd", line))
			ft_pwd(&data);
		if(!ft_strcmp("env", line))
			ft_env(&data);
		*/

		//multipipe(structure principale);
		//fonction qui free tout avant la prochaine ligne de commande
		free(line);
		line = NULL;
		// l'exit(0) ne peut se faire que si l'utilisateur tape exit
	}
	printf("ERROR: no argument is required.\n");
	return (1);
}
