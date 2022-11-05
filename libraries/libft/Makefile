
NAME = libft.a

CC = cc
C_FLAGS = -Wall -Wextra -Werror

OBJ_PATH = ./objs/
INC_PATH = ./includes/
SRC_PATH = ./srcs/

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_NAME = ft_atoi.c ft_strdup.c ft_bzero.c ft_putnbr_fd.c ft_strjoin.c \
	   	ft_calloc.c ft_strlcat.c ft_isalnum.c ft_strlcpy.c \
		ft_isalpha.c ft_memccpy.c ft_strlen.c ft_isascii.c ft_memchr.c \
		ft_strmapi.c ft_isdigit.c ft_memcmp.c ft_strncmp.c ft_strcmp.c \
		ft_isprint.c ft_memcpy.c ft_strnstr.c ft_isspace.c \
		ft_memmove.c ft_strrchr.c ft_itoa.c ft_memset.c ft_strtrim.c \
		ft_putchar_fd.c ft_substr.c ft_putendl_fd.c ft_tolower.c \
		ft_putstr_fd.c ft_toupper.c ft_split.c ft_strchr.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c ft_putmem_fd.c ft_putnbr_base_fd.c ft_atoi_base.c \
		ft_abs.c ft_swap.c get_next_line.c \


SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $@ $(OBJ)
	@echo "Obj folder & files created"
	@echo "Executable created"
	@echo "Compilation finished"

$(OBJ): | $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)ft_printf/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ft_printf/ft_format_functions/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ft_printf/ft_flag_functions/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ft_printf/utils/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)ft_printf/utils/double/ 2> /dev/null || true

clean:
	@rm -rf $(OBJ_PATH) 2> /dev/null || true
	@echo "Obj folder & files suppressed"

fclean: clean
	@rm -f $(NAME)
	@echo "Executable suppressed"

re: fclean
	@$(MAKE) all

norme:
	@norminette $(SRC)
	@echo "norme check finished"
