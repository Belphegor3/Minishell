#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			initial_len_dst;
	unsigned int	i;

	i = 0;
	while (dst[i] && i < size)
		i++;
	if (dst[i])
		return (ft_strlen(src) + size);
	initial_len_dst = i;
	i = 0;
	while (src[i] != '\0' && size > initial_len_dst + i + 1)
	{
		dst[initial_len_dst + i] = src[i];
		i++;
	}
	dst[initial_len_dst + i] = '\0';
	return (initial_len_dst + ft_strlen(src));
}
