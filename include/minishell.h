/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:52:32 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/10/15 18:15:31 by fmonbeig         ###   ########.fr       */
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
# include <linux/limits.h>

// +------------------------------------------+ //
//   Libft                                      //
// +------------------------------------------+ //
# include "../libft/libft.h"
// +------------------------------------------+ //
//   Define                                     //
// +------------------------------------------+ //

# define BUFFER_SIZE 25

// +------------------------------------------+ //
//   Type definition                            //
// +------------------------------------------+ //


// struct pour le pipe

typedef struct s_pipe // retravailler la structure pour le parsing
{
	char	**path; //split du path
	int		**end;
	char	*infile; // permet de recup le fd de l ouverture du infile
	char	*outfile; // 										outfile
	int		i;
	int		argc;
}		t_pipe;

typedef struct s_env
{
	int				is_env;
	char			*var;
	char			*value;
	struct s_env	*next;
}		t_env;

// Idee de struct principale
typedef struct s_data
{
	int		len_line;
	int		exit_status;
	t_pipe	*pipe;
	t_cmd	*l_cmd;
	t_env	*env_lst;
}		t_data;

// +------------------------------------------+ //
//   Main                                       //
// +------------------------------------------+ //
void	remove_comment(char *line);
void	reset_data(t_data *data);
// +------------------------------------------+ //
//   Utils                                      //
// +------------------------------------------+ //

// +------------------------------------------+ //
//   Builtins                                   //
// +------------------------------------------+ //
void	ft_pwd(t_data *data);
void	ft_env(t_data *data);
void	ft_exit(t_data *data);
// +------------------------------------------+ //
//   Export                                     //
// +------------------------------------------+ //
void	ft_export(t_data *data, char *line);
int		check_is_env(char *line);
int		error_var_name(char *line);
void	print_export(t_data *data);
void	print_env_with_export_layout(t_data *data);
// +------------------------------------------+ //
//   Free                                       //
// +------------------------------------------+ //
void	free_all(t_data *data, int exit_value);
void	delete_one_env_list(t_env *env);
void	ft_lstclear_env(t_env *lst);

// +------------------------------------------+ //
//   Echo                                       //
// +------------------------------------------+ //
void	ft_echo(t_data *data, char *line);
// +------------------------------------------+ //
//   Error                                      //
// +------------------------------------------+ //

// +------------------------------------------+ //
//   Parsing                                    //
// +------------------------------------------+ //

// +------------------------------------------+ //
//   Environnement                               //
// +------------------------------------------+ //

void	env_add_front(t_env **head, t_env *new);
t_env	*init_env(char **env);
char	**list_to_env(t_env *env_lst);
t_env	*find_var_env(t_data *data, char *var_name);
char	*get_var_name(char *str);
char	*get_var_value(char *str);

// +------------------------------------------+ //
//   Multipipe                                  //
// +------------------------------------------+ //
void	take_path(t_data *data);
void	parse_cmd(t_data *data, char *cmd_line);

#endif
