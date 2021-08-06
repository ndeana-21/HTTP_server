NAME = webserv

SRCS_DIR = ./srcs

SRCS_MAIN_DIR = .
SRCS_MAIN = main.cpp

SRCS_PARSER_DIR = parser
SRCS_PARSER =   Request.cpp\
				Response.cpp\
				Server.cpp\
				Location.cpp\
				Base.cpp

SRCS_SERVER_DIR = server
SRCS_SERVER =   Manager.cpp\
                Client.cpp \
                Cgi.cpp

SRCS_UTILS_DIR = utils
SRCS_UTILS	=   Base64.cpp\
				Data.cpp\
				HttpStatusCode.cpp\
                utils.cpp

SRCS 		=	$(addprefix $(SRCS_MAIN_DIR)/, $(SRCS_MAIN))\
				$(addprefix $(SRCS_PARSER_DIR)/, $(SRCS_PARSER))\
				$(addprefix $(SRCS_SERVER_DIR)/, $(SRCS_SERVER))\
				$(addprefix $(SRCS_UTILS_DIR)/, $(SRCS_UTILS))

RES_SRCS 	= $(addprefix $(SRCS_DIR)/, $(SRCS))

BUILD_DIR 	= ./build_dir
OBJS 		= $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))
DEPS 		= $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.d))

COMPILER	= clang++
INCLUDES	= -Iincludes
FLAGS		= -Wall -Werror -Wextra -std=c++98 -O3
M_FLAGS		= --no-print-directory

$(BUILD_DIR)/%.o : $(SRCS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(COMPILER) $(FLAGS) $(INCLUDES) -MMD -c $< -o $@
	@$(PRINT) "\n$(FGREEN)COMPILE: $<                   $(PNULL)"

all:
	@$(MAKE) $(M_FLAGS) $(NAME) -j

$(NAME): $(OBJS)
	@$(COMPILER) $(FLAGS) $(OBJS) -o $(NAME)
	@$(PRINT) "\n$(FGREEN)MAKE: ${NAME}                 $(PNULL)\n"

clean:
	@rm -f $(OBJS)
	@$(PRINT) "$(addprefix \n$(FRED)REMOVE: $(FYELLOW), $(OBJS))$(PNULL)"
	@rm -f $(DEPS)
	@$(PRINT) "$(addprefix \n$(FRED)REMOVE: $(FYELLOW), $(DEPS))$(PNULL)"
	@rm -rf $(BUILD_DIR)
	@$(PRINT) "$(addprefix \n$(FRED)REMOVE: $(FYELLOW), $(BUILD_DIR))$(PNULL)"

fclean:
	$(MAKE) $(M_FLAGS) clean
	@rm -f $(NAME)
	@$(PRINT) "\n$(FRED)REMOVE: $(FYELLOW)$(NAME)$(PNULL)"

re:
	$(MAKE) $(M_FLAGS) fclean
	$(MAKE) $(M_FLAGS) all

sanitizer:
	$(MAKE) $(M_FLAGS) fclean
	$(COMPILER) $(FLAGS) $(INCLUDES) -fsanitize=address -g3 $(RES_SRCS) -o $(NAME)
	ASAN_OPTIONS=detect_leaks=1 ./$(NAME)

valgrind:
	$(MAKE) $(M_FLAGS) re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME)

.PHONY: all clean fclean re

-include $(DEPS)


# **************************************************************************** #
#								Utilits										   #
# **************************************************************************** #

# Цвета шрифта
FBLACK		= \033[30m
FRED		= \033[31m
FGREEN		= \033[32m
FYELLOW		= \033[33m
FBLUE		= \033[34m
FMAGENTA	= \033[35m
FCYAN		= \033[36m
FGREY		= \033[37m

# Цвета фона
BGBLACK		= \033[40m
BGRED		= \033[41m
BGGREEN		= \033[42m
BGYELLOW	= \033[43m
BGBLUE		= \033[44m
BGMAGENTA	= \033[45m
BGCYAN		= \033[46m
BGGREY		= \033[47m

# Свойства текста
PBOLD		= \033[1m#	жирный шрифт
PDBOLD		= \033[2m#	полу яркий цвет
PNBOLD		= \033[22m#	нормальная интенсивность
PUNDERLINE	= \033[4m#	подчеркивание
PBLINK		= \033[5m#	мигание
PINVERSE	= \033[7m#	инверсия
PNULL		= \033[0m#	отмена

PRINT		= printf