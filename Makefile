NAME = libftprintf.a

CYAN_CLR = \x1b[36m
GRN_CLR  = \x1b[32m
NO_CLR	 = \x1b[00m
WRN_CLR	 = \x1b[31m
HDR_PR = NO

LIB_DIR = libft/
OBJ_DIR = obj/
INC_DIR = includes/

SRC_DIR = src/
SRC_FILES =	ft_printf.c\
			error.c\
      flags.c\
      flags_help.c\
			flag_x.c\
			flag_f.c\
			flag_lf.c\
			flag_o.c\
			flag_di.c\
			flag_u.c\
			flag_s.c\
			flag_c.c\
			flag_size.c\
			flag_color.c\
      flag_valid.c\
			util.c\
			buffun.c\
			offpre.c\
			calculator.c\


HEADERS = $(INC_DIR)ft_printf.h $(LIB_DIR)libft.h

OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC = -I $(INC_DIR) -I $(LIB_DIR)

all: $(NAME)

$(NAME): $(HEADERS) $(OBJ_DIR) $(OBJ)
	@$(MAKE) -C $(LIB_DIR)/
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\n$(GRN_CLR)FT_PRINFT SUCCESS!$(NO_CLR)\n"

$(OBJ_DIR):
	@mkdir obj

#ALL_SRC_DIRS = $(SRC_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) Makefile
	@if [ "$(HDR_PR)" = "NO" ]; then \
		printf "\n$(CYAN_CLR)BUILD STAUS:$(NO_CLR)\n\n"; \
		$(eval HDR_PR = YES) \
	fi
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@printf "$(NO_CLR)$(notdir $<)"
	@printf "$(GRN_CLR)✓$(NO_CLR)\n"

clean:
	@echo "Cleaning" [ $(OBJ_DIR) ] "..." "$(GRN_CLR)OK"
	@$(MAKE) -C $(LIB_DIR)/ clean
	@rm -rf $(OBJ_DIR)*
	@printf "$(GRN_CLR)FT_PRINTF $(NO_CLR)object files have been $(WRN_CLR)Removed!\n"

fclean: clean
	@echo "$(NO_CLR)Cleaning" [ $(NAME) ] "..." "$(GRN_CLR)OK"
	@$(MAKE) -C $(LIB_DIR)/ fclean
	@rm -rf $(NAME)
	@printf "$(NO_CLR)$(NAME) have been $(WRN_CLR)Removed!\n"


re: fclean all

norm:
	@norminette $(SRC) $(HEADERS)
