/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:52:32 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/19 18:22:21 by fmonbeig         ###   ########.fr       */
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
//   Libft & other custom headers               //
// +------------------------------------------+ //

# include "../libft/libft.h"
# include "structures.h"

// +------------------------------------------+ //
//   Define                                     //
// +------------------------------------------+ //

# define MALLOC_ERROR		"malloc failed"
# define INVALID_CHAR_ERR	"invalid characters in your command"
# define ODD_NB_APOSTROPHES	"odd number of \' or \""
# define END_CHAR_ERR		"invalid char at the end of your command"
# define START_CHAR_ERR		"invalid char at the beginning of your command"
# define TOO_MANY_ARG		"minishell does not accept any argument"
# define LINE_TOO_LONG		"this command is too long, please try to split it"
# define INVALID_STATUS		"this exit status is not an int"
# define BUFFER_SIZE 		25
# define EMOJI_OK			"\033[32m[\xE2\x9C\x94]\033[0m "
# define EMOJI_X			"\033[31m[\xE2\x9C\x96]\033[0m "

// +------------------------------------------+ //
//   Utils                                      //
// +------------------------------------------+ //

// +------------------------------------------+ //
//   Builtins                                   //
// +------------------------------------------+ //
int		ft_pwd(t_data *data);
void	ft_exit(t_data *data, char *str, char **split, long long exit_status);
// +------------------------------------------+ //
//   Export                                     //
// +------------------------------------------+ //
int		ft_export(t_data *data, char **cmd);
void	put_in_env_export(t_data *data, char **cmd, int i);
int		check_is_env(char *line);
int		error_var_name(char *line);
void	print_export(t_data *data);
void	print_env_with_export_layout(t_data *data);
// +------------------------------------------+ //
//   Env                                     //
// +------------------------------------------+ //
int		ft_env(t_data *data, char **cmd);
int		check_argument_ft_env(char **cmd);
// +------------------------------------------+ //
//   Cd                                     //
// +------------------------------------------+ //
void	ft_cd(t_data *data, char **cmd);
int		error_ft_cd(char **cmd);
short	switch_old_pwd(t_data *data, char * line);
short	switch_pwd(t_data *data, char * line, char *temp);
// +------------------------------------------+ //
//   Unset                                     //
// +------------------------------------------+ //
int				ft_unset(t_data *data, char **cmd);
static t_env	*find_previous_var_env(t_data *data, char *var_name);
void			pop_out_list_env(t_data *data, char *line);

// +------------------------------------------+ //
//   Free                                       //
// +------------------------------------------+ //
void	reset_data(t_data *data);
void	ft_lstclear_pipe(t_pipe *this, t_data *data);//CHECKED
void	free_data(t_data *data);//CHECKED
void	delete_one_env_var(t_env *env);//CHECKED
void	ft_lstclear_env(t_env *lst);//CHECKED
// +------------------------------------------+ //
//   Echo                                       //
// +------------------------------------------+ //
void	ft_echo(t_data *data, char **cmd);
int		echo_argument_n(char *str);
// +------------------------------------------+ //
//   Error                                      //
// +------------------------------------------+ //
void	ft_error(char *str);//CHECKED
void	err_free(char *msg, t_data *data, char *str, char **split);//CHECKED
// +------------------------------------------+ //
//   Input checks                               //
// +------------------------------------------+ //
void	remove_comment(t_data *data);//CHECKED
short	even_nb_of_quote_marks(char *line);//CHECKED
void	remove_quotation_marks(t_data *data);//CHECKED
void	deduplicate_spaces(t_data *data);//CHECKED
void	space_before_after_chevron(t_data *data);//CHECKED
short	too_many_chevrons_o_pipes(t_data *data);//CHECKED
short	invalid_suite(t_data *data);//CHECKED
short	file_not_found(char *line);
short	valid_start_end(char *line);
// +------------------------------------------+ //
//   Parsing                                    //
// +------------------------------------------+ //
void	parse_cmd_list(t_data *data);//CHECKED
// +------------------------------------------+ //
//   Environnement                               //
// +------------------------------------------+ //
t_env	*init_env(t_data *data, char **env);//CHECKED
t_env	*ft_lstnew_env(void);//CHECKED
char	*get_var_name(t_data *data, char *str);//CHECKED
char	*get_var_value(t_data *data, char *str);//CHECKED
char	*convert_env_var(t_data *data);//CHECKED
short	special_cases(t_data *data, char **output, size_t *pos);//CHECKED
t_env	*find_var_env(t_data *data, char *var_name);//CHECKED
void	env_add_front(t_env **head, t_env *new);//CHECKED
char	**list_to_env(t_env *env_lst);

// +------------------------------------------+ //
//   Execute                                  //
// +------------------------------------------+ //
void	execute(t_data *data);
int		is_built_in(t_data *data);
void	make_one_cmd(t_data *data);
void	make_one_built_in(t_data *data);
// +------------------------------------------+ //
//   Multipipe                                  //
// +------------------------------------------+ //
void	take_path(t_data *data);
void	parse_cmd(t_data *data, char *cmd_line);
//void	error_var_name(t_data *data, t_cmd *new, char *cmd_line);
// +------------------------------------------+ //
//   Fonction list CMD                          //
// +------------------------------------------+ //
static t_cmd	*ft_lstlast(t_cmd *lst);//CHECKED
void			cmd_add_back(t_cmd **alst, t_cmd *new);//CHECKED
t_cmd			*ft_lstnew_cmd(char *raw);//CHECKED
void			ft_lstclear_cmd(t_cmd *head);//CHECKED
int				ft_lstsize(t_cmd *lst);//CHECKED
// +------------------------------------------+ //
//   Fonction list CMD                          //
// +------------------------------------------+ //
t_env			*find_var_env(t_data *data, char *var_name);//CHECKED
void			env_add_front(t_env **head, t_env *new);//CHECKED
t_env			*ft_lstnew_env(void);//CHECKED
void			delete_one_env_var(t_env *lst);//CHECKED
void			ft_lstclear_env(t_env *head);//CHECKED

#endif



