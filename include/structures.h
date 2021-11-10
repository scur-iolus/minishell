/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:42:05 by llalba            #+#    #+#             */
/*   Updated: 2021/11/10 12:06:57 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/*
** Structure s_pipe
** path -> split du path
** end -> les differents fd ouverts pour le multipipe
** infile -> permet de recup le fd de l ouverture du infile
** outfile -> permet de recup le fd de l ouverture du outfile
*/

typedef struct s_pipe
{
	char	**path;
	int		**end;
	char	*infile;
	char	*outfile;
	int		i;
	int		argc;
}	t_pipe;

typedef struct s_env
{
	int				is_env;
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char			*line;
	long long		exit_status;
	struct s_pipe	*pipe;
	struct s_cmd	*cmd;
	struct s_env	*env_lst;
}	t_data;

/*
** Structure s_content : un noeud par fichier/texte
** La liste chainee qui en resulte est contenus dns un s_cmd
** str -> soit utilisée comme infile comme pour la commande "cat infile",
** soit comme une str classique pour "echo infile" par exemple.
** in -> no < = 0 , < = 1 , << = 2
** out -> no > = 0 , > = 1 , >> = 2
** pos -> position par rapport a la commande (0: avant, 1: apres la commande)
*/

typedef struct s_content
{
	char				*str;
	int					in;
	int					out;
	int					pos;
	struct s_content	*next;
}	t_content;

/*
** Structure s_cmd : une s_cmd par 'pipe'
** cmd -> ["cat", "-e"]
** cmd_path -> /usr/bin/head ou autre du PATH
*/

typedef struct s_cmd
{
	char				*raw;
	char				**cmd;
	char				*cmd_path;
	struct s_content	*content;
	struct s_cmd		*next;
}	t_cmd;

t_cmd	*ft_lstnew_cmd(char *raw);
void	ft_lstadd_back_cmd(t_cmd **alst, t_cmd *new);
void	ft_lstadd_front_cmd(t_cmd **alst, t_cmd *new);
int		ft_lstsize(t_cmd *lst);
t_cmd	*ft_lstlast(t_cmd *lst);
void	ft_lstclear_cmd(t_cmd *lst);

#endif