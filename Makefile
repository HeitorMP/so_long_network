# VAR DECLARATION

# SYSTEM
CPP 			:= g++
FLAGS			:= -Wall -Wextra -Werror #-g #-fsanitize=address
RM				:= rm -f

#CLIENT
NAME_CLIENT		:= so_long
SRC_CLIENT_DIR	:= client/srcs
INC_CLIENT_DIR  := client/includes
OBJS_CLIENT_DIR	:= client/objs
SRCS_CLIENT		:= main.cpp Client.cpp Playfield.cpp

#SERVER GAME
NAME_SERVER		:= so_long_server
SRC_SERVER_DIR	:= server_game/srcs
INC_SERVER_DIR  := server_game/includes
OBJS_SERVER_DIR	:= server_game/objs
SRCS_SERVER		:= main.cpp ClientServer.cpp

# GFX
SFMLFLAGS		:= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

OBJS_CLIENT		:= ${SRCS_CLIENT:%.cpp=${OBJS_CLIENT_DIR}/%.o}
OBJS_SERVER	:= ${SRCS_SERVER:%.cpp=${OBJS_SERVER_DIR}/%.o}

# COLORS
CLR_RMV			:= \033[0m
RED				:= \033[1;31m
GREEN			:= \033[1;32m
YELLOW			:= \033[1;33m
BLUE			:= \033[1;34m
CYAN			:= \033[1;36m


all: ${NAME_CLIENT} ${NAME_SERVER}

# COMPILATION CLIENT
${NAME_CLIENT}:		${OBJS_CLIENT} 
					@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME_CLIENT} ${CLR_RMV}..."
					${CPP} ${OBJS_CLIENT} ${SFMLFLAGS} -o bin/${NAME_CLIENT}
					@echo "${GREEN}${NAME_CLIENT} so_long client created[0m 🎮 ✔️"

${OBJS_CLIENT}:		${OBJS_CLIENT_DIR}/%.o: ${SRC_CLIENT_DIR}/%.cpp
					@mkdir -p $(@D)
					${CPP} -I${INC_CLIENT_DIR} ${FLAGS} -O3 -c $< -o $@

# COMPILATION SERVER GAME
${NAME_SERVER}:	${OBJS_SERVER}
					@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME_SERVER} ${CLR_RMV}..."
					${CPP} ${OBJS_SERVER} ${SFMLFLAGS} -o  bin/${NAME_SERVER}
					@echo "${GREEN}${NAME_SERVER} game server created[0m 🎮 ✔️"

${OBJS_SERVER}:	${OBJS_SERVER_DIR}/%.o: ${SRC_SERVER_DIR}/%.cpp
					@mkdir -p $(@D)
					${CPP} -I${INC_SERVER_DIR} ${FLAGS} -O3 -c $< -o $@

clean:
				@ ${RM} -rf ${OBJS_CLIENT_DIR} ${OBJS_SERVER_DIR} ${OBJS_SERVERC_DIR}
				@ echo "${RED}Deleting ${CYAN}${NAME_CLIENT} ${CLR_RMV}objs ✔️"
				@ echo "${RED}Deleting ${CYAN}${NAME_SERVER_C} ${CLR_RMV}objs ✔️"
				@ echo "${RED}Deleting ${CYAN}${NAME_SERVER} ${CLR_RMV}objs ✔️"

fclean:			clean
				@ ${RM} bin/${NAME_CLIENT}
				@ ${RM} bin/${NAME_SERVER}
				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}binary ✔️"

re:				fclean all
