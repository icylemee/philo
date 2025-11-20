
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
LDLIBS = -pthread

SRCS = main.c \
	simu/ft_start_simulation.c \
	simu/simu_bis.c \
	ft_monitor.c \
	cleaning/ft_clean_data.c \
	parsing/ft_atol.c \
	parsing/parsing.c \
	utils/ft_get_time.c \
	utils/ft_strncmp.c \

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
