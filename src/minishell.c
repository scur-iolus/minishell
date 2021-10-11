/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:59:45 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/11 17:07:24 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_comment(char *line)
{
	size_t	new_len;
	size_t	i;
	char	*output;

	new_len = 0;
	while (line[new_len] && line[new_len] != '#')
		new_len++;
	output = calloc(new_len + 1, sizeof(char));
	i = 0;
	while (i < new_len)
	{
		output[i] = line[i];
		i++;
	}
	free(line);
	line = output;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_env	*env_lst;
	t_data	data;

	(void)argv;
	while (argc == 1)
	{

		line = readline("Mishell c'est le Brésil>");
		if (ft_strlen(line) > 0)
			add_history(line);
		if (ft_strlen(line) > 0 && ft_strchr(line, (int) '#'))
			remove_comment(line);
		data.env_lst = init_env(env);

// test lecture de la liste chainee, on checke qu'on a bien tout
t_env	*tmp = data.env_lst;
while (tmp)
{
	printf("%s  ===  %s\n", tmp->var, tmp->value);
	tmp = tmp->next;
}
printf("\n\n\n\n");
// test ecriture de la liste chainee dans un char **
char	**test;
test = list_to_env(data.env_lst);
int i = 0;
while(test[i])
{
	printf("%s\n", test[i]);
	i++;
}

		// fonction de parsing

		// fonction qui fait la ou les commandes
		printf("line read --> %s\n", line);

		//multipipe(structure principale);
		//fonction qui free tout avant la prochaine ligne de commande
		free(line);
		line = NULL;
		// l'exit(0) ne peut se faire que si l'utilisateur tape exit
	}
	printf("ERROR: no argument is required.\n");
	return (1);
}
