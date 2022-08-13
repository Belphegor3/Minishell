/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:09:09 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/13 13:40:31 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "builtins.h"
#include "executor.h"

int	g_status;

static char	**cpy_exp(char **env)
{
	int		i;
	char	**cpy;

	i = 0;
	cpy = malloc(sizeof(char *) * (len_env(env) + 1000));
	if (!cpy)
		return (printf("\033[1;31mCopy failed\033[0m"), NULL);
	while (env[i])
	{
		cpy[i] = ft_strdup(env[i]);
		if (!cpy[i])
			return (free_2d_tab(&cpy),
				printf("\033[1;31Copy failed\n\033[0m"), NULL);
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

static int	check_for_unclosed_quotes(char *line)
{
	while (*line)
	{
		if (*line == '\'')
		{
			line = ft_strchr(line + 1, '\'');
			if (line == NULL)
				return (ft_putstr_fd("minishell: unexpected EOF "
						"while looking for matching `''\n", 2), -1);
		}
		else if (*line == '\"')
		{
			line = ft_strchr(line + 1, '\"');
			if (line == NULL)
				return (ft_putstr_fd("minishell: unexpected EOF "
						"while looking for matching `\"'\n", 2), -1);
		}
		line++;
	}
	return (0);
}

void	parse_and_execute_line(char *line, t_tab *tabs)
{
	t_dlist			*token_list;
	t_syntax_node	*syntax_tree;

	add_history(line);
	if (check_for_unclosed_quotes(line) == 0)
	{
		token_list = lexer(line);
		free(line);
		if (!token_list)
			return ;
		if (check_for_unexpected_token(token_list) == 0)
		{
			syntax_tree = parser(&token_list, tabs->env);
			ft_dlstclear(&token_list, NULL);
			if (syntax_tree)
				executor(&syntax_tree, tabs);
			delete_syntax_tree(&syntax_tree);
			return ;
		}
		else
			ft_dlstclear(&token_list, (void *)destroy_token);
	}
	else
		free(line);
	g_status = 2;
}

static void	clear_exit(t_tab *tabs)
{
	close_standard_fds();
	rl_clear_history();
	free_2d_tab(&tabs->env);
	free_2d_tab(&tabs->exp);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_tab			tabs;

	(void)argc;
	(void)argv;
	tabs.env = cpy_exp(envp);
	tabs.exp = cpy_exp(envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_interactiv_signals);
	line = readline("$ ");
	while (line)
	{
		signal(SIGQUIT, &handle_non_interactiv_signals);
		signal(SIGINT, &handle_non_interactiv_signals);
		if (line[0] == '\0')
			free(line);
		else
			parse_and_execute_line(line, &tabs);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handle_interactiv_signals);
		line = readline("$ ");
	}
	clear_exit(&tabs);
	return (g_status);
}
