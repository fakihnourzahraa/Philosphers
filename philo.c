/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:55:36 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/22 15:03:22 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	take_forks(t_philosophers **philos)
{

}

void	think(t_philosophers *philo)
{
	
}

void	*philos_routine(void *arg)
{
	t_philosophers *philo;

	philo = (t_philosophers *)arg;

	think(philo);
	take_forks(philo);
	eat(philo);
	put_down_forks(philo);
	sleep_philo(philo);

}