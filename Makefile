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
NAME_SERVER_G		:= so_long_server
SRC_SERVERG_DIR		:= server_game/srcs
INC_SERVERG_DIR  	:= server_game/includes
OBJS_SERVERG_DIR	:= server_game/objs
SRCS_SERVERG		:= main.cpp ClientServer.cpp

#SERVER CHAT
NAME_SERVER_C		:= chat_server
SRC_SERVERC_DIR		:= server_chat/srcs
INC_SERVERC_DIR  	:= server_chat/includes
OBJS_SERVERC_DIR	:= server_chat/objs
SRCS_SERVERC		:= main.cpp
# GFX
SFMLFLAGS		:= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

OBJS_CLIENT		:= ${SRCS_CLIENT:%.cpp=${OBJS_CLIENT_DIR}/%.o}
OBJS_SERVERG	:= ${SRCS_SERVERG:%.cpp=${OBJS_SERVERG_DIR}/%.o}
OBJS_SERVERC	:= ${SRCS_SERVERC:%.cpp=${OBJS_SERVERC_DIR}/%.o}

# COLORS
CLR_RMV			:= \033[0m
RED				:= \033[1;31m
GREEN			:= \033[1;32m
YELLOW			:= \033[1;33m
BLUE			:= \033[1;34m
CYAN			:= \033[1;36m


all: ${NAME_CLIENT} ${NAME_SERVER_G} ${NAME_SERVER_C}

# COMPILATION CLIENT
${NAME_CLIENT}:		${OBJS_CLIENT} 
					@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME_CLIENT} ${CLR_RMV}..."
					${CPP} ${OBJS_CLIENT} ${SFMLFLAGS} -o bin/${NAME_CLIENT}
					@echo "${GREEN}${NAME_CLIENT} so_long client created[0m 🎮 ✔️"

${OBJS_CLIENT}:		${OBJS_CLIENT_DIR}/%.o: ${SRC_CLIENT_DIR}/%.cpp
					@mkdir -p $(@D)
					${CPP} -I${INC_CLIENT_DIR} ${FLAGS} -O3 -c $< -o $@

# COMPILATION SERVER GAME
${NAME_SERVER_G}:	${OBJS_SERVERG}
					@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME_SERVER_G} ${CLR_RMV}..."
					${CPP} ${OBJS_SERVERG} ${SFMLFLAGS} -o  bin/${NAME_SERVER_G}
					@echo "${GREEN}${NAME_SERVER_G} game server created[0m 🎮 ✔️"

${OBJS_SERVERG}:	${OBJS_SERVERG_DIR}/%.o: ${SRC_SERVERG_DIR}/%.cpp
					@mkdir -p $(@D)
					${CPP} -I${INC_SERVERG_DIR} ${FLAGS} -O3 -c $< -o $@
# COMPILATION SERVER CHAT
${NAME_SERVER_C}:	${OBJS_SERVERC}
					@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME_SERVER_C} ${CLR_RMV}..."
					${CPP} ${OBJS_SERVERC} ${SFMLFLAGS} -o  bin/${NAME_SERVER_C}
					@echo "${GREEN}${NAME_SERVER_C} chat server created[0m 🎮 ✔️"

${OBJS_SERVERC}:	${OBJS_SERVERC_DIR}/%.o: ${SRC_SERVERC_DIR}/%.cpp
					@mkdir -p $(@D)
					${CPP} -I${INC_SERVERC_DIR} ${FLAGS} -O3 -c $< -o $@

clean:
				@ ${RM} -rf ${OBJS_CLIENT_DIR} ${OBJS_SERVERG_DIR} ${OBJS_SERVERC_DIR}
				@ echo "${RED}Deleting ${CYAN}${NAME_CLIENT} ${CLR_RMV}objs ✔️"
				@ echo "${RED}Deleting ${CYAN}${NAME_SERVER_C} ${CLR_RMV}objs ✔️"
				@ echo "${RED}Deleting ${CYAN}${NAME_SERVER_G} ${CLR_RMV}objs ✔️"

fclean:			clean
				@ ${RM} bin/${NAME_CLIENT}
				@ ${RM} bin/${NAME_SERVER_C}
				@ ${RM} bin/${NAME_SERVER_G}
				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}binary ✔️"

re:				fclean all
