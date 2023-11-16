# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpiras <tpiras@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 16:48:16 by tpiras             #+#    #+#              #
#    Updated: 2023/09/11 16:48:18 by tpiras            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

LIBFT_PATH = libft

GNL = get_next_line

LIBFT = $(LIBFT_PATH)/libft.a

MAKEFLAGS += --silent

SRC = amain.c\
	ft_mini_split.c \
	ft_mini_split_utils.c \
	ft_mini_split_utils2.c \
	ft_mini_split_utils3.c \
	lists.c \
	parser.c \
	parser2.c \
	parser3.c \
	parser_utils.c \
	parser_utils2.c \
	parser_utils3.c \
	test_input.c \
	test_input2.c \
	test_input3.c \
	expander.c \
	lists_utils.c \
	wildcats.c \
	wildcats2.c \
	wildcats3.c \
	builtin_ctrl.c \
	builtin_exec.c \
	export_unset.c \
	export_utils.c \
	general_utils.c \
	signal.c \
	$(GNL)/get_next_line.c \
	$(GNL)/get_next_line_utils.c \
	builtin_pipe.c \
	ft_echo_split.c \
	echo_replacer.c \
	echo_replacer2.c \
	echo_utils.c  \
	pipe.c \
	pipe_utils.c  \
	pipe_utils2.c \
	matrix_utils.c \
	export_argu.c \
	export_unset2.c \
	echo_replacer_utils.c \
	
OBJ = ${SRC:.c=.o}

CC = gcc

RM = rm -f

CFLAGS = -W -W -W -g


.o:.c
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:  ${OBJ}
	make -C $(LIBFT_PATH)
	${CC} $(CFLAGS) ${OBJ} ${LIBFT} -lreadline -o $(NAME)
	@echo "\033[31m	       (         )   (         )         (      (     \033[0m"  
	@echo "\033[31m(        )\ )   ( /(   )\ )   ( /(         )\ )   )\ ) \033[0m"   
	@echo "\033[31m)\))(   (()/(   )\()) (()/(   )\())  (    (()/(  (()/( \033[0m"   
	@echo "\033[31m((_)()\   /(_)) ((_)\   /(_)) ((_)\   )\    /(_))  /(_)) \033[0m"  
	@echo "\033[31m(_()((_) (_))    _((_) (_))    _((_) ((_)  (_))   (_))    \033[0m" 
	@echo "\033[31m|  \/  | |_ _|  | \| | |_ _|  | || | | __| | |    | |     \033[0m" 
	@echo "\033[31m| |\/| |  | |   | .  |  | |   | __ | | _|  | |__  | |__   \033[0m" 
	@echo "\033[31m|_|  |_| |___|  |_|\_| |___|  |_||_| |___| |____| |____|   \033[0m"
	@echo "\033[31m                                                          \033[0m"
	@echo "\033[31m PERDETE OGNI SPERANZA O VOI CHE PROGRAMMATE!\033[0m"
	
all: ${NAME}

clean:
		${RM} ${OBJ}
		make clean -C ${LIBFT_PATH}
		@echo "\033[35mCleared everything!\033[0m"

fclean: clean
		make fclean -C ${LIBFT_PATH}
		${RM} ${NAME}

re: fclean all