/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:20:11 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/09 06:51:44 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"
# include <errno.h>

int		execute_builtin_cd(char **to_cd, t_tab *tabs);
void	chdir_not_found(void);
int		execute_builtin_echo(char **args);
int		execute_builtin_env(char **env);
int		execute_builtin_exit(char **argv, t_tab *tabs,
			t_redirections *redirect);
int		execute_builtin_export(t_tab *tabs, char **to_export);
int		execute_builtin_pwd(void);
void	pwd_not_found(void);
int		execute_builtin_unset(t_tab *tabs, char **unset);
int		found_name_with_value(char **exp, char *to_find);
int		deal_with_oldpwd(t_tab *tabs, char *real_pwd_path,
			char *getenv_pwd_path);
int		deal_with_pwd(t_tab *tabs);
char	*ft_strdup_export(char *src, int i, int j);
char	**cpy_env_extend(char **env, char **to_export);
int		found_export_name_with_value(char **exp, char *to_find);
int		found_unset_name_without_value(char **exp, char *to_find);
char	**cpy_env_exp(char **env, char **cpy);
int		display_unset_error(int error_count, char *to_export);
char	*ft_getenv(char **env, char *to_find);
void	free_2d_tab(char ***tabs);
void	display(char **display);
int		len_env(char **env);
int		found_name(char **env, char *to_find);
int		execute_builtins(char **argv, t_tab *tabs, t_redirections *redirect);
int		display_export_error(int error_count, char *error);
char	*to_find(char *to_change);

#endif
