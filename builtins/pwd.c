#include "builtins.h"

int	main_pwd()
{
	char	str[4096];

	getcwd(str, 4096);
	ft_printf("%s\n", str);
	return (0);
}
