/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvalue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 08:34:55 by dcaetano          #+#    #+#             */
/*   Updated: 2024/09/25 07:24:07 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*vars_getvalue(t_env *env, char *const key)
{
	t_vars	*iter;

	if (env == NULL || key == NULL || *key == '\0')
		return (NULL);
	iter = vars_first(env->envs);
	while (iter != NULL)
	{
		if (utils_strcmp(iter->key, key) == 0)
			return (iter->value);
		iter = iter->next;
	}
	if (utils_strcmp(key, "_") == 0)
		return (env->underscore);
	return (NULL);
}
