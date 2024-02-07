# VAR DECLARATION

# SYSTEM
CPP 			:= g++
FLAGS			:= -Wall -Wextra -Werror -g #-fsanitize=address
RM				:= rm -f

#CLIENT
CLIENT_NAME		:= so_long
SRC_CLI_DIR		:= client/srcs
INC_CLI_DIR		:= client/includes
OBJS_CLI_DIR	:= client/objs
SRCS_CLI		:= main.cpp

#SERVER
SERVER_NAME		:= so_long_server
SRC_SERV_DIR	:= server/srcs
INC_SERV_DIR	:= server/includes
OBJS_SERV_DIR	:= server/objs
SRCS_SERV		:= main.cpp Server.cpp Client.cpp

# GFX
SFMLFLAGS		:= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

OBJS_CLI		:= ${SRCS_CLI:%.cpp=${OBJS_CLI_DIR}/%.o}
OBJS_SERV		:= ${SRCS_SERV:%.cpp=${OBJS_SERV_DIR}/%.o}

# COLORS
CLR_RMV			:= \033[0m
RED				:= \033[1;31m
GREEN			:= \033[1;32m
YELLOW			:= \033[1;33m
BLUE			:= \033[1;34m
CYAN			:= \033[1;36m


all: client server

#CLIENT COMPILATION
client: ${CLIENT_NAME}
${CLIENT_NAME}:		${OBJS_CLI}
					@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${CLIENT_NAME} ${CLR_RMV}..."
					${CPP} ${OBJS_CLI} ${SFMLFLAGS} -o ${CLIENT_NAME}
					@echo "${GREEN}${NAME} client created[0m 🎮 ✔️"

${OBJS_CLI}:		${OBJS_CLI_DIR}/%.o: ${SRC_CLI_DIR}/%.cpp
					@mkdir -p $(@D)
					${CPP} -I${INC_CLI_DIR} ${FLAGS} ${SFMLFLAGS} -O3 -c $< -o $@


server: ${SERVER_NAME}
${SERVER_NAME}:	${OBJS_SERV}
				@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${SERVER_NAME} ${CLR_RMV}..."
				${CPP} ${OBJS_SERV} ${SFMLFLAGS} ${FLAGS} -o ${SERVER_NAME}
				@echo "${GREEN}${SERVER_NAME} server created[0m 🎮 ✔️"

${OBJS_SERV}:	${OBJS_SERV_DIR}/%.o: ${SRC_SERV_DIR}/%.cpp
				@mkdir -p $(@D)
				${CPP} -I${INC_SERV_DIR} ${SFMLFLAGS} ${FLAGS} -O3 -c $< -o $@

cclean:
				@ ${RM} -rf ${OBJS_CLI_DIR}
				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}objs ✔️"

sclean:
				@ ${RM} -rf ${OBJS_SERV_DIR}
				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}objs ✔️"

fclean:			cclean sclean
				@ ${RM} ${CLIENT_NAME}
				@ ${RM} ${SERVER_NAME}
				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}binary ✔️"

re:				fclean all