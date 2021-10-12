# include <stdlib.h>
# include <stdio.h>

int	main()
{
	char *test;

	test = (char *)malloc(0);
	if (test)
	{
		printf("test existe\n");
		if (test[0])
			printf("test[0] existe\n");
	} else {
		printf("test n'existe pas\n");
	}
	free(test);
	printf("test freed\n");
	return (0);
}