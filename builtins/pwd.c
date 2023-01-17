#include "builtins.h"

void	main_pwd(void)
{
	char	str[4096];

	getcwd(str, 4096);
	ft_printf("%s\n", str);
}
