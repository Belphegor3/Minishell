#include <criterion/criterion.h>
#include "../libft.h"
#include <stdlib.h>

char	wrapper_toupper(unsigned int i, char c)
{
	(void)i;
	return (ft_toupper(c));
}

void	*map_toupper(void *s)
{
	return (ft_strmapi((char*)s, &wrapper_toupper));
}

Test(ft_lstmap, test)
{
	t_list	*head;
	t_list	*mapped;

	head = NULL;
	ft_lstadd_back(&head, ft_lstnew(strdup("Lorem")));
	ft_lstadd_back(&head, ft_lstnew(strdup("Ipsum")));
	ft_lstadd_back(&head, ft_lstnew(strdup("Dolor")));
	mapped = ft_lstmap(head, &map_toupper, &free);
	cr_assert_str_eq(mapped->content, "LOREM");
	cr_assert_str_eq(mapped->next->content, "IPSUM");
	cr_assert_str_eq(mapped->next->next->content, "DOLOR");
	ft_lstclear(&head, &free);
	ft_lstclear(&mapped, &free);
}
