/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:55:36 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/23 14:34:37 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	take_forks(t_philosophers *philo)
{
	long long time;
	
	time = get_time() - philo->rules->start_time;
	printf("%lld %d has taken a fork", time, philo->pid);
	
}

void	think(t_philosophers *philo)
{
	long long time;
	
	time = get_time() - philo->rules->start_time;
	printf("%lld %d is thinking", time, philo->pid);
	
}

void	sleep(t_philosophers *philo)
{	
	long long time;
	
	time = get_time() - philo->rules->start_time;
	printf("%lld %d is sleeping", time, philo->pid);
	
}
void	dying(t_philosophers *philo)
{
	long long time;
	
	time = get_time() - philo->rules->start_time;
	printf("%lld %d died", time, philo->pid);
	
}
void	eating(t_philosophers *philo)
{
	long long time;
	
	time = get_time() - philo->rules->start_time;
	printf("%lld %d is eating", time, philo->pid);
}
void	*philos_routine(void *arg)
{
	t_philosophers *philo;

	think(philo);
	take_forks(philo);
	eat(philo);
	put_down_forks(philo);
	sleep_philo(philo);

}