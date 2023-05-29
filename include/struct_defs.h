/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_defs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edomingu <edomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:07:38 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/24 13:23:38 by edomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_DEFS_H
# define STRUCT_DEFS_H
# include "minishell.h"

typedef enum e_cmd_id
{
	cmd_none,
	cmd_echo,
	cmd_cd,
	cmd_pwd,
	cmd_export,
	cmd_unset,
	cmd_env,
	cmd_exit,
	cmd_exec,
	cmd_unknown
}	t_cmd_id;

typedef enum e_redir_type
{
	redir_none,
	redir_inputFile,
	redir_heredoc,
	redir_outputFile,
	redir_appendOutputFile
}	t_redir_type;

// typedef struct s_flag_info
// {
// 	char				id;
// 	char				*arg;
// 	struct s_flag_info	*next;
// }	t_flag_info;

typedef struct s_redir_info
{
	char				*file_name;
	t_redir_type		redir_type;
}	t_redir_info;

//t_cmd_info is a stuct type to store info related to a 
//	single command to be executed
//args is a null terminated array or strings corresponding to
//	the arguments to send to the command.
//flags is a list of flag_info,
//	each for an option flag with arg to send the the command.
typedef struct s_cmd_info
{
	t_cmd_id			cmd_id;
	pid_t				pid;
	int					status;
	char				**args;
	t_list				*redir_list;
	t_redir_info		*last_input;
	t_redir_info		*last_output;
}	t_cmd_info;

//t_cmd_list represents a set of commands to be executed sequentially, 
//	chained by pipes and redirections.
//the first command element will use the redirection for the input,
//the last command element will use the redirection for the output,
//all command element will use the error redirection.
//a null terminated array of command info structs called lst will be
//	the elements ot this set.

typedef struct s_cmd_list
{
	t_list		*lst;
}	t_cmd_list;

typedef struct s_exec_data
{
	t_list			*envl;
	t_cmd_list		*cmd_list;
	int				result;
}	t_exec_data;

typedef struct s_built_ins_funct_args
{
	t_cmd_info	*ci;
	t_exec_data	*ed;
	int			i;
	int			last;
	int			fds_status[2];
	int			tmp_stfds[2];
	int			pipe_fds[2];
	int			redir_fds[2];
	int			abort;
	int			abort_redirs;
}	t_built_ins_funct_args;

typedef struct s_main_data{
	char			*line;
	char			**matrix;
	t_exec_data		ed;
	int				flag_quotes;
	int				flag_pipes;
}	t_main_data;

typedef struct s_env_var
{
	char	*name;
	char	*value;
}	t_env_var;

typedef void	(*t_built_in_funct)(t_built_ins_funct_args *);
typedef void	(*t_reduce_funct)(unsigned int, void *, void *);

// redirection info redir_info.c
t_redir_info	*ft_create_redir_info(char *file_name, t_redir_type redir_type);
// int				ft_dispose_redir_info(t_redir_info **ri);
void			ft_dispose_redir_info(void *ri);
int				ft_append_redir(t_redir_info **rl, t_redir_info *ri);
t_redir_type	ft_get_redir_type(char *redir_type);

// command info cmd_info.c
// t_cmd_info		*ft_create_cmd_info(t_cmd_id cid);
t_cmd_info		*ft_create_cmd_info(void);
// int				ft_dispose_cmd_info(t_cmd_info	**ci);
void			ft_dispose_cmd_info(void *ci);
int				ft_append_cmd(t_cmd_info **cl, t_cmd_info *ci);
// int				ft_append_flag_to_cmd_info(t_cmd_info *ci, t_flag_info *fi);
t_cmd_id		ft_get_cmd_id(char *cmd_name);
// int				ft_init_cmd_info(t_cmd_info *cmd_info, char **cmd);
t_cmd_info		*ft_init_cmd_info(char **cmd);
void			ft_fill_cmd_info(t_cmd_info *cmd_info, char **cmd);
void			ft_append_redir_info(t_cmd_info *cmd_info, \
					t_redir_info *redir_info);

// command list cmd_list.c
t_cmd_list		*ft_create_cmd_lst(void);
void			ft_dispose_cmd_lst(t_cmd_list **cl);
int				ft_append_cmd_to_lst(t_cmd_list **cl, t_cmd_info *ci);
t_cmd_info		*ft_get_cmd_from_lst(t_cmd_list **cl, int index);
t_cmd_list		*ft_init_cmd_lst(char **cmd_line);

// command list executor cmd_exe.c
int				ft_cmd_exe(t_exec_data *ed);
void			ft_cmd_iter(t_exec_data *ed);

#endif