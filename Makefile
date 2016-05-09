##
## Makefile for make in /home/peau_c/rendu/PSU/minishell/PSU_2015_minishell1
##
## Made by Clement Peau
## Login   <peau_c@epitech.net>
##
## Started on  Thu Jan  7 16:17:02 2016 Clement Peau
## Last update Mon May  9 14:22:06 2016 marel_m
##

DEBUG=	yes

SRC=	main.c			\
	epur.c			\
	check_home.c		\
	check_oldpwd.c		\
	check_path.c		\
	check_pwd.c		\
	env.c			\
	my_get_next_line.c	\
	my_str_to_word_tab.c	\
	my_strdup_e.c		\

OBJ=	$(addprefix src/, $(SRC:.c=.o))

RM=	rm -f

ifeq ($(DEBUG), yes)
	CFLAGS=		-W -Wall -Wextra -g -D DEBUG -O0
	CC=		clang
else
	CFLAGS=		-W -Wall -Wextra -Werror
	CC=		gcc
endif

NAME=	mysh

HEAD=	-I inc/

$(NAME):                $(OBJ)
ifeq ($(DEBUG), yes)
	@tput setaf 1; tput bold
	@echo " ____________________ ________________________   ____ ___._________________";
	@echo "/   _____/\_   _____|/  _____/\_   _____/  _  \ |    |   \    | \__    ___/";
	@echo "\_____  \  |    ___|/   \  ___ |    __)/  / \  \|    |   /    |   |    |";
	@echo "/        \ |        \    \_\  \|     \/    |    \    |  /|    |___|    |";
	@echo "/________//_________/\________/\_____/\____|____/______/ |________|____|";
	@tput sgr0
	rm -rf TAGS
	find . -type f -iname "*.[chS]" | xargs etags -a
endif
	@ echo "CC = $(CC)"
	@ echo "CFLAGS = $(CFLAGS)"
	@ $(CC) $(OBJ) -o $(NAME)
	@ echo -e "\033[1;31m \t \t \n \t ♩♪♫ $(NAME) Compiled\033[0;31m®\033[1;31m Created Sucesfully \033[0m"

all:		$(NAME)

clean:
		@ $(RM) $(OBJ)
		@ echo "[ OK ] clean sucessfull"
fclean: clean
		@ $(RM) $(NAME)
		@ echo "[ OK ] fclean succesfull"

re:	fclean all
%.o:                    %.c
			@ echo "[ OK ] Compiling" $<
			@ $(CC) -o $@ -c $< $(CFLAGS) $(HEAD)
