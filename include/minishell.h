/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:52:32 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/07 18:00:06 by fmonbeig         ###   ########.fr       */
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
	t_pipe	*pipe;
	t_cmd	*l_cmd;
}		t_data;

// struct pour le pipe

typedef struct s_pipe
{
	char	**path; //split du path
	int		**end;
	char	*infile; // permet de recup le fd de l ouverture du infile
	char	*outfile; // 										outfile
	int		i;
	int		argc;
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

