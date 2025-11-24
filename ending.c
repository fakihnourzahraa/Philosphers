/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:46:06 by nour              #+#    #+#             */
/*   Updated: 2025/11/23 19:49:18 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dying(t_philosophers *philo)
{
	long long time;

	pthread_mutex_lock(philo->rules->print);
	time = get_time() - philo->rules->start_time;
	printf("%lld %d died\n", time, philo->index);
	pthread_mutex_unlock(philo->rules->print);
}
