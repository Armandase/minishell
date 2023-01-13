#include "builtins.h"

void	main_pwd(void)
{
	char	str[1024];

	getcwd(str, 1024);
	ft_printf("%s\n", str);
}
