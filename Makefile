
NAME = minishell

CC = cc
C_FLAGS = -Wall -Wextra -Werror

LFT_PATH = ./libraries/libft/
LFT_INC_PATH = ./libraries/libft/includes/
OBJ_PATH = ./objs/
INC_PATH = ./includes/
SRC_PATH = ./srcs/

LFT_NAME = libft.a
OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = minishell.h
SRC_NAME = minishell.c ms_parse.c ms_utils/ms_clear_node.c \
	   ms_utils/ms_parse_split.c ms_treat_line.c \
	   ms_utils/ms_add_variable.c \
	   ms_exec_line.c ms_utils/ms_build_env.c \
	   ms_pwd/ms_cmd_pwd.c ms_cd/ms_cmd_cd.c \
	   ms_echo/ms_cmd_echo.c ms_env/ms_cmd_env.c \
	   ms_exit/ms_cmd_exit.c ms_export/ms_cmd_export.c \
	   ms_unset/ms_cmd_unset.c ms_exec/ms_cmd_exec.c

LFT = $(addprefix $(LFT_PATH),$(LFT_NAME))
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LFT_INC = $(addprefix -I,$(LFT_INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LFT_PATH)
	@$(CC) -o $@ -L $(LFT_PATH) -lft $^
	@echo "Obj folder & files created"
	@echo "Executable created"
	@echo "Compilation finished"

$(OBJ): | $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(C_FLAGS) $(INC) $(LFT_INC) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)ms_utils/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ms_pwd/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ms_cd/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ms_echo/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ms_env/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ms_exit/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ms_export/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ms_unset/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ms_exec/ 2> /dev/null || true

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
