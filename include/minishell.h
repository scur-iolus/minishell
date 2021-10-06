/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:52:32 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/06 17:48:05 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// +------------------------------------------+ //
//   System header files                        //
// +------------------------------------------+ //

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// +------------------------------------------+ //
//   Libft                                      //
// +------------------------------------------+ //

# include "../libft/libft.h"

// +------------------------------------------+ //
//   Define                                     //
// +------------------------------------------+ //

//////////

// +------------------------------------------+ //
//   Type definition                            //
// +------------------------------------------+ //

// Idee de struct principale
typedef struct s_data
{
    int     len_line;
    int     in; // no < = 0 , < = 1 , << = 2
    int     out; // no > = 0 , > = 1 , >> = 2
    char    *infile; //nom du infile . e.g  test < cat -e    --> infile = test
    char    *outfile;//       outfile        cat -e > test   --> outfile = test
    t_pipe  *pipe;
}       t_data;

// struct pour le pipe

typedef struct s_pipe
{
	char	**cmd; // commande a parser avec la fonction parse_cmd
	char	**path; //split du path
	int		**end;
	int		i;
	int		argc;
	int		infile;
	int		outfile;
	t_list	*list;  // ==> nom de liste chaînée a changer ??
}		t_pipe;

// +------------------------------------------+ //
//   Main                                       //
// +------------------------------------------+ //

// +------------------------------------------+ //
//   Utils                                      //
// +------------------------------------------+ //

// +------------------------------------------+ //
//   Free                                       //
// +------------------------------------------+ //

// +------------------------------------------+ //
//   Error                                      //
// +------------------------------------------+ //


#endif

