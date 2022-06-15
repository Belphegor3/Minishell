#include <stdlib.h>
#include <unistd.h>
// void	execute_builtin_echo(t_syntax_node *token_list)
// {
// 	int	write_trailing_newline;
// 	int	i;
// 	int	j;

// 	write_trailing_newline = 1;
// 	if (token_list->left->token->slice.length)
// 	{
// 		j = 0;
// 		while (token_list->left->token.slice.start[j])
// 		{
// 			i = j;
// 			if (token_list->left->token.slice.start[i++] == '-')
// 			{
// 				while (token_list->left->token.slice.start[i] == 'n')
// 				{
// 					write_trailing_newline = 0;
// 					i++;
// 				}
// 				while (token_list->left->token.slice.start[i] && token_list->left->token.slice.start[i] == ' ')
// 					i++;
// 				{
// 					if (token_list->left->token.slice.start[i] && token_list->left->token.slice.start[i] == '-')
// 					{
// 						j += i;
// 						continue ;
// 					}
// 					else
// 					{
// 						/* afficher a partir de i si i existe en fonction de write_trailing_newline*/;
// 					}
// 				}
// 				else
// 				{
// 					/* afficher a partir de j (j existe forcement ici) en fonction de write_trailing_newline*/;
// 				}
// 			}
// 			else
// 			{
// 				/* afficher a partir de j parce que attention i vaut j + 1 ici donc on perdrait un caractere et ne pas oublier le newline */;
// 			}
// 		}
// 		// while (ft_strncmp("-", token_list->left->token.slice.start[++i], token_list->left->token->slice.length) == 0 && ft_strncmp("n", token_list->left->token->slice.start, token_list->left->token->slice.length) == 0
// 		// write_trailing_newline = 0;
// 		// token_list = token_list->right;
// 	}
// 	else
// 	{
// 		/* afficher le message enfin je crois que c est un ?WORD? genre ici c est un echo bonjour donc on affiche bonjour et faut s occuper des white spaces je sais pas dans le parsing ou ici directement*/;
// 	}
// }
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

void	execute_builtin_echo(char	*arg)
{
	int	newline;
	int	i;
	int	j;

	newline = 1;
	if (arg)
	{
		j = 0;
		while (arg[j])
		{
			i = j;
			while (arg[j] == ' ')
				j++;
			// i = j;
			if (arg[i++] == '-')
			{
				while (arg[i] == 'n')
				{
					newline = 0;
					i++;
				}
				while (arg[i])
				{	
					if (arg[i] != ' ')
						break ;
					i++;
				}
				if (arg[i] == '-' && arg[i + 1] == 'n')  /*	erreur vient du continue ici qui continue anyway apres le premier -n	*/
				{
					j += i;
					continue ;
				}
				else
				{
					if (newline == 1)
					{
						while (arg[j])
							write(1, &arg[j++], 1);
						write(1, "\n", 1);
						return ;
					}
					// while (arg[i])
					// 	if (arg[i++] != ' ')
					// 		break ;
					// i--;
					if (arg[i] != '-')
					{
						while (arg[i])
							write(1, &arg[i++], 1);
						return ;
					}
					
				}
			}
			else
			{
				/* afficher a partir de j (j existe forcement ici) en fonction de write_trailing_newline*/;
				while (arg[j])
					write(1, &arg[j++], 1);
				return ;
			}
			j = i;
		}
	}
	if (newline == 1)
		write(1, "\n", 1);
}

int	main(int ac, char **av)
{
	(void)ac;
	execute_builtin_echo(av[1]);
	return 0;
}