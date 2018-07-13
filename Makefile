# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/12 17:06:00 by rsibiet           #+#    #+#              #
#    Updated: 2016/01/20 18:50:30 by rsibiet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FTC = ft_ls.c \
	  dp_ls.c \
	  dp_ls2.c \
	  dp_lls.c \
	  ls_data.c \
	  l_spaces.c \
	  l_space_two.c \
	  finish_to_sort.c \
	  ls_recursive.c \
	  ls_final_recursive.c \
	  ls_special_device.c \
	  cut_to_norme_ls.c \
	  ls_error.c

FTO = $(subst .c,.o,$(FTC))

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(FTO)
	@echo ""
	@make -C ./libft
	@gcc -o $(NAME) $(FTO) ./libft/libft.a
	@echo "\033[32m$(NAME) created!\033[0m"

%.o: %.c
	@gcc -Wall -Wextra -Werror -I./libft/ -c $<
	@echo "\033[33m.\033[0m\c"

clean:
	@make -C ./libft clean
	@rm -rf $(FTO)
	@echo "\033[33m$(NAME) object deleted!\033[0m"

fclean: clean
	@make -C ./libft fcleana
	@rm -rf $(NAME)
	@echo "\033[31m$(NAME) deleted!\033[0m"

re: fclean all
