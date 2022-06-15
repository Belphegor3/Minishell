#include <criterion/criterion.h>
#include "../libft.h"

void	turns_first_char_into_J(void *s)
{
	((char*)s)[0] = 'J';
}

Test(ft_lstiter, test)
{
	t_list	*head;

	head = NULL;
	ft_lstadd_back(&head, ft_lstnew(strdup("Lorem")));
	ft_lstadd_back(&head, ft_lstnew(strdup("Ipsum")));
	ft_lstadd_back(&head, ft_lstnew(strdup("Dolor")));
	ft_lstiter(head, &turns_first_char_into_J);
	cr_assert_str_eq(head->content, "Jorem");
	cr_assert_str_eq(head->next->content, "Jpsum");
	cr_assert_str_eq(head->next->next->content, "Jolor");
	ft_lstclear(&head, &free);
}
