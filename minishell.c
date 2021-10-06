/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:59:45 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/06 15:46:03 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int argc, char **argv, char **env)
{
    char *line;
    (void)argv;
    (void)env;
    if (argc == 1)
    {
        while (1)
        {
            line = readline("Mishell>");
            if  (ft_strlen(line) > 0)
                add_history(line);

            // fonction de parsing

            
            // fonction qui fait la ou les commandes    
            printf("line read --> %s\n", line);

            //fonction qui free tout avant le prochaine ligne de commande
            free(line);
            line = NULL;
        }
        return (0);
    }
    printf("ERROR : no argument is required");
    return (1);       
}