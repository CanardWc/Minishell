/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 06:11:03 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:29:02 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ms_get_home(t_data *data)
{
	t_list	*tmp;
	t_env	*oui;

	tmp = data->env;
	while (tmp)
	{
		oui = tmp->content;
		if (!ft_strcmp(oui->key, "HOME"))
			return (oui->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ms_cmd_cd(t_data *data, char **line)
{
	char	*home;

	if (!line[1])
	{
		home = ms_get_home(data);
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return ;
		}
		if (chdir(home))
			printf("%s\n", strerror(errno));
		return ;
	}
	if (chdir(line[1]))
	{
		printf("%s\n", strerror(errno));
		data->exit_status = errno;
	}
	else
		data->exit_status = 1;
}
