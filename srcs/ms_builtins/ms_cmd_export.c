/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 05:29:36 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:29:02 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_strndup(const char *s, size_t n)
{
	char	*result;
	size_t	idx;
	size_t	len;

	idx = 0;
	len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * len + 1);
	while (s[idx] && idx < n)
	{
		result[idx] = s[idx];
		idx++;
	}
	result[idx] = '\0';
	return (result);
}

static t_env	*ms_search(t_list *lst, char *key)
{
	t_env	*env;

	while (lst)
	{
		env = lst->content;
		if (!ft_strcmp(env->key, key))
			return (env);
		lst = lst->next;
	}
	return (NULL);
}

static void	ms_args(t_data *data, char **line)
{
	t_env	*new;
	t_env	*ret;

	while (*(++line))
	{
		if (!ft_strchr(*line, '='))
			continue ;
		new = (t_env *)malloc(sizeof(t_env));
		new->key = ft_strndup(*line, ft_strchr(*line, '=') - *line);
		new->value = ft_strdup(ft_strchr(*line, '=') + 1);
		ret = ms_search(data->env, new->key);
		if (!ret)
			ft_lstadd_back(&data->env, ft_lstnew(new));
		else
		{
			ret->value = new->value;
			free(new->key);
			free(new);
			new = NULL;
		}
	}
}

void	ms_cmd_export(t_data *data, char **line)
{
	t_list	*tmp;
	t_env	*env;

	if (!line[1])
	{
		tmp = data->env;
		while (tmp)
		{
			env = tmp->content;
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
			tmp = tmp->next;
		}
	}
	else
		ms_args(data, line);
	data->exit_status = 0;
}
