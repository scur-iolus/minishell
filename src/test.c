#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	short success;
	char *test;

	(void)argv;
	if (argc >= 1)
	{
		test = (char *)ft_calloc(1, sizeof(char));
		success = ft_str_insert_char(&test, '1', ft_strlen(test));
		success = ft_str_insert_char(&test, '2', ft_strlen(test));
		success = ft_str_insert_char(&test, '3', 0);
		success = ft_str_insert_char(&test, '4', ft_strlen(test));
		success = ft_str_insert_char(&test, '5', 2);
		success = ft_str_insert_str(&test, "h", 5);
		printf("%i : %s\n", success, test);
		free(test);
	}
	return (0);
}

// gcc -Wall -Werror -Wextra src/test.c -L/mnt/nfs/homes/llalba/minishell/libft -lft && ./a.out