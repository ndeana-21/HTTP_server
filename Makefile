NAME		=	webserv
DIR			=	srcs

FILES		=	main.cpp					\
				Config/ServerConfig.cpp		\
				Config/RequestConfig.cpp	\
				Config/InputArgs.cpp		\
				Config/Config.cpp			\
				HTTP/Server.cpp				\
				HTTP/Response.cpp			\
				HTTP/Request.cpp			\
				HTTP/Client.cpp				\
				HTTP/CGI.cpp				\
				Utils/Utils.cpp				\
				Utils/StringUtils.cpp		\
				Utils/StatusCode.cpp		\
				Utils/MimeTypes.cpp			\
				Utils/Logger.cpp			\
				Utils/get_next_line.cpp		\
				Utils/File.cpp				\
				Utils/Base64.cpp

HEAD_FILES	=	includes/Config/ServerConfig.hpp	\
				includes/Config/RequestConfig.hpp	\
				includes/Config/InputArgs.hpp		\
				includes/Config/Config.hpp			\
				includes/HTTP/Server.hpp			\
				includes/HTTP/Response.hpp			\
				includes/HTTP/Request.hpp			\
				includes/HTTP/Client.hpp			\
				includes/HTTP/CGI.hpp				\
				includes/Utils/Utils.hpp			\
				includes/Utils/StringUtils.hpp		\
				includes/Utils/StatusCode.hpp		\
				includes/Utils/MimeTypes.hpp		\
				includes/Utils/Logger.hpp			\
				includes/Utils/get_next_line.hpp	\
				includes/Utils/File.hpp				\
				includes/Utils/Base64.hpp

SRCS		=	$(addprefix $(DIR)/, $(FILES))
INCLUDES	=	-I includes/Config -I includes/Utils -I includes/HTTP
OBJS		=	$(SRCS:.cpp=.o)

M_FLAGS		=	--no-print-directory
CC			=	clang++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -pthread -g -O0 $(INCLUDES) 

all: $(NAME)

%.o: %.cpp $(HEAD_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(PRINT) "\n$(FGREEN)COMPILE: $<                   $(PNULL)"


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@$(PRINT) "\n$(FGREEN)MAKE: ${NAME}                 $(PNULL)\n"

clean:
	@$(PRINT) "$(addprefix \n$(FRED)REMOVE: $(FYELLOW), $(OBJS))$(PNULL)"
	@rm -f $(OBJS)

fclean: clean
	@$(PRINT) "\n$(FRED)REMOVE: $(FYELLOW)$(NAME)$(PNULL)"
	@rm -f $(NAME)

re:	fclean all

run: all
	@./$(NAME)


.PHONY: all clean fclean re run lib

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