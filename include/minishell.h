/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:52:32 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/25 14:18:55 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// +------------------------------------------+ //
//   System header files                        //
// +------------------------------------------+ //

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
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
# define FILE_NOT_FOUND		"no such file or directory"
# define FAILED_TO_CLOSE	"failed to close one or more file descriptor(s)"
# define GNL_ERROR			"failed to malloc or to read standard input"
# define HEREDOC_EOF		"Warning: here-document delimited by EOF.\n"
# define CMD_NOT_FOUND		": command not found\n"
# define BUFFER_SIZE 		254
# define EMOJI_OK			"\033[32m[\xE2\x9C\x94]\033[0m "
# define EMOJI_X			"\033[31m[\xE2\x9C\x96]\033[0m "
# define ONE_RIGHT			1
# define TWO_RIGHT			2
# define ONE_LEFT			3
# define TWO_LEFT			4
# define HEREDOC_CONTINUE	0
# define HEREDOC_END		1

// +------------------------------------------+ //
//   Utils                                      //
// +------------------------------------------+ //
int		gnl_result(int ret, char **line, char **save);//CHECKED
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
int		check_equal_sign(char *str);
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
short	ft_cd(t_data *data, char **cmd);
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
void	free_data(t_data *data);//CHECKED
void	free_everything(t_data *data, char *str);//CHECKED
void	delete_one_env_var(t_env *env);//CHECKED
void	ft_lstclear_env(t_env *lst);//CHECKED
void	free_pipe(t_data *data, t_pipe *pipe);
// +------------------------------------------+ //
//   Echo                                       //
// +------------------------------------------+ //
void	ft_echo(t_data *data, char **cmd);
int		echo_argument_n(char *str);
// +------------------------------------------+ //
//   Error                                      //
// +------------------------------------------+ //
void	ft_error(char *str);//CHECKED
void	err_free(char *msg, t_data *data, char *str);//CHECKED
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
void	load_heredoc(t_data *data);//CHECKED
short	parse_cmd(t_data *data);//CHECKED
short	parse_cmd_content(t_data *data, t_cmd *head);//CHECKED
short	open_file(t_cmd *head, char *file, short opening);//CHECKED
// +------------------------------------------+ //
//   Environnement                              //
// +------------------------------------------+ //
void			delete_one_env_var(t_env *lst);//CHECKED
void			ft_lstclear_env(t_env *head);//CHECKED
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
void	find_command_path(t_data *data, t_cmd *head);
//void	error_var_name(t_data *data, t_cmd *new, char *cmd_line);
int		init_pipe(int nb_pipe, t_data *data, t_pipe *pipes);
int		init_pipe_struct(t_data *data);
int		len_before_redirection(t_cmd *cmd);
void	fork_creation(t_pipe *pipe, t_data *data);
void	command_failed(t_data *data, t_pipe *pipe, t_cmd *cmd);
// +------------------------------------------+ //
//   Multipipe Process                          //
// +------------------------------------------+ //
void	first_process(t_data *data, t_pipe *pipe, t_cmd *cmd);
void	middle_process(t_data *data, t_pipe *pipe, t_cmd *cmd);
void	last_process(t_data *data, t_pipe *pipe, t_cmd *cmd);
// +------------------------------------------+ //
//   Close_FD                                   //
// +------------------------------------------+ //
void		close_all_fd(t_pipe *pipe);
void		close_fd_first_process(t_pipe *pipe);
void		close_fd_middle_process(t_pipe *pipe);
void		close_fd_last_process(t_pipe *pipe);
// +------------------------------------------+ //
//   Dup                                   //
// +------------------------------------------+ //
void	open_infile_and_heredoc(t_cmd *cmd);
void		up_outfile(t_cmd *cmd, t_pipe *pipe);
// +------------------------------------------+ //
//   Fonction list CMD                          //
// +--------------------------------a----------+ //
void			cmd_add_back(t_cmd **alst, t_cmd *new);//CHECKED
t_cmd			*ft_lstnew_cmd(char *raw);//CHECKED
void			ft_lstclear_cmd(t_cmd *head);//CHECKED
int				ft_lstsize(t_cmd *lst);//CHECKED

#endif
