# include "minishell.h"

char	*find_outfile_name(char *prompt, int i)
{
	char	*file_name;
	int		start;
	int		end;
	int		name_len;

	file_name = NULL;
	start = i;
	while (prompt[i] && !ft_isspace(prompt[i]))
	{
		i++;
	}
	end = i;
	name_len = end - start;
	file_name = malloc(sizeof(char) * name_len + 1);
	i = 0;
	while (prompt[i] && !ft_isspace(prompt[i]))
	{
		file_name[i] = prompt[start + i];
		i++;
	}
	file_name[start + i] = '\0';
	printf("%s\n", file_name);
	return(file_name);
}

int	check_outfile(char *prompt, int i)
{
	char	*outfile_name;
	int		fd;

	outfile_name = find_outfile_name(prompt, i);
	fd = open(outfile_name, O_CREAT);
	if (fd == -1)
		return (-1);
	return (0);
}