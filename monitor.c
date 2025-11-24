/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:50:47 by nour              #+#    #+#             */
/*   Updated: 2025/11/24 12:02:00 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_to_die_exceeded(t_rules *rules)
{
	int			i;
	long long	time;

	i = 0;
	while (rules->finish_all && i < rules->philo_amount)
	{
		pthread_mutex_lock(rules->print);
		time = get_time() - rules->start_time;		
		if (time > rules->t_to_die)
		{
			dying(rules->philos[i]);
			pthread_mutex_lock(rules->death);
			rules->finish_all = 1;
			pthread_mutex_unlock(rules->death);
		}
		pthread_mutex_unlock(rules->print);
		i++;
	}
}

void	all_have_eaten(t_rules *rules)
{
	int	i;

	i = 0;
	while (rules->finish_all && i < rules->philo_amount)
	{
		pthread_mutex_lock(rules->print);		
		if (rules->philos[i]->meals >= rules->must_eat)
		{
			pthread_mutex_lock(rules->death);
			rules->finish_all = 1;
			pthread_mutex_unlock(rules->death);
		}
		pthread_mutex_unlock(rules->print);
		i++;
	}
}

void	*monitor_thread(void *arg)
{
	t_rules *rules;

	rules = (t_rules *)arg;
	while (1)
	{
		t_to_die_exceeded(rules);
		all_have_eaten(rules);
	}
	return ((void *)rules);
}
