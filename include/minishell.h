/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:52:32 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/02 16:13:18 by llalba           ###   ########.fr       */
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
//   Unique global variable                     //
// +------------------------------------------+ //

extern long long	*g_exit_status;

// +------------------------------------------+ //
//   Define                                     //
// +------------------------------------------+ //

# define MALLOC_ERROR		"malloc failed"
# define INVALID_CHAR_ERR	"invalid characters in your command"
# define ODD_NB_APOSTROPHES	"odd number of \' or \""
# define END_CHAR_ERR		"invalid char at the end of your command"
# define START_CHAR_ERR		"invalid char at the beginning of your command"
# define TOO_MANY_ARG		"minishell does not accept any argument"
# define TOO_MANY_ARG2		"too many arguments"
# define HOME_NOT_SET		"HOME not set"
# define LINE_TOO_LONG		"this command is too long, please try to split it"
# define INVALID_STATUS		"this exit status is not an int"
# define INVALID_OPTION		"- invalid option"
# define FILE_NOT_FOUND		"no such file or directory"
# define FAILED_TO_CLOSE	"failed to close one or more file descriptor(s)"
# define GNL_ERROR			"failed to malloc or to read standard input"
# define HEREDOC_EOF		"Warning: here-document delimited by EOF.\n"
# define CMD_NOT_FOUND		": command not found\n"
# define SIGQUIT_MSG		"Quit (core dumped)"
# define NUMERIC_ARG		": numeric argument required"
# define EMOJI_OK			"\033[32m[\xE2\x9C\x94]\033[0m "
# define EMOJI_X			"\033[31m[\xE2\x9C\x96]\033[0m "
# define BUFFER_SIZE 		511
# define ONE_RIGHT			1
# define TWO_RIGHT			2
# define ONE_LEFT			3
# define TWO_LEFT			4
# define HEREDOC_CONTINUE	0
# define HEREDOC_END		1
# define TRUE				1
# define FALSE				0

// +------------------------------------------+ //
//   Utils                                      //
// +------------------------------------------+ //
void	signals_init(void);
int		gnl_result(int ret, char **line, char **save);
void	secure_between_apo(char *str, char c);
void	replace_semicolon(char *str, char c);
// +------------------------------------------+ //
//   Builtins                                   //
// +------------------------------------------+ //
int		ft_pwd(t_data *data, char **cmd);
void	ft_exit(t_data *data, char *str, char **split, long long exit_status);
void	ft_exit2(t_data *data, char **cmd); // FIXME j en ai fait un autre plus en adéquation avec les autre fonction
// +------------------------------------------+ //
//   Export                                     //
// +------------------------------------------+ //
int		ft_export(t_data *data, char **cmd);
int		check_is_env(char *line);
int		check_equal_sign(char *str);
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
t_bool	ft_cd(t_data *data, char **cmd);
// +------------------------------------------+ //
//   Unset                                     //
// +------------------------------------------+ //
int		ft_unset(t_data *data, char **cmd);
int		error_var_name(char *line);
int		ft_is_var_name(int c);
// +------------------------------------------+ //
//   Free                                       //
// +------------------------------------------+ //
void	reset_data(t_data *data);
void	free_data(t_data *data);
void	free_everything(t_data *data, char *str);
void	delete_one_env_var(t_env *env);
void	ft_lstclear_env(t_env *lst);
void	free_pipe(t_data *data, t_pipe *pipe);
// +------------------------------------------+ //
//   Echo                                       //
// +------------------------------------------+ //
int		ft_echo(char **cmd);
// +------------------------------------------+ //
//   Error                                      //
// +------------------------------------------+ //
void	ft_error(char *str);
void	err_free(char *msg, t_data *data, char *str);
void	err_free_command_not_found(char *msg, t_data *data, char *str);
// +------------------------------------------+ //
//   Input checks                               //
// +------------------------------------------+ //
void	remove_comment(t_data *data);
t_bool	even_nb_of_quote_marks(char *line);
void	remove_quotation_marks(t_data *data);
void	deduplicate_spaces(t_data *data);
void	space_before_after_chevron(t_data *data);
t_bool	too_many_chevrons_o_pipes(t_data *data);
t_bool	invalid_suite(t_data *data);
t_bool	file_not_found(char *line);
t_bool	valid_start_end(char *line);
// +------------------------------------------+ //
//   Parsing                                    //
// +------------------------------------------+ //
void	load_heredoc(t_data *data);
t_bool	parse_cmd(t_data *data);
t_bool	parse_cmd_content(t_data *data, t_cmd *head);
t_bool	open_file(t_cmd *head, char *file, t_bool opening);
// +------------------------------------------+ //
//   Environnement                              //
// +------------------------------------------+ //
void	delete_one_env_var(t_env *lst);
void	ft_lstclear_env(t_env *head);
t_env	*init_env(t_data *data, char **env);
t_env	*ft_lstnew_env(void);
char	*get_var_name(t_data *data, char *str);
char	*get_var_value(t_data *data, char *str);
char	*convert_env_var(t_data *data);
t_bool	special_cases(t_data *data, char **output, size_t *pos);
t_env	*find_var_env(t_data *data, char *var_name);
void	env_add_front(t_env **head, t_env *new);
char	**list_to_env(t_env *env_lst);
// +------------------------------------------+ //
//   Execute                                  //
// +------------------------------------------+ //
void	execute(t_data *data);
int		is_built_in(char **cmd);
void	make_one_built_in(t_data *data, t_cmd *cmd);
void	launch_built_in(t_data *data, t_cmd *cmd);
// +------------------------------------------+ //
//   Multipipe                                  //
// +------------------------------------------+ //
void	take_path(t_data *data);
void	find_command_path(t_data *data, t_cmd *head);
//void	error_var_name(t_data *data, t_cmd *new, char *cmd_line);
int		init_pipe(int nb_pipe, t_data *data, t_pipe *pipes);
int		init_pipe_struct(t_data *data);
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
void	close_all_fd(t_pipe *pipe);
void	close_fd_first_process(t_pipe *pipe);
void	close_fd_middle_process(t_pipe *pipe);
void	close_fd_last_process(t_pipe *pipe);
// +------------------------------------------+ //
//   Dup                                   //
// +------------------------------------------+ //
void	open_infile_and_heredoc(t_cmd *cmd);
void	dup_outfile(t_cmd *cmd, t_pipe *pipe);
// +------------------------------------------+ //
//   Fonction list CMD                          //
// +--------------------------------a----------+ //
void	cmd_add_back(t_cmd **alst, t_cmd *new);
t_cmd	*ft_lstnew_cmd(char *raw);
void	ft_lstclear_cmd(t_cmd *head);
int		ft_lstsize(t_cmd *lst);

#endif
