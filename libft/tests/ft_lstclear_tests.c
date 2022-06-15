#include <criterion/criterion.h>
#include "../libft.h"
#include <stdlib.h>

Test(ft_lstclear, one_element)
{
	t_list	*head;

	head = NULL;
	ft_lstadd_back(&head, ft_lstnew(strdup("Lorem")));
	ft_lstclear(&head, &free);
	cr_assert(head == NULL);
}

Test(ft_lstclear, multiple_elements)
{
	t_list	*head;

	head = NULL;
	ft_lstadd_back(&head, ft_lstnew(strdup("Lorem")));
	ft_lstadd_back(&head, ft_lstnew(strdup("Ipsum")));
	ft_lstadd_back(&head, ft_lstnew(strdup("Dolor")));
	ft_lstclear(&(head->next), &free);
	cr_assert_str_eq(head->content, "Lorem");
	cr_assert(head->next == NULL);
	ft_lstclear(&head, &free);
}
