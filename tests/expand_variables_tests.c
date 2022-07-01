#include <criterion/criterion.h>
#include "minishell.h"
#include "../expander.h"
#include "libft.h"

extern char	**environ;

int	g_status = 0;

Test(expand_variable, home)
{
	t_vector	v;
	int			iter;

	iter = 0;
	v = ft_veccreate(32, sizeof(char));
	ft_vecinsert(&v, 0, "$HOME", 6);
	cr_assert_str_eq(v.buffer, "$HOME");
	expand_variable(&v, &iter, environ);
	cr_assert_str_eq(v.buffer, getenv("HOME"));
	ft_vecdestroy(&v);
}

Test(expand_variable, non_existing)
{
	t_vector	v;
	int			iter;

	iter = 0;
	v = ft_veccreate(32, sizeof(char));
	ft_vecinsert(&v, 0, "$abc", 5);
	cr_assert_str_eq(v.buffer, "$abc");
	expand_variable(&v, &iter, environ);
	cr_assert_str_eq(v.buffer, "");
	ft_vecdestroy(&v);
}
