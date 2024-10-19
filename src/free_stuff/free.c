#include "minishell.h"

void	*ft_free(void *pointer)
{
	if (pointer)
	{
		free(pointer);
		pointer = NULL;
	}
	return (NULL);
}
