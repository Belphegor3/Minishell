#include <unistd.h>
#include "lexer.h"
#include "parser.h"
#include <limits.h>
#include <stdlib.h>

void	execute_builtin_echo(t_syntax_node *token_list)
{
	int	write_trailing_newline;
	int	i;
	int	j;

	write_trailing_newline = 1;
	if (token_list->left->token->slice.length)
	{
		j = 0;
		while (token_list->left->token.slice.start[j])
		{
			i = j;
			if (token_list->left->token.slice.start[i++] == '-')
			{
				while (token_list->left->token.slice.start[i] == 'n')
				{
					write_trailing_newline = 0;
					i++;
				}
				while (token_list->left->token.slice.start[i] && token_list->left->token.slice.start[i] == ' ')
					i++;
				{
					if (token_list->left->token.slice.start[i] && token_list->left->token.slice.start[i] == '-')
					{
						j += i;
						continue ;
					}
					else
						/* afficher a partir de i si i existe en fonction de write_trailing_newline*/
				}
				else
					/* afficher a partir de j (j existe forcement ici) en fonction de write_trailing_newline*/
			}
			else
				/* afficher a partir de j parce que attention i vaut j + 1 ici donc on perdrait un caractere et ne pas oublier le newline */
		}
		// while (ft_strncmp("-", token_list->left->token.slice.start[++i], token_list->left->token->slice.length) == 0 && ft_strncmp("n", token_list->left->token->slice.start, token_list->left->token->slice.length) == 0
		// write_trailing_newline = 0;
		// token_list = token_list->right;
	}
	else
		/* afficher le message enfin je crois que c est un ?WORD? genre ici c est un echo bonjour donc on affiche bonjour et faut s occuper des white spaces je sais pas dans le parsing ou ici directement*/
}
	/*while (token_list->right)
	{
		write(1, token_list->left->token->slice.start, token_list->left->token->slice.length);
		write(1, " ", 1);
		token_list = token_list->right;
	}
	write(1, token_list->left->token->slice.start, token_list->left->token->slice.length);
	if (write_trailing_newline)
		write(1, "\n", 1);
}*/

int	execute_builtin_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
		return (ft_putendl_fd(current_path, 1) , EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	execute_builtin_env(/* je dois recevoir l env avec un char **env par exemple*/)
{
	while (/* on est dans l env */)
		ft_putendl_fd(/*env*/, 1);
}


