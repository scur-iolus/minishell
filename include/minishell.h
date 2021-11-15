/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:52:32 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/15 18:49:58 by llalba           ###   ########.fr       */
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
# define BUFFER_SIZE 		25

// +------------------------------------------+ //
//   Utils                                      //
// +------------------------------------------+ //

// +------------------------------------------+ //
//   Builtins                                   //
// +------------------------------------------+ //
void	ft_pwd(t_data *data);
void	ft_env(t_data *data);
void	ft_exit(t_data *data, int n);
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
void	ft_lstclear_pipe(t_pipe *this);//CHECKED
void	free_data(t_data *data);//CHECKED
void	delete_one_env_var(t_env *env);//CHECKED
void	ft_lstclear_env(t_env *lst);//CHECKED
// +------------------------------------------+ //
//   Echo                                       //
// +------------------------------------------+ //
void	ft_echo(t_data *data, char *line);
// +------------------------------------------+ //
//   Error                                      //
// +------------------------------------------+ //
void	ft_error(char *str);//CHECKED
void	err_free(char *msg, t_data *data, char *str1, char *str2);//CHECKED
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
//   Multipipe                                  //
// +------------------------------------------+ //
void	take_path(t_data *data);
void	parse_cmd(t_data *data, char *cmd_line);
void	find_command_path(t_data *data, t_cmd *new, char *cmd_line);

#endif
