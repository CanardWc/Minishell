
NAME = minishell

CC = cc
C_FLAGS = -Wall -Wextra -Werror

LFT_PATH = ./libraries/libft/
LFT_INC_PATH = ./libraries/libft/includes/
OBJ_PATH = ./objs/
INC_PATH = ./includes/
SRC_PATH = ./srcs/

RL_LIB = -L$(shell brew --prefix readline)/lib
RL_INC = -I$(shell brew --prefix readline)/include

LFT_NAME = libft.a
OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = minishell.h
SRC_NAME = minishell.c ms_utils/ms_clear_node.c \
	   ms_parsing/ms_parsing.c ms_signal.c \
	   ms_parsing/ms_pipes.c ms_parsing/ms_redirections.c \
	   ms_parsing/ms_in.c ms_parsing/ms_out.c \
	   ms_utils/ms_build_env.c ms_utils/ft_subsubstr.c \
	   ms_parsing/ms_replace_variables.c ms_parsing/ms_split.c\
	   ms_parsing/ms_remove_quotes.c \
	   ms_parsing/ms_add_variables.c \
	   ms_parsing/ms_flush_variables.c \
	   ms_logic/ms_logic.c ms_logic/ms_find_cmd.c \
	   ms_builtins/ms_cmd_cd.c ms_builtins/ms_cmd_echo.c \
	   ms_builtins/ms_cmd_env.c ms_builtins/ms_cmd_exec.c \
	   ms_builtins/ms_cmd_exit.c ms_builtins/ms_cmd_export.c \
	   ms_builtins/ms_cmd_pwd.c ms_builtins/ms_cmd_unset.c 

LFT = $(addprefix $(LFT_PATH),$(LFT_NAME))
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LFT_INC = $(addprefix -I,$(LFT_INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LFT_PATH)
	@$(CC) -fsanitize=address -g3 -o $@ -L $(LFT_PATH) -lft $^ $(RL_INC) $(RL_LIB) -lreadline
	@echo "Obj folder & files created"
	@echo "Executable created"
	@echo "Compilation finished"

$(OBJ): | $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(C_FLAGS)  -fsanitize=address -g3 $(INC) $(LFT_INC) -o $@ -c $< $(RL_INC)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)ms_parsing/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ms_logic/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ms_builtins/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ms_utils/ 2> /dev/null || true

clean:
	@make clean -C $(LFT_PATH)
	@rm -rf $(OBJ_PATH) 2> /dev/null || true
	@echo "Obj folder & files suppressed"

fclean: clean
	@make fclean -C $(LFT_PATH)
	@rm -f $(NAME)
	@echo "Executable suppressed"

re: fclean
	@$(MAKE) all

bonus: all

norme:
	@norminette -R CheckForbiddenSourceHeader $(SRC)
	@echo "C files norme check finished"
	@norminette -R CheckDefine $(INC_PATH)
	@echo "Header files norme check finished"
