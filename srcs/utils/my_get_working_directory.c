
#include "minishell.h"

char	*my_get_working_directory(const char *for_whom)
{
	char *ret;
	char buf[PATH_MAX];

	ret = NULL;
	ret = getcwd(buf, PATH_MAX);
	if (!ret) {
		if (errno == ENOMEM)
			return (NULL);
		ft_putstr_fd((char *)for_whom, 2);
		write(2, ": ", 2);
		perror("get_cwd()");
		return (NULL);
	}
	return (ft_strdup(ret));
}
