/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:06:47 by edomingu          #+#    #+#             */
/*   Updated: 2023/05/26 17:24:12 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <sys/stat.h>
# include "../lib/libft/libft.h"
# include "struct_defs.h"
# include "built_in_defs.h"
# include "env_manage.h"
# include "constants.h"
# include "../include/atoli.h"

int					*g_status;

// constants.c
t_built_in_funct	get_built_in(t_cmd_id id);

// free.c
void				ft_free(void **mem);
void				ft_free_matrix(void ***matrix);

// utils.c
int					ft_is_whitespace(const unsigned char c);
int					ft_is_end_of_word(const unsigned char c);
int					ft_is_path(char *path);
int					ft_is_exit(const char *str);
int					ft_isnumeric(const char *str);
// char				*ft_unsplit(const char **matrix, const char c);

// checks.c
int					ft_is_a_quote(char c);
// int					ft_quotes_are_closed(char c);
int					ft_check_quotes(const char *str);
int					ft_check_pipes(const char *str);

// checks2.c
int					ft_check_redirs(char **matrix);

// matrix_utils.c
void				ft_str_matrix_add(char ***matrix, const char *str);
size_t				ft_matrix_len(char **matrix);
void				ft_matrix_del_last(char **matrix);
// int					ft_is_string_in_matrix(char *str, char **matrix);
// char				**ft_matrix_dup(const char **matrix);
size_t				ft_matrix_size(char **matrix);
char				*ft_matrix_to_str(char **matrix);

// str_utils.c
int					ft_strcmp(const char *s1, const char *s2);
void				ft_stradd_str(char **s1, const char *s2);
void				ft_stradd_char(char **s1, char c);
char				ft_get_last_char(char *str);

// user_input.c
int					ft_user_input(t_built_ins_funct_args *bifa, char *end);

// prepare_redir.c
void				ft_create_pipe(t_built_ins_funct_args *bifa);
void				ft_redir_pipe_ini_on_child(t_built_ins_funct_args *bifa, \
												int flag_fork);
void				ft_redir_pipe_end_on_parent(t_built_ins_funct_args *bifa, \
												int flag_fork);

// parser.c
char				**ft_split_tokens(const char *str, t_list *envl);
char				*ft_expand_env_vars(const char *str, t_list *envl);
void				ft_added_trimmed(char **s1, char *s2);

// read.c
char				*ft_read_quotes(const char *str, int *pos);
char				*ft_read_word_no_quotes(const char *str, int *pos);
char				*ft_read_word_redir(const char *str, int *pos);
char				*ft_read_word(const char *str, t_list *envl, \
									int flag_heredoc);

//read2.c
char				**ft_read_command(char **cmd_line);

// path_utils.c
char				*ft_from_relative_to_absolute(char *relative_path, \
												t_list *envl);
void				ft_append_dir(char ***splited_path, char *dir);
char				*ft_read_dir(char *path);

// path_utils2.c
// char				*ft_init_path(char *relative_path, const char **env);
char				*ft_init_path(char *relative_path, t_list *env);

// handlers.c
void				ft_sigint_handler_father(int sig);
void				ft_handlers_father(void);
void				ft_handler_ignore(void);
void				ft_handlers_son(void);
void				ft_handlers_heredoc(void);

// redir_utils.c
int					ft_is_input_redirection(const t_redir_type redir_type);
int					ft_is_output_redirection(const t_redir_type redir_type);
int					ft_is_redirection(char *str);
void				ft_append_redir_info(t_cmd_info *cmd_info, \
											t_redir_info *redir_info);

// file_checker.c
int					ft_is_directory(char *filename);
int					ft_search_in_env_path(t_built_ins_funct_args *bifa);
int					ft_check_if_is_dir(char *filename);
int					ft_search_for_program(t_built_ins_funct_args *bifa);
int					ft_search_for_command(t_built_ins_funct_args *bifa);

// wait.c
pid_t				ft_wait_for_status(t_built_ins_funct_args *bifa, \
										t_cmd_info *ci);
void				ft_wait_for_pids(t_built_ins_funct_args *bifa);
void				ft_putstr_repl_line_n_redisp(char *str_2_put, \
													char *str_2_repl);

// cmd_info_exe.c
void				ft_cmd_exit(t_built_ins_funct_args *bifa);
void				ft_cmd_builtins(t_built_ins_funct_args *bifa);
void				ft_cmd_others(t_built_ins_funct_args *bifa);
void				ft_cmd_info_exe(t_built_ins_funct_args *bifa);

// read_utils.c
char				*ft_remove_quotation_marks(char *arg);
void				ft_read_quotes_loop(const char *str, int *pos, char **word);

// cmd_info_utils.c
void				ft_fill_cmd_info_init(t_cmd_info *cmd_info, char ***cmd);
void				ft_fill_cmd_info_body(t_cmd_info *cmd_info, char **cmd);

// ft_expand_status.c
void				ft_expand_status(char **cmd);

// expand_env_vars_heredoc.c
char				*ft_expand_env_vars_heredoc(const char *str, \
												t_list *envl);

// ft_strlen_safe.c
size_t				ft_strlen_safe(const char *s);

// ft_chdir.c
void				ft_chdir(t_built_ins_funct_args *bifa, char *new_dir, \
								char *arg);

// dup_utils.c
void				ft_dups2(int *fds);
void				ft_dups(int *fds);

// ft_split_safe.c
char				**ft_split_safe(char const *s, char c);

// list_utils.c
t_list				*ft_lstreverse(t_list **lst);
t_list				*ft_lstduprev_n_size(t_list *lst, size_t *len);
void				ft_lstreduce(t_list *lst, t_reduce_funct f, void *arg);
t_list				*ft_lstsort(t_list **lst, int (*comp)(void *, void *));

// redirect_open.c
void				ft_prepare_redirs(t_built_ins_funct_args *bifa);

// open_redir.c
int					ft_open_redir(t_built_ins_funct_args *bifa, \
									t_redir_info *ri);

// ft_dup2.c
int					ft_dup2(int *fd_src, int fd_dest);

// ft_close.c
int					ft_close(int *fd);

#endif