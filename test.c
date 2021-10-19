/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:16:23 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/15 14:58:37 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


int main(int argc, char **argv)
{
	(void)argc;

	char line[PATH_MAX];

	getcwd(line, PATH_MAX);

	printf("%s\n", line);

	chdir(argv[1]);
	perror("ERROR :");

	//open("poil", O_CREAT | O_RDWR | O_TRUNC, 0644);

	return(0);
}
