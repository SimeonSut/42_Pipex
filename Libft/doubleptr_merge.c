
#include "libft.h"

char	**doubleptr_merge(char **start, char **end, int mode)
{
	int		s_len;
	int		e_len;
	int		o_len;
	char	**output;

	s_len = ft_doubleptr_len((const char **)start);
	e_len = ft_doubleptr_len((const char **)end);
	o_len = s_len + e_len;
	output = malloc((o_len + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	output[o_len] = NULL;
	while (--o_len >= s_len)
		output[o_len] = ft_strdup(end[--e_len]);
	while (--s_len >= 0)
		output[s_len] = ft_strdup(start[s_len]);
	if (mode == 0)
		return (output);
	else if (mode == 1)
		return (free_table(start), output);
	else if (mode == 2)
		return (free_table(end), output);
	return (free_table(start), free_table(end), output);
}
