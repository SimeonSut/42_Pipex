
#include "libft.h"

char	**doubleptr_add(char **src, char *add, int mode)
{
	int		len;
	int		i;
	char	**result;

	len = ft_doubleptr_len((const char **)src);
	len++;
	i = 0;
	result = malloc ((len + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[len] = NULL;
	while (src[i])
	{
		result[i] = ft_strdup(src[i]);
		i++;
	}
	result[i] = ft_strdup(add);
	if (mode == 0)
		return (result);
	else if (mode == 1)
		return (free_table(src), result);
	else if (mode == 2)
		return (free(add), result);
	return (free_table(src), free(add), result);
}
