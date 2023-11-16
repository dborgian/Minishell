/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:48:28 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/16 16:16:31 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <inttypes.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_varie
{
	int				i;
	int				j;
	int				z;
	int				newlen;
	int				withinquotes;
	int				withindoublequotes;
	int				quotesstack;
	int				doublequotesstack;
	char			*newstr;
}					t_varie;

typedef struct s_pipe
{
	int				num_pipes;
	int				i;
	int				*fds;
	int				std_out;
	int				std_in;
	int				fd;
	int				fd_out;
	int				j;
}					t_pipex;

typedef struct s_flags
{
	int				command_separator;
	int				operators;
	int				major;
	int				minor;
	int				quote_flag;
	int				redirect_input;
	int				redirect_output;
	int				brackets;
	int				pipes;
}					t_flags;

typedef struct s_args
{
	char			*str;
	char			*command;
	char			*flags;
	char			*argument;
	char			*redirect;
	char			*infile;
	char			*outfile;
	int				order;
	int				redirection_quantity;
	struct s_args	*previous;
	struct s_args	*next;
}					t_args;

typedef struct s_shell
{
	char			*home;
	char			*input;
	int				command_presence;
	char			*main_path;
	char			**envp;
	char			**new_envp;
	char			*syntax;
	int				dollar_flag;
	int				exit;
	int				total_pipes;
	int				flag_status;
	t_flags			flags;
	t_args			**list;
	t_args			**high;
}					t_shell;

// general_utils.c
int					ft_revstr(char *str, char c);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strcpy(char *dest, const char *src);
char				*rev_string(char *s);
int					ft_strcmp(char *s1, char *s2);

// stronzo.c
void				init_flags(t_shell *mini);
void				print_error(char *error);

// split_strings.c
void				splitting_operators(t_shell *mini);
t_args				*ft_lstnew_mini(void);
void				ft_lstadd_back_mini(t_args **lst, char *command);

// parser.c
void				analizer(t_shell *mini, char **envp);
char				*check_path(t_shell *mini, char *command);
int					check_redirection(char *s);
void				free_matrix(char **matrix);
void				redirecting_nodes(t_shell *mini, t_args *new, t_args *red);
int					check_path2(t_shell *mini, char *s);

// parser_utils.c
void				checking_node_vilidity(t_shell *mini);
void				ultimating_commands(t_shell *mini);
int					reassembling_strings(t_shell *mini, char **temp, int i);
void				its_a_command(t_shell *mini, char *temp);
void				its_not_a_command(t_shell *mini, char *temp, int i);
void				boh(t_shell *mini, char *temp);
int					reassembling_brackets(t_shell *mini, char **temp, int i);
void				its_a_flag(t_shell *mini, char *temp);

// lists.c
t_args				*create_node(t_shell *mini, char *data);
void				insert_last_with_delimiter(t_shell *mini, char delim);
void				print_list(t_args **head);
void				init_node(t_args *node);
void				handling_dollar(t_shell *mini);

// ft_mini_split.c
char				**ft_mini_split(t_shell *mini, char *s, char c);
char				**creting_matrix_to_populate_nodes(char **tokens);
int					operator_checker(const char *s, char control);
char				*ft_strjoin_mini(char const *s1, char const *s2, int free1,
						int free2);
int					apices(const char *s, char control,
						int pos);
char				**new_function(char **matrix);

// test_input.c
int					start(t_shell *mini);
char				*insertSpaces(char *str, int len);
int					isDelimiter(char c, char *str, int i);
char				*getting_final_string(char *s, char c);
int					counting(char *s);

// expander.c
char				*expanding_dollar_own_variables(t_shell *mini, char *s);
void				replacer(t_shell *mini);
void				get_dollars(t_shell *mini, char *s);
char				*expanding_d(t_shell *mini, char *s);

// lists_utils.c
void				test(t_shell *mini, t_args *new_node);
void				clear_list(t_shell *mini);
void				adding_rediretion_node(t_shell *mini, t_args **node);

// wildcats.c
char				**wildone(t_shell *mini, t_args *node);

// wildcats2.c
void				wild(t_shell *mini);

// wildcats3.c
int					counting_dir(char *cartella);
void				**case_one(DIR *dir, char **temp);
void				control(char c, t_args *node);

// signal.c
void				handlectrl(t_shell *mini, char **envp);
void				handlectrlc(int signal);

// builtin_ctrl.c
int					check_builtin_presence(t_shell *mini, char *command);
void				builtin_exec(t_shell *mini, char **envp, t_args *node,
						char *temp);

// builtin_exec.c
void				command_echo(t_shell *mini, char **envp, t_args *current);
void				command_cd(t_shell *mini, t_args *node, char *arg);
void				command_pwd(t_shell *mini, t_args *current);
void				command_env(t_shell *mini);

