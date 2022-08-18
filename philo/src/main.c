/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:31:30 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/08/18 17:34:47 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_usage(void)
{
	printf("Correct usage: ./philo number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
}

int	ft_atoi(const char *str)
{
	int	num;

	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32 || *str == 43)
		++str;
	if (*str == 45)
		return (-1);
	while (*str >= 48 && *str <= 57)
		num = num * 10 + (*(str++) - 48);
	if (*(--str) - 48 != num % 10)
		return (-1);
	return (num);
}

t_table	*create_table(int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = malloc(sizeof(t_table));
	table->n_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		table->number_of_meals = ft_atoi(argv[5]);
	else
		table->number_of_meals = -2;
	if (table->n_philosophers == -1 || table->time_to_die == -1
		|| table->time_to_eat == -1 || table->time_to_sleep == -1
		|| table->number_of_meals == -1)
		return (0);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->n_philosophers);
	i = -1;
	while (++i < table->n_philosophers)
		pthread_mutex_init(&table->fork[i], NULL);
	table->pos = 1;
	return (table);
}

void	*philo_routine(void *table)
{
	(void) table;
	printf("holi\n");
	return (0);
}

void	init_table(t_table *table)
{
	pthread_t	*philo;
	int			i;

	philo = malloc(sizeof(pthread_t) * table->n_philosophers);
	i = -1;
	while (++i < table->n_philosophers)
		pthread_create(&philo[i], NULL, &philo_routine, (void *)table);
	i = -1;
	while (++i < table->n_philosophers)
		pthread_join(philo[i], NULL);
}

int	main(int argc, char **argv)
{
	t_table		*table;

	if (argc < 5 || argc > 6)
	{
		print_usage();
		return (0);
	}
	table = create_table(argc, argv);
	if (!table)
	{
		printf("Error while parsing arguments.\n");
		return (0);
	}
	init_table(table);
	return (0);
}
