/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:42:05 by llalba            #+#    #+#             */
/*   Updated: 2021/11/24 11:08:17 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

// /*
// ** Structure s_pipe
// ** path -> split du path
// ** end -> les differents fd ouverts pour le multipipe
// ** infile -> permet de recup le fd de l ouverture du infile
// ** outfile -> permet de recup le fd de l ouverture du outfile
// */

typedef struct s_pipe
{
	int		**end;
	int		nb_pipe;
	int		cmd_nb;
	int		cmd_len;
	int		i; // pour savoir ou on en est dans les pipes
}	t_pipe;

typedef struct s_env
{
	int				is_env;
	int				equal_sign;
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char			**env;
	char			**path;
	char			*line;
	long long		exit_status;
	struct s_cmd	*cmd;
	struct s_pipe	pipe;
	struct s_env	*env_lst;
}	t_data;

/*
** Structure s_cmd : une s_cmd par 'pipe'
** cmd
** -> ["cat", "-e", "<", "infile", "poil.txt", "<", "3"]
** -> ["cat", "-e", "poil.txt"]
** cmd_path -> /usr/bin/head ou autre du PATH
*/

typedef struct s_cmd
{
	char				*raw;
	char				**split;
	int					infile;
	int					outfile;
	char				*heredoc;
	char				**cmd;
	char				*cmd_path;
	struct s_cmd		*next;
}	t_cmd;

t_cmd		*ft_lstnew_cmd(char *raw);
void		cmd_add_back(t_cmd **alst, t_cmd *new);
void		ft_lstclear_cmd(t_cmd *lst);

#endif