// export_unset.c
void				command_export(t_shell *mini, char **envp, char *str);
void				command_unset(t_shell *mini, char *str);
void				delete_var(t_shell *mini, int i);
void				delete_var2(t_shell *mini, int i);
void				command_unset2(t_shell *mini, char *str, int i);
void				order_new_envp(t_shell *mini);

// export_utils.c
char				*get_env_value(char *env);
char				*get_env_name(char *env);
void				swap_envp(t_shell *mini, int i, int k);
void				create_new_var(t_shell *mini, char *str);
void				copy_envp(t_shell *mini, char **envp);
char				**new_new_envp(char *s, t_shell *mini);

// pipe.c
int					pipe_set_up(t_shell *mini, t_args **node);
void				pipe_init(t_shell *mini, t_args **node);
void				execpipe(t_shell *mini, t_args *node);
void				single(t_shell *mini, t_args *node, char **envp);
void				screening_terminal(t_shell *mini, t_args *node,
						int temp_fd);
char				**redirect_input_no_pipes(t_shell *mini, t_args *node,
						char ***commands, char **envp);
void				no_pipes(t_shell *mini, t_pipex *pipes, t_args *cur,
						char ***commands);
void				first_command_w_outfile(t_pipex *pipes, t_args *cur);
void				first_command_in_pipe(t_shell *mini, t_pipex *pipes,
						t_args *cur, char ***commands);
void				last_command_w_outfile(t_pipex *pipes, t_args *cur);
void				last_command_in_pipe(t_shell *mini, t_pipex *pipes,
						t_args *cur, char ***commands);
void				mid_command_w_outfile(t_pipex *pipes, t_args *cur);
void				mid_command_in_pipe(t_shell *mini, t_pipex *pipes,
						t_args *cur, char ***commands);
void				close_n_wait(t_pipex *pipes);
void				august(t_shell *mini, t_pipex *pipes, t_args *cur,
						char ***commands);
t_args				*while_in_pipes(t_shell *mini, t_pipex *pipes, t_args *cur,
						char ***commands);

// builtins_pipe
void				builtin_pipe(t_shell *mini, t_pipex *pipes, t_args *cur);
void				init_pipexxx(t_pipex *pipes, t_shell *mini, t_args *cur);
char				**ft_echo_split(t_shell *mini, char const *s, char c);
void				echo_replacer(t_shell *mini, t_args *node);

// test_input.c
int					start(t_shell *mini);
char				*insert_spaces(char *str, int len);
int					is_delimiter(char c, char *str, int i);
char				*getting_final_string(char *s, char c);

// test_input_utils.c
void				init_varie(t_varie *varie, int len);

// test_input_utils.c
void				first_half(t_varie *var, char *s, char c);
void				sencond_half(t_varie *var, char *s, char c);

char				**new_new_function(char **matrix, char **final);
char				**mini_choosing_final(t_shell *mini, char **matrix,
						char *s);
void				ft_mini_cicle(t_shell *mini, char *s, char **str,
						unsigned int count);
char				**creting_matrix_to_populate_nodes(char **matrix);
char				**coping_matrix(char **matrix, char **final);
int					mini_g(t_shell *mini, char *s, int i, char c);
void				mini_h(t_shell *mini, char *s, int i);
int					ft_mini_strcheck(char const *s, char c);
unsigned int		ft_mini_counter(char const *s, char c);
char				*mini_p(t_shell *mini, int i, int j, int z);
int					ft_echo_strcheck(char const *s, char c);
int					check_quotes(t_shell *mini, char const *s, int i, char c);
void				init_fd(t_pipex *pipes);

// create_matri.c
char				**create_matri(t_args *node);
int					count_size(t_args *node);
char				**allocate_memory(int size);
void				copy_arguments(char **temp, char **arguments);

char				*get_my_env(t_shell *mini, char *d);
void				cloning_envp(t_shell *mini, char **envp);
char				*get_my_new_env(t_shell *mini, char *d);
int					my_strchr(const char *s, int c);
void				command_env2(t_shell *mini, char *dollar);

void				clear_mini(t_shell *mini, int flag);
void				clear_high(t_shell *mini);
char				**tyu(t_args *node, int *dollar_pos);
char				*echo_expanding_d(t_shell *mini, char *s);
char				*ft_quite_strong(t_args *node, int *dollar_pos);

//export argu
char				**argu(t_args *node);
char				*ft_quite_strong2(t_args *node);
char				*ft_strongest2(t_args *node, int i, int j, int counter);
char				**new_new_envp(char *s, t_shell *mini);
int					ft_contace2(char *str, char c);

//echo_replacer_utils.c

int					ft_contace(char *str, char c, int *dollar_pos);
int					check(char	*s);
void				argu_export(t_shell *mini, char **envp, t_args *node);
void				argu_unset(t_shell *mini, char **envp, t_args *node);
char				*echo_rep_supp(t_shell *mini, char **matrix,
						char *en, int *dollars_pos);
bool				checking(int i, int *dollars_pos);

#endif
