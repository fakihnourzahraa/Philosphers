/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:55:36 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/21 18:26:21 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	philos_routine(t_philosophers **philos)
{
	while (1)
	{
		think(philos);
		take_forks(philos);
		eat(philos);
		put_down_forks(philos);
		sleep_philo(philos);
	}
}