/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:52:32 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/08 17:32:17 by llalba           ###   ########.fr       */
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

# define MALLOC_ERROR	"Error: malloc failed\n"
# define INVALID_CHAR	"Error: invalid characters in your command\n"
# define END_CHAR_ERR	"Error: invalid char at the end of your command\n"
# define START_CHAR_ERR	"Error: invalid char at the beginning of your command\n"
# define ODD_NB			"Error: odd number of \' or \"\n"
# define TOO_MANY_ARG	"Error: minishell does not accept any argument\n"
# define TOO_MANY_ARG2	"Error: too many arguments\n"
# define HOME_NOT_SET	"Error: HOME not set\n"
# define LINE_TOO_LONG	"Error: this command is too long\n"
# define INVALID_STATUS	"Error: this exit status is not an int\n"
# define INVALID_OPTION	"Error: invalid option\n"
# define FILE_NOT_FOUND	"Error: no such file or directory\n"
# define CLOSE_FAILED	"Error: failed to close some file descriptors\n"
# define GNL_ERROR		"Error: failed to malloc or to read standard input\n"
# define CMD_NOT_FOUND	"Error: command not found\n"
# define NUMERIC_ARG	"Error: numeric argument required\n"
# define PIPE_FAILED	"Error: pipe failed\n"
# define FORK_FAILED	"Error: fork failed\n"
# define HEREDOC_EOF	"Warning: here-document delimited by EOF.\n"
# define SIGQUIT_MSG	"Quit (core dumped)\n"
# define BUFFER_SIZE 	511
# define ONE_RIGHT		1
# define TWO_RIGHT		2
# define ONE_LEFT		3
# define TWO_LEFT		4
# define HEREDOC_CONT	0
# define HEREDOC_END	1
# define TRUE			1
# define FALSE			0

// +------------------------------------------+ //
//   Utils                                      //
// +------------------------------------------+ //
void	signals_init(void);
void	signals_init_child(void);
void	update_exit_status(pid_t this_pid);
void	secure_between(char *str, char to_secure, char tmp, t_bool remove);
int		quote_status(char *str, size_t i);
t_bool	remove_surrounding_quotes(char **str);
void	protect_with_backslash(t_data *data);
void	replace_backslash(t_data *data);
int		get_next_line(char **line, t_bool flag);
// +------------------------------------------+ //
//   Builtins                                   //
// +------------------------------------------+ //
int		ft_pwd(t_data *data, char **cmd);
void	ft_exit(t_data *data, char **cmd); // FIXME j en ai fait un autre plus en adéquation avec les autres fonctions
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
void	change_directory(t_data *data, char *line);
t_bool	cdpath(t_data *data, char **cmd);
void	switch_old_pwd(t_data *data, char *line);
void	switch_pwd(t_data *data, char *line);
t_bool	arg_is_point_point(char *str);
int		go_to_old_pwd(t_data *data, char **cmd);
// +------------------------------------------+ //
//   Unset                                     //
// +------------------------------------------+ //
int		ft_unset(t_data *data, char **cmd);
int		error_var_name(char *line);
int		ft_is_var_name(int c);
// +------------------------------------------+ //
//   Free                                       //
// +------------------------------------------+ //
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
t_bool	env_special_cases(t_data *data, char **output, size_t *pos);
t_env	*find_var_env(t_data *data, char *var_name);
void	env_add_front(t_env **head, t_env *new);
char	**list_to_env(t_data *data, t_env *env_lst);
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
//   Dup                                        //
// +------------------------------------------+ //
void	open_infile_and_heredoc(t_cmd *cmd, int fd[2]);
void	dup_outfile(t_cmd *cmd, t_pipe *pipe);
void	command_failed_because_of_file_opening(t_data *data);
// +------------------------------------------+ //
//   Fonction list CMD                          //
// +--------------------------------a----------+ //
void	cmd_add_back(t_cmd **alst, t_cmd *new);
t_cmd	*ft_lstnew_cmd(char *raw);
void	ft_lstclear_cmd(t_cmd *head);
int		ft_lstsize(t_cmd *lst);
// +-------------------------------------------+ //
//   Utils Minishell                             //
// +--------------------------------a----------+ //
void	update_var_shlvl(t_data *data);

#endif
