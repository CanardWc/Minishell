/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_build_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 06:21:27 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:21:30 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*ms_build_env(char **env)
{
	t_list	*ret;
	t_env	*tmp;
	int		i;

	ret = NULL;
	while (*env)
	{
		i = 0;
		tmp = (t_env *)malloc(sizeof(t_env));
		while ((*env)[i] && (*env)[i] != '=')
			i++;
		tmp->key = ft_substr(*env, 0, i);
		tmp->value = ft_strdup(*env + i + 1);
		ft_lstadd_back(&ret, ft_lstnew(tmp));
		env++;
	}
	return (ret);
}
