/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:31:30 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/10/05 20:14:35 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_philo(int argc, char **argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->n_philosophers = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->pos = 0;
	if (argc > 5)
		philo->number_of_meals = ft_atoi(argv[5]);
	else
		philo->number_of_meals = -2;
	if (philo->n_philosophers == -1 || philo->time_to_die == -1
		|| philo->time_to_eat == -1 || philo->time_to_sleep == -1
		|| philo->number_of_meals == -1)
	{
		free(philo);
		return (0);
	}
	sem_unlink("FORKS");
	sem_unlink("PRINT");
	sem_unlink("LOCK");
	return (philo);
}

void	error_exit(int error, t_philo *philo)
{
	if (!error)
	{
		printf("Correct usage: ./philo number_of_philosophers ");
		printf("time_to_die time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
	}
	else if (error == 1)
		printf("Error while parsing arguments.\n");
	else if (error == 2)
		printf("Error while creating processes.\n");
	if (philo)
	{
		free(philo);
		sem_close(philo->forks);
		sem_close(philo->print);
		sem_close(philo->lock);
	}
	exit(1);
}

void	wait_and_finish(t_philo *philo, int *pid)
{
	int	i;
	int	status;
	int	dead_process;

	while (philo->n_philosophers)
	{
		dead_process = waitpid(0, &status, 0);
		if (WEXITSTATUS(status) == 2)
			--philo->n_philosophers;
		else
		{
			i = -1;
			while (++i < philo->n_philosophers)
				if (dead_process != pid[i])
					kill(pid[i], SIGINT);
			break ;
		}
	}
	sem_close(philo->forks);
	sem_close(philo->print);
	sem_close(philo->lock);
	free(philo);
	free(pid);
}

int	main_process(t_philo *philo)
{
	int	i;
	int	*pid;

	pid = malloc(sizeof(int) * philo->n_philosophers);
	philo->forks = sem_open("FORKS", O_CREAT, 0777,
			philo->n_philosophers);
	philo->print = sem_open("PRINT", O_CREAT, 0777, 1);
	philo->lock = sem_open("LOCK", O_CREAT, 0777, 1);
	i = -1;
	gettimeofday(&philo->g_start, NULL);
	while (++i < philo->n_philosophers)
	{
		philo->pos++;
		pid[i] = fork();
		if (!pid[i])
			philo_routine(philo);
		else if (pid[i] == -1)
		{
			free(pid);
			return (1);
		}
	}
	wait_and_finish(philo, pid);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*default_philo;

	if (argc < 5 || argc > 6)
		error_exit(0, 0);
	default_philo = create_philo(argc, argv);
	if (!default_philo)
		error_exit(1, 0);
	if (main_process(default_philo))
		error_exit(2, default_philo);
	return (0);
}
