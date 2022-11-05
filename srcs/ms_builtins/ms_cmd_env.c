/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 06:11:19 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:29:02 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_cmd_env(t_data *data, char **line)
{
	t_list	*tmp;
	t_env	*ret;

	tmp = data->env;
	if (*++line)
		printf("env command can't take options or arguments\n");
	else
	{
		while (tmp)
		{
			ret = tmp->content;
			printf("%s=%s\n", ret->key, ret->value);
			tmp = tmp->next;
		}
	}
	data->exit_status = 0;
}
