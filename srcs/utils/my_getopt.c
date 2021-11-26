//
// Created by jgiron on 11/26/21.
//

void	my_getopt(char ***argv, char *option, char dest[256])
{
	int	i;

	i = 0;
	while (i < 256)
		dest[i] = 0;
	while (**argv && ***argv == '-')
	{
		i = 0;
		while ((**argv)[++i])
			if (!ft_strchr(option, (**argv)[i]))
				return;
		i = 0;
		while ((**argv)[++i])
			dest[*ft_strchr(option, (**argv)[i])] = 1;
		(*argv)++;
	}
}