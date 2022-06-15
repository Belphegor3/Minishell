#include <criterion/criterion.h>
#include "../libft.h"

Test(ft_lstadd_front, add_one)
{
	t_list	*head;

	head = NULL;
	ft_lstadd_front(&head, ft_lstnew("Lorem"));
	cr_assert_str_eq(head->content, "Lorem");
	cr_assert(head->next == NULL);
	ft_lstclear(&head, NULL);
}

Test(ft_lstadd_front, add_multiple)
{
	t_list	*head;

	head = NULL;
	ft_lstadd_front(&head, ft_lstnew("Lorem"));
	cr_assert_str_eq(head->content, "Lorem");
	cr_assert(head->next == NULL);

	ft_lstadd_front(&head, ft_lstnew("Ipsum"));
	cr_assert_str_eq(head->content, "Ipsum");
	cr_assert_str_eq(head->next->content, "Lorem");
	cr_assert(head->next->next == NULL);
	ft_lstclear(&head, NULL);
}
