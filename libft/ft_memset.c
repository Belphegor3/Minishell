#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;

	i = -1;
	while (++i < n)
		((char *)s)[i] = c;
	return (s);
}
