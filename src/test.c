#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	long bytes;
	long i;

	if (argc ==2)
	{
		bytes = 0;
		i = 0;
		while (argv[1][i])
		{
			bytes += sizeof(argv[1][i]);
			i++;
		}
		printf("bytes sans \'0\': %ld\n", bytes);
		bytes += sizeof(0);
		printf("bytes avec \'0\': %ld\n", bytes);

	}
	return (0);
}

// gcc -Wall -Werror -Wextra src/test.c -L/mnt/nfs/homes/llalba/minishell/libft -lft && ./a.out