/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoli_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:58:56 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/17 14:44:25 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/atoli.h"
#include "../include/minishell.h"

static int	ft_issign(int c)
{
	return (c == '-' || c == '+');
}

void	ft_atoli_ph0(const char *s, t_atoli_data *pd)
{
	while (s[pd->i] && ft_is_whitespace(s[pd->i]))
		pd->i++;
	if (!s[pd->i])
		pd->overf = 1;
	pd->phase++;
}

void	ft_atoli_ph1(const char *s, t_atoli_data *pd)
{
	if (ft_issign(s[pd->i]))
	{
		if (s[pd->i] == '-')
			pd->sign = -1;
		pd->phase++;
		pd->i++;
	}
	else if (ft_isdigit(s[pd->i]))
		pd->phase++;
	else
		pd->overf = 1;
}

void	ft_atoli_ph2(const char *s, t_atoli_data *pd)
{
	while (s[pd->i] && s[pd->i] == '0')
	{
		pd->i++;
		pd->dig_count++;
	}
	if (pd->dig_count == 0 && (!s[pd->i] || !ft_isdigit(s[pd->i])))
		pd->overf = 1;
	pd->phase++;
}

void	ft_atoli_ph3(const char *s, t_atoli_data *pd)
{
	if (ft_isdigit(s[pd->i]))
	{
		pd->res = pd->sign * (s[pd->i] - '0');
		pd->i++;
		pd->phase++;
	}
	else if (pd->i == 0 || (!ft_issign(s[pd->i - 1]) && s[pd->i - 1] != '0'))
		pd->overf = 1;
	else
		pd->phase += 2;
}
