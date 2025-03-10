# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lilefebv <lilefebv@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 13:55:49 by lilefebv          #+#    #+#              #
#    Updated: 2025/02/13 12:08:31 by lilefebv         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Program name
NAME     = fdf
BONUS    = fdf_bonus

# Style
GREY     = \033[0;30m
RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
BLUE     = \033[0;34m
PURPLE   = \033[0;35m
CYAN     = \033[0;36m
WHITE    = \033[0;37m

BOLD     = \033[1m
UNDER    = \033[4m
REV      = \033[7m
BLINK    = \033[5m

NC       = \033[0;0m
ERASE    = \033[2K\r
ERASE2   = $(ERASE)\033[F$(ERASE)

# Compiler and flags
CC       = cc
CFLAGS   = -Wall -Wextra -Werror
LDFLAGS  = -L$(MINILIBXDIR) -lXext -lX11 -lm
DEBUG_FLAGS = -g3
FAST_FLAGS = -Ofast

ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += $(DEBUG_FLAGS)
endif
ifeq ($(MAKECMDGOALS), fast)
	CFLAGS += $(FAST_FLAGS)
endif

MODE_FILE = .build_mode

# libs
LIBFTDIR = libft/
LIBFT    = $(LIBFTDIR)libft.a

MINILIBXDIR = minilibx/
MINILIBX    = $(MINILIBXDIR)libmlx_Linux.a

# Includes
INCLUDES = -I includes/ -I $(LIBFTDIR)includes/ -I $(MINILIBXDIR)

# Source files
SRC_DIR  = srcs/
SRCS     = fdf.c console.c utils.c free.c                                                                                                                                       \
           projections/matrix.c projections/matrix_calc.c projections/projection_point.c projections/color_preset.c                                                              \
           rendering/utils.c rendering/pixel.c rendering/frame.c rendering/draw_lines.c rendering/utils_lines.c rendering/draw_string.c rendering/frustum_culling.c               \
		   rendering/lines_algo/anti_aliasing.c rendering/lines_algo/basic_slope.c rendering/lines_algo/bresenham.c rendering/lines_algo/circle.c rendering/lines_algo/rectangle.c \
		   events/actions.c events/hooks.c                                                                                                                                          \
		   env/inits.c env/parsing.c env/map_line.c env/font.c env/init_buttons.c env/save_map.c                                                                                     \
		   camera/calcs.c camera/movements.c camera/key_movements.c                                                                                                                   \
		   edition/move_point.c edition/painter.c edition/select.c                                                                                                                     \
		   components/button.c components/slider_int.c components/text_input.c                                                                                                          \
		   procedural_generation/gen_perlin_noise.c procedural_generation/init_map_procedural.c procedural_generation/biomes.c procedural_generation/utils.c procedural_generation/rivers.c procedural_generation/init_biomes_color.c procedural_generation/init_biomes_height.c
		   

SRCS_BONUS = 

# Object files directory
OBJ_DIR   = .obj/
OBJ       = $(SRCS:%.c=$(OBJ_DIR)%.o)
OBJ_BONUS = $(SRCS_BONUS:%.c=$(OBJ_DIR)%.o)

# Remake all if modified
REMAKE   = libft/includes/libft.h libft/includes/ft_printf.h libft/includes/get_next_line.h libft/Makefile  \
           Makefile includes/fdf.h includes/structs.h includes/components.h

# NORMINETTE
NORM_RET = $(RED)[ERROR]$(BOLD) Norminette Disable$(NC)
# NORM	 = $(shell norminette srcs includes | grep -c 'Error!')
# ifeq ($(NORM), 0)
# 	NORM_RET = $(GREEN)[DONE] $(BOLD)$(YELLOW)Norminette.$(NC)
# else
# 	NORM_RET = $(RED)[ERROR] $(BOLD)$(YELLOW)Norminette.$(NC)
# endif

# Variables for progress bar
TOTAL_FILES		:=	$(words $(SRCS))
MODIFIED_FILES  := $(shell if [ -f $(NAME) ]; then                                                             \
                        if [ `for file in $(REMAKE); do find $$file -newer $(NAME); done | wc -l` -gt 0 ]; then \
                            echo $(TOTAL_FILES);                                                                 \
                        else                                                                                      \
                            for file in $(SRCS); do                                                  \
                                obj_file=$(OBJ_DIR)$${file%.c}.o;                                     \
                                if [ $(SRC_DIR)$$file -nt $(NAME) ] || [ ! -f $$obj_file ]; then       \
                                    echo $$file;                                                        \
                                fi;                                                         \
                            done | wc -l;                                                    \
                        fi;                                                                   \
                    else                                                                       \
						if [ ! -d $(OBJ_DIR) ]; then                                            \
							echo $(TOTAL_FILES);                              \
						else                                                                      \
							for file in $(SRCS); do                                                \
								obj_file=$(OBJ_DIR)$${file%.c}.o;                                   \
								if [ ! -f $$obj_file ] || [ $(SRC_DIR)$$file -nt $$obj_file ]; then  \
									echo $$file;                                                      \
								fi;                                                                    \
                        done | wc -l; fi; fi)

COMPILED_FILES	:=	0
PERCENT			:=	0
BAR_WIDTH		:=	41

REPEAT_CHAR		=	$(if $(filter-out 0,$2),$(shell seq 1 $2 | xargs -I@ printf "$1"),)

# Pattern rule for object files
$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(REMAKE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)
	@$(eval COMPILED_FILES := $(shell expr $(COMPILED_FILES) + 1))
	@if [ $(MODIFIED_FILES) -ne 0 ]; then                                                                               \
		$(eval PERCENT := $(shell echo $$(($(COMPILED_FILES) * 100 / $(MODIFIED_FILES)))))                               \
		$(eval PROGRESS := $(shell echo $$(($(PERCENT) * $(BAR_WIDTH) / 100))))                                           \
		$(eval EMPTY := $(shell echo $$(($(BAR_WIDTH) - $(PROGRESS)))))                                                    \
		printf "$(ERASE2)$(GREEN)[Compiling] $(NC)$(shell echo $< | sed 's|^srcs/||')\n";                                   \
		printf "\n$(YELLOW)[$(call REPEAT_CHAR,⣿,$(PROGRESS))$(call REPEAT_CHAR, ,$(EMPTY))]${NC} ${NC}${PERCENT}%%${NC}\r"; \
	fi

all : libft_make mlx_make start_message $(NAME)

start_message:
	@if [ ! -f $(NAME) ] || [ $(MODIFIED_FILES) != 0 ]; then \
		echo "\n$(YELLOW)╔══════════════════════════════════════════════╗$(NC)";                                                                             \
		echo "$(YELLOW)║         Starting $(YELLOW2)$(NAME)$(YELLOW) compilation...          ║$(NC)";                                                              \
		echo "$(YELLOW)╚══════════════════════════════════════════════╝$(NC)\n\n";                                                                             \
	else                                                                                                                                                     \
		echo "\n$(YELLOW)╔══════════════════════════════════════════════╗$(NC)";                                                                             \
		echo "$(YELLOW)║         Nothing to be done for $(YELLOW2)$(NAME)$(YELLOW).          ║$(NC)";                                                              \
		echo "$(YELLOW)╚══════════════════════════════════════════════╝$(NC)\n";                                                                             \
	fi

end_message:
	@echo "\n$(PURPLE)          $(WHITE)__..--''\`\`---....___   _..._    __$(PURPLE) ________$(NC)"
	@echo "$(PURPLE)  / //$(WHITE)_.-'    .-/\";  \`        \`\`<._  \`\`.''_ \`.$(PURPLE) / // /|$(NC)"
	@echo "$(PURPLE) //$(WHITE)_.-' _..--.'_    \\                    \`( ) )$(PURPLE) / // |$(NC)"
	@echo "$(PURPLE)/ $(WHITE)(_..-' $(PURPLE)// $(WHITE)(< _     ;_..__               ; \`'$(PURPLE) / //  |$(NC)"
	@echo "$(PURPLE)/ // // //  $(WHITE)\`-._,_)' $(PURPLE)// /$(WHITE) \`\`--...____..-'$(PURPLE) /// / /  F |$(NC)"
	@echo "$(PURPLE)╔══════════════════════════════════════════════╗  d  |$(NC)"
	@echo "$(PURPLE)║ $(BLUE)Une carte ? Des points ? Peux importe, tant  $(PURPLE)║ F  /$(NC)"
	@echo "$(PURPLE)║ $(BLUE)qu'il y a des fils un chat sera heureux !    $(PURPLE)║   /$(NC)"
	@echo "$(PURPLE)║ $(GREEN)       $(BLINK)> $(WHITE)FdF successfully compiled! $(GREEN)$(BLINK)<        $(PURPLE)║  /$(NC)"
	@echo "$(PURPLE)╚══════════════════════════════════════════════╝/$(NC)"
	@echo "\n$(NORM_RET)";

$(NAME) : ${LIBFT} $(OBJ)
	@echo "\n\n$(GREEN)[Compiling program] $(NC)$(NAME)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MINILIBX) $(LDFLAGS)
	@make --no-print-directory end_message

libft_make:
	@make --no-print-directory -C $(LIBFTDIR) all

mlx_make:
	@if [ ! -f $(MINILIBX) ]; then \
		make --no-print-directory -C $(MINILIBXDIR) all; \
	fi

mlx_re:
	@make --no-print-directory -C $(MINILIBXDIR) re

mlx_clean:
	@make --no-print-directory -C $(MINILIBXDIR) clean

clean :
	@make --no-print-directory -C $(LIBFTDIR) clean
	@echo "$(RED)[Removing] $(NC)object files"
	@rm -rf $(OBJ_DIR)

fclean : clean
	@make --no-print-directory -C $(LIBFTDIR) fclean
	@if [ -f $(NAME) ]; then \
		echo "$(RED)[Removing] $(NC)program $(NAME)"; \
		rm -f $(NAME); \
	fi
	
clean_fdf_only :
	@echo "$(RED)[Removing] $(NC)object files"
	@rm -rf $(OBJ_DIR)
	
fclean_fdf_only : clean_fdf_only
	@if [ -f $(NAME) ]; then \
		echo "$(RED)[Removing] $(NC)program $(NAME)"; \
		rm -f $(NAME); \
	fi

re : fclean
	@make --no-print-directory all

fast: all

debug: all 

ffast: fclean_fdf_only
	@make --no-print-directory fast

fdebug: fclean_fdf_only
	@make --no-print-directory debug

norminette:
	@norminette srcs/ libft/ includes/


.PHONY: all clean fclean clean_fdf_only fclean_fdf_only re start_message end_message libft_make mlx_make mlx_re mlx_clean norminette
