#include <criterion/criterion.h>
#include "../libft.h"

Test(ft_lstadd_back, empty_list)
{
	t_list	*head;

	head = NULL;
	ft_lstadd_back(&head, ft_lstnew("Lorem"));
	cr_assert_str_eq(ft_lstlast(head)->content, "Lorem");
	cr_assert(ft_lstlast(head)->next == NULL);
	ft_lstclear(&head, NULL);
}

Test(ft_lstadd_back, multiple_elements)
{
	t_list	*head;

	head = NULL;
	ft_lstadd_back(&head, ft_lstnew("Lorem"));
	ft_lstadd_back(&head, ft_lstnew("Ipsum"));
	ft_lstadd_back(&head, ft_lstnew("Dolor"));
	cr_assert_str_eq(head->content, "Lorem");
	cr_assert_str_eq(head->next->content, "Ipsum");
	cr_assert_str_eq(head->next->next->content, "Dolor");
	cr_assert(ft_lstlast(head)->next == NULL);
	ft_lstclear(&head, NULL);
}
