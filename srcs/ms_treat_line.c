#include <minishell.h>

//number of pipes
//error gestion
// > meme si erreur les fichiers sont créés.
// jamais deux chevrons a la suite séparé par un espace
// jamais plusieurs pipe a la suite

int	ms_treat_line(t_data *data)
{
	t_list	*tmp;
	int	mark;

	mark = 0;
	tmp = data->args;
	while (tmp)
	{
		if (ft_strchr("<>|", **(char **)(tmp->content)))
		{
			if (mark)
				return (ft_printf("syntax error near unexpected token `%c'\n", **(char **)(tmp->content)));
			mark = 1;
		}
		else
			mark = 0;
		//check dollars;
		tmp = tmp->next;
	}
	if (mark)
		return (ft_printf("syntax error near unexpected token `newline'\n"));
	return (0);
}
