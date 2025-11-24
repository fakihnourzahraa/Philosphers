/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:55:36 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/23 19:46:45 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*philos_routine(void *arg)
{
	t_philosophers *philo;
	int				s;

	philo = (t_philosophers *)arg;
	pthread_mutex_lock(philo->rules->death);
	while (philo->rules->finish_all == 0)
	{
		pthread_mutex_unlock(philo->rules->death);
		if (philo->index % 2 == 0)
			s = 0;
		else
			s = 1;
		thinking(philo);
		taking_fork(philo, s);
		taking_fork(philo, s + 2);
		eating(philo);
		releasing_fork(philo, s);
		releasing_fork(philo, s + 2);
		sleeping_philo(philo);
		pthread_mutex_lock(philo->rules->death);
	}
}
