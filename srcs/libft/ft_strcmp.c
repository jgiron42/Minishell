//
// Created by joachim on 25/11/2021.
//

int	ft_strcmp(const char *s1, const char *s2)
{
	if ((!s1 && s2) || (!s2 && s1))
		return (1);
	if (!s1 && !s2)
		return (0);
	while (*s1 && *s2 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}
