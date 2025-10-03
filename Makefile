NAME		=	cub3D
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -Ofast
RM			=	rm -rf

# -----------------------------------------------------------------------------
# Directories
SRC_DIR		=	src
OBJ_DIR		=	obj
INC_DIR		=	include

MLX_DIR		=	../MLX42
MLX_BUILD	=	$(MLX_DIR)/build
MLX_LIB		=	$(MLX_BUILD)/libmlx42.a
MLX_INC		=	-I$(MLX_DIR)/include
MLX_LIBS	=	-L$(MLX_BUILD) -lmlx42 -lglfw -ldl -lpthread -lm

LIBFT_DIR	=	libft
LIBFT_LIB	=	$(LIBFT_DIR)/libft.a
LIBFT_INC	=	-I$(LIBFT_DIR) -I$(LIBFT_DIR)/inc

# -----------------------------------------------------------------------------
# Sources
SRC_FILES	=	main.c utils.c \
				file_io/file_io.c \
				parse_entry/parse_entry.c parse_entry/parse_entry_utils1.c parse_entry/parse_entry_utils2.c \
				parse_config/parse_config.c parse_config/parse_config_utils1.c parse_config/parse_config_utils2.c \
				parse_map/parse_map.c parse_map/parse_map_utils1.c parse_map/parse_map_utils2.c \
				validate_map/validate_map.c validate_map/validate_map_utils1.c validate_map/validate_map_utils2.c \
				game/game.c game/map.c game/textures.c game/utils.c game/reycast/reycast.c game/reycast/rey_util.c \
				game/reycast/rey_draw.c game/reycast/rey_tex.c

SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADERS		=	$(INC_DIR)/*.h

# -----------------------------------------------------------------------------
# Colors
GREEN		=	\033[1;32m
CYAN		=	\033[1;36m
YELLOW		=	\033[1;33m
RED			=	\033[1;31m
BLUE		=	\033[1;34m
RESET		=	\033[0m

# Progress
TOTAL_FILES		:=	$(words $(SRC_FILES))
COMPILED_FILES	=	0

define update_progress
	$(eval COMPILED_FILES := $(shell echo $$(($(COMPILED_FILES) + 1))))
	@printf "$(CYAN)[%2d/%d]$(RESET) Compiling $(notdir $<)...\n" $(COMPILED_FILES) $(TOTAL_FILES)
endef

define check_error
	@if [ $$? -ne 0 ]; then \
		echo "$(RED)[CUB3D] ❌ Build failed!$(RESET)"; \
		exit 1; \
	fi
endef

# -----------------------------------------------------------------------------
# Build rules
all:
	@echo "$(GREEN)╔══════════════════════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║                 CUB3D BUILD                  ║$(RESET)"
	@echo "$(GREEN)╚══════════════════════════════════════════════╝$(RESET)"
	@$(MAKE) --no-print-directory $(NAME) || { echo "$(RED)[CUB3D] ❌ Build failed$(RESET)"; exit 1; }

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(OBJS)
	@echo "$(BLUE)🔗 Linking executable...$(RESET)"
	@$(CC) $(OBJS) $(CFLAGS) $(MLX_LIBS) $(LIBFT_LIB) -o $(NAME)
	$(call check_error)
	@echo "$(GREEN)✅ Build complete! Executable: $(NAME)$(RESET)"

# Object compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(call update_progress)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(MLX_INC) $(LIBFT_INC) -c $< -o $@
	$(call check_error)

# -----------------------------------------------------------------------------
# External libs
$(MLX_LIB):
	@echo "$(YELLOW)⚙️  Building MLX42...$(RESET)"
	@cmake -S $(MLX_DIR) -B $(MLX_BUILD) >/dev/null
	@cmake --build $(MLX_BUILD) -j >/dev/null

$(LIBFT_LIB):
	@echo "$(YELLOW)⚙️  Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

# -----------------------------------------------------------------------------
# Utils
clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean || true

fclean: clean
	@echo "$(RED)🗑️  Removing executable and libs...$(RESET)"
	@$(RM) $(NAME)
	@$(RM) -r $(MLX_BUILD)
	@$(MAKE) -C $(LIBFT_DIR) fclean || true

re:
	@echo "$(CYAN)♻️  Rebuilding everything...$(RESET)"
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all

debug: CFLAGS += -DDEBUG -g3
debug: re

.PHONY: all clean fclean re debug
