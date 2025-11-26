/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:46:06 by nour              #+#    #+#             */
/*   Updated: 2025/11/26 17:38:33 by nfakih           ###   ########.fr       */
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
	pthread_mutex_lock(philo->rules->death);
	philo->rules->finish_all = 1;
	pthread_mutex_unlock(philo->rules->death);
	// exit(1);
}
