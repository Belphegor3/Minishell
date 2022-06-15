#include <stdlib.h>
#include "libft.h"

static int	get_beginning_trim_size(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (set[0] && s1[i] && ft_strchr(set, s1[i]))
		i++;
	return (i);
}

static int	get_end_trim_size(char const *s1, char const *set)
{
	size_t	len_s1;
	int		i;

	len_s1 = ft_strlen(s1);
	if (len_s1 == 0)
		return (0);
	i = len_s1 - 1;
	while (set[0] && i != 0 && ft_strchr(set, s1[i]))
		i--;
	return (len_s1 - i - 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	len_s1;
	int		beginning_trim_size;
	int		end_trim_size;

	len_s1 = ft_strlen(s1);
	beginning_trim_size = get_beginning_trim_size(s1, set);
	end_trim_size = get_end_trim_size(s1, set);
	result = malloc(sizeof(char)
			* (len_s1 - beginning_trim_size - end_trim_size + 1));
	if (!result)
		return (0);
	ft_strlcpy(result, s1 + beginning_trim_size,
		len_s1 - beginning_trim_size - end_trim_size + 1);
	return (result);
}
