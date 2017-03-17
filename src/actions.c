/*
** actions.c for actions in /home/marwane/Projets/Epitech/C/PSU/PSU_2016_philo/src
** 
** Made by Marwane
** Login   <marwane.khsime@epitech.eu>
** 
** Started on  Fri Mar 17 01:03:58 2017 Marwane
** Last update Fri Mar 17 03:36:37 2017 Marwane
*/

#include "../includes/philosophers.h"

void	philoThink(t_philo *philosopher, int whichChopstick) {
  printf("philosopher %d thinks\n", philosopher->id);
  sleep(philosopher->timeToThink);
  pthread_mutex_unlock(&philosopher->table->bowls[philosopher->id + whichChopstick]);
}

void	philoEat(t_philo *philosopher) {
  printf("philosopher %d eats\n", philosopher->id);
  sleep(philosopher->timeToThink);
  ++philosopher->nbMeals >= philosopher->table->mealsLimit ? philosopher->table->limitReached = true : 0;
  philosopher->lastAction = EAT;
  pthread_mutex_unlock(&philosopher->table->bowls[philosopher->id]);
  pthread_mutex_unlock(&philosopher->table->bowls[(philosopher->id + 1) % philosopher->table->nbPhilos]);
}

void	philoSleep(t_philo *philosopher) {
  printf("philosopher %d sleeps\n", philosopher->id);
  sleep(philosopher->timeToSleep);
  philosopher->lastAction = SLEEP;
}
