/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:52:32 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/07 18:25:11 by llalba           ###   ########.fr       */
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
# include "multipipe.h"

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
	int		len_line;
	int		in; // no < = 0 , < = 1 , << = 2
	int		out; // no > = 0 , > = 1 , >> = 2
	char	*infile_name; //nom du infile . e.g  test < cat -e    --> infile = test
	char	*outfile_name;//       outfile        cat -e > test   --> outfile = test
	char	*infile; // permet de recup le fd de l ouverture du infile
	char	*outfile; // 										outfile
	//t_pipe	*pipe;
	t_cmd	*l_cmd;
}		t_data;

// struct pour le pipe

typedef struct s_pipe
{
	char	**cmd; // commande a parser avec la fonction parse_cmd
	char	**path; //split du path
	int		**end;
	int		i;  // ??
	int		argc;
}		t_pipe;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}		t_env;

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

// +------------------------------------------+ //
//   Parsing                                    //
// +------------------------------------------+ //

// +------------------------------------------+ //
//   Environnement                               //
// +------------------------------------------+ //

void	init_env(void);

#endif