#include <stdio.h>
#include "virtual_machine.h"

int			get_code(char ocp)
{
	if ((ocp & 1) && ((ocp >> 1) & 1))
		return (IND_CODE);
	else if ((ocp >> 1) & 1)
		return (DIR_CODE);
	else if (ocp & 1)
		return (REG_CODE);
	else
		return (0);
}

int		main(int ac, char **av)
{
	int i;
	char c;

	c = ft_atoi(av[1]);
	ft_printf("atoi: %d\n", c);
	i = 0;
	if (ac == 2)
	{
		while (i < 3)
		{
			printf("code for param number: %d is: %d\n", i + 1, get_code(c >> (6 - (2 * i))));
			i++;
		}
	}
	return (0);
}