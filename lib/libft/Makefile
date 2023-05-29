# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 11:10:43 by omoreno-          #+#    #+#              #
#    Updated: 2023/05/09 18:24:12 by omoreno-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strncmp.c\
	ft_memset.c\
	ft_bzero.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_memchr.c\
	ft_strnstr.c\
	ft_atoi.c\
	ft_calloc.c\
	ft_strdup.c\
	ft_substr.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_split.c\
	ft_itoa.c\
	ft_strmapi.c\
	ft_striteri.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c

SRCB = ft_lstnew_bonus.c\
	ft_lstadd_front_bonus.c\
	ft_lstsize_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstadd_back_bonus.c\
	ft_lstdelone_bonus.c\
	ft_lstclear_bonus.c\
	ft_lstiter_bonus.c\
	ft_lstmap_bonus.c

OBJ := $(SRC:.c=.o)
OBJB := $(SRCB:.c=.o)
DEPS = $(SRC:.c=.d)
DEPSB = $(SRCB:.c=.d)
CC	= 	gcc
CFLAGS = -Wall -Werror -Wextra -MMD -MP
RM	= 	rm -f
LIBC	= 	ar -rcs
HEADER = libft.h

%.o : %.c ${HEADER}
	@${CC} ${CFLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}
	@echo "compiled $(NAME) file: <$(notdir $<)>"

all : $(NAME) 

-include: $(DEPS)
$(NAME) : $(OBJ) $(HEADER)
	@$(LIBC) $(NAME) $(OBJ)
	@echo "compiled $(NAME) file: <$(notdir $<)>"

-include: $(DEPS) $(DEPSB)
bonus: $(OBJ) $(OBJB) $(HEADER)
	@$(LIBC) $(NAME) $(OBJ) $(OBJB)
	@touch $@

clean :
	@$(RM) $(OBJ)
	@$(RM) $(OBJB)
	@$(RM) $(DEPS)
	@$(RM) $(DEPSB)
	@echo $(NAME) Cleaned

fclean : clean
	@$(RM) $(NAME)
	@$(RM) bonus
	@echo $(NAME) Fully Cleaned

re: fclean all

.PHONY : clean fclean re all