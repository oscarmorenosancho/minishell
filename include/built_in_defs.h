/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_defs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:11:26 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/09 17:07:53 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_DEFS_H
# define BUILT_IN_DEFS_H
# include "struct_defs.h"

// redirect_open.c
int				ft_open_fdout(t_built_ins_funct_args *bifa, t_cmd_info *ci);
int				ft_open_fdin(t_built_ins_funct_args *bifa, t_cmd_info *ci);
void			ft_open_dummy_redirs(t_built_ins_funct_args *bifa, \
					t_list *redir_lst, int i_o);

// built-ins built_ins_x.c
void			ft_none_exe(t_built_ins_funct_args *bifa);
void			ft_echo_exe(t_built_ins_funct_args *bifa);
void			ft_cd_exe(t_built_ins_funct_args *bifa);
void			ft_pwd_exe(t_built_ins_funct_args *bifa);
void			ft_export_exe(t_built_ins_funct_args *bifa);
void			ft_unset_exe(t_built_ins_funct_args *bifa);
void			ft_env_exe(t_built_ins_funct_args *bifa);
void			ft_exit_exe(t_built_ins_funct_args *bifa);
void			ft_exec_exe(t_built_ins_funct_args *bifa);

#endif