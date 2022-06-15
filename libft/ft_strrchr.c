char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*result;

	i = 0;
	result = 0;
	while (s[i])
	{
		if (s[i] == c)
			result = (char *)&s[i];
		i++;
	}
	return (result);
}
