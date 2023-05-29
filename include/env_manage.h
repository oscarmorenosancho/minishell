/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:03:54 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/23 18:19:50 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MANAGE_H
# define ENV_MANAGE_H

# include <stdlib.h>

//env_utils.c
size_t		ft_varname_len(const char *name);
int			ft_check_valid_env_name(const char *name);

//	ft_increase_shlvl.c
t_list		*ft_increase_shlvl_envl(t_list **env);

//	env_var_utils.c
void		ft_format_env_var_line(unsigned int i, void *c, void *arg);
void		ft_print_env_var_line(unsigned int i, void *c, void *arg);
void		ft_print_exp_var_line(unsigned int i, void *c, void *arg);

//	env_var_utils2.c
char		**ft_env_var_2_matrix(t_list *l);
t_list		*ft_env_line_2_node(char *line);
t_list		*ft_env_var_2_list(char **t);

//	env_var.c
t_env_var	*ft_create_env_var(char *name, char *value);
void		ft_dispose_env_var(void *env_var);
t_list		*ft_create_env_node(char *name, char *value);
void		ft_append_env_node(t_list **lst, char *name, char *value);

//	env_var2.c
t_list		*ft_search_env(t_list *lst, char *name);
t_list		*ft_lstextract(t_list **lst, t_list *node);
void		ft_update_env_value(t_list *node, char *value);
void		ft_set_env_value(t_list **lst, char *name, char *value);
void		ft_append_env_value(t_list **lst, char *name, char *con_value);

//	env_var3.c
int			ft_env_comp(void *arg1, void *arg2);
t_list		*ft_search_env_inspos(t_list *lst, t_list *to_ins, \
									int (*comp)(void *, void *));

// envl_manage.c
t_list		*ft_envl_init(char **original);
char		*ft_get_envl(const char *name, t_list *envl);
t_list		*ft_set_envl(const char *name, const char *src, t_list **envl);
t_list		*ft_unset_envl(const char *name, t_list **envl);
void		ft_put_envl(int fd, t_list *envl, char *prefix);

#endif
