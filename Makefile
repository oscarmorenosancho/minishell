# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 19:22:02 by edomingu          #+#    #+#              #
#    Updated: 2023/05/26 18:48:00 by omoreno-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

MKF			=	Makefile

SRC_DIR		=	src
INC_DIR		=	include
LIB_DIR		=	lib
LIBFT_DIR	=	$(LIB_DIR)/libft
# RLDIR		=	/Users/$(USER)/localbin/homebrew/opt/readline/include
ifeq ($(USER), edomingu)
	RLDIR	=	/Users/$(USER)/localbin/homebrew/opt/readline/include
else
	RLDIR	=	/Users/$(USER)/.brew/opt/readline/include
endif
BUILD_DIR	=	.build

FILES		=	utils.c \
				checks.c \
				checks2.c \
				free.c \
				cmd_list.c \
				cmd_info.c \
				cmd_exe.c \
				envl_manage.c \
				redir_info.c \
				matrix_utils.c \
				str_utils.c \
				redirect_open.c \
				user_input.c \
				prepare_redir.c \
				parser.c \
				read.c \
				read2.c \
				constants.c \
				path_utils.c \
				handlers.c \
				redir_utils.c \
				file_checker.c \
				wait.c \
				cmd_info_exe.c \
				env_utils.c \
				read_utils.c \
				cmd_info_utils.c \
				built_in_env.c \
				built_in_exit.c \
				built_in_export.c \
				built_in_pwd.c \
				built_in_unset.c \
				built_in_none.c \
				built_in_echo.c \
				built_in_cd.c \
				cmd_exit.c \
				ft_expand_status.c \
				cmd_list_utils.c \
				path_utils2.c \
				ft_increase_shlvl.c \
				expand_env_vars_heredoc.c \
				ft_strlen_safe.c \
				ft_chdir.c \
				dup_utils.c \
				ft_split_safe.c \
				atoli_aux.c \
				atoli.c \
				env_var_utils.c \
				env_var_utils2.c \
				env_var.c \
				env_var2.c \
				env_var3.c \
				list_utils.c \
				open_redir.c \
				ft_dup2.c \
				ft_close.c

FILES 		:=	$(FILES) main.c

SRC			=	$(addprefix $(SRC_DIR)/, $(FILES))
OBJS		=	$(addprefix $(BUILD_DIR)/, $(FILES:.c=.o))
DEPS		=	$(addprefix $(BUILD_DIR)/, $(FILES:.c=.d))

LIB_A 		=	$(LIBFT_DIR)/libft.a

GCC			=	gcc
RM			=	rm -rf

FLAGS		=	-Werror -Wextra -Wall -MMD
# LDFLAGS		=	-L/Users/$(USER)/localbin/homebrew/opt/readline/lib
ifeq ($(USER), edomingu)
	LDFLAGS	=	-L/Users/$(USER)/localbin/homebrew/opt/readline/lib
else
	LDFLAGS	=	-L/Users/$(USER)/.brew/opt/readline/lib
endif

#-fsanitize=address

INCLUDE		=	-I $(INC_DIR) -I $(LIBFT_DIR) -I $(RLDIR) # /$(INC_DIR)

GSU			=	git submodule update
GSU_FLAGS	=	--remote --merge --recursive

all:
		@$(MAKE) $(NAME)

clean:
		@$(MAKE) clean -C $(LIBFT_DIR)
		@$(RM) $(BUILD_DIR)
		@echo $(NAME) Cleaned

fclean:
		@$(MAKE) fclean -C $(LIBFT_DIR)
		@$(RM) minishell.dSYM/
		@$(RM) $(BUILD_DIR)
		@$(RM) $(NAME)
		@echo $(NAME) Fully Cleaned

update:
		$(GSU) $(GSU_FLAGS)

re:
		@$(MAKE) fclean
		@$(MAKE) all

$(NAME): $(BUILD_DIR) $(OBJS) $(LIB_A)
		@$(GCC) $(FLAGS) $(LDFLAGS) -lreadline $(OBJS) $(LIB_A) -o $(NAME)

$(LIB_A):
		@$(MAKE) bonus -C $(LIBFT_DIR)

$(BUILD_DIR):
		@mkdir -p -m700 $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(LIB_A) $(MKF)
		@$(GCC) $(FLAGS) $(INCLUDE) -c $< -o $(BUILD_DIR)/$(notdir $@)
		@echo "compiled $(NAME) file: <$(notdir $<)>"

-include $(DEPS)

.PHONY:	all update clean fclean re