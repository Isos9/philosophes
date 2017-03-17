/*
** actions.c for actions in /home/marwane/Projets/Epitech/C/PSU/PSU_2016_philo/src
** 
** Made by Marwane
** Login   <marwane.khsime@epitech.eu>
** 
** Started on  Fri Mar 17 01:03:58 2017 Marwane
** Last update Fri Mar 17 07:29:31 2017 Marwane
*/

#include "../includes/extern.h"
#include "../includes/philosophers.h"

void	philoThink(t_philo *philosopher) {
  int whichChopstick;

  if ((whichChopstick = 0 && philosopher->lastAction != THINK && pthread_mutex_trylock(&philosopher->table->bowls[philosopher->id]) == 0) ||
      (whichChopstick = 1 && philosopher->lastAction != THINK && pthread_mutex_trylock(&philosopher->table->bowls[(philosopher->id + 1) % philosopher->table->nbPhilos]) == 0)) {

    lphilo_take_chopstick(&philosopher->table->bowls[(philosopher->id + whichChopstick) % philosopher->table->nbPhilos]);
    lphilo_think();

    philosopher->lastAction = THINK;
    usleep(philosopher->timeToThink);

    pthread_mutex_unlock(&philosopher->table->bowls[(philosopher->id + whichChopstick) % philosopher->table->nbPhilos]);
    lphilo_release_chopstick(&philosopher->table->bowls[(philosopher->id + whichChopstick) % philosopher->table->nbPhilos]);
  }
}

void	philoEat(t_philo *philosopher) {
  int	right;
  int	left;

  if ((right = pthread_mutex_trylock(&philosopher->table->bowls[(philosopher->id + 1) % philosopher->table->nbPhilos])) == 0 &&
      (left = pthread_mutex_trylock(&philosopher->table->bowls[philosopher->id])) == 0) {

    lphilo_take_chopstick(&philosopher->table->bowls[philosopher->id]);
    lphilo_take_chopstick(&philosopher->table->bowls[(philosopher->id + 1) % philosopher->table->nbPhilos]);
    lphilo_eat();

    usleep(philosopher->timeToThink);
    ++philosopher->nbMeals >= philosopher->table->mealsLimit ? philosopher->table->limitReached = true : 0;
    philosopher->lastAction = EAT;

    pthread_mutex_unlock(&philosopher->table->bowls[philosopher->id]);
    pthread_mutex_unlock(&philosopher->table->bowls[(philosopher->id + 1) % philosopher->table->nbPhilos]);
    lphilo_release_chopstick(&philosopher->table->bowls[philosopher->id]);
    lphilo_release_chopstick(&philosopher->table->bowls[(philosopher->id + 1) % philosopher->table->nbPhilos]);

  }

  else {
    if (right == 0) {
      lphilo_take_chopstick(&philosopher->table->bowls[(philosopher->id + 1) % philosopher->table->nbPhilos]);
      pthread_mutex_unlock(&philosopher->table->bowls[(philosopher->id + 1) % philosopher->table->nbPhilos]);
      lphilo_release_chopstick(&philosopher->table->bowls[(philosopher->id + 1) % philosopher->table->nbPhilos]);
    }
    if (left == 0) {
      lphilo_take_chopstick(&philosopher->table->bowls[philosopher->id]);
      pthread_mutex_unlock(&philosopher->table->bowls[philosopher->id]);
      lphilo_release_chopstick(&philosopher->table->bowls[philosopher->id]);
    }
  }
}

void	philoSleep(t_philo *philosopher) {
  lphilo_sleep();
  usleep(philosopher->timeToSleep);
  philosopher->lastAction = SLEEP;
}
