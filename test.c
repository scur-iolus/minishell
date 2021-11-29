/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:06:57 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/26 16:15:44 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


int main()
{
	char line[PATH_MAX];
	int i;

	getcwd(line, PATH_MAX);
	printf("OLD DIR ==> %s\n",line);
	i = chdir("../..");
	printf("RET = %d\n", i);
	getcwd(line, PATH_MAX);
	printf("NEW DIR ==> %s\n",line);
}
