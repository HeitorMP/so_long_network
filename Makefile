# VAR DECLARATION

# SYSTEM
CC				:= c++
FLAGS			:= -Wall -Wextra -Werror -Wno-unused-result -g #-fsanitize=address
RM				:= rm -f

#CLIENT
CLIENT_NAME		:= so_long
SRC_CLI_DIR		:= client/srcs
INC_CLI_DIR		:= ./client/includes
OBJS_CLI_DIR	:= client/objs
SRCS_CLI		:= main.cpp \

#SERVER
SERVER_NAME		:= so_long_server
SRC_SERV_DIR	:= server/srcs
INC_SERV_DIR	:= ./server/includes
OBJS_SERV_DIR	:= server/objs
SRCS_SERV		:= main.cpp Server.cpp Client.cpp

# GFX
MLXFLAGS		:= -lmlx -lXext -lX11 -lm -lz -lbsd
MLX_DIR			:= ./minilibx-linux

OBJS_CLI		:= ${SRCS_CLI:%.cpp=${OBJS_CLI_DIR}/%.o}
OBJS_SERV		:= ${SRCS_SERV:%.cpp=${OBJS_SERV_DIR}/%.o}

# COLORS
CLR_RMV			:= \033[0m
RED				:= \033[1;31m
GREEN			:= \033[1;32m
YELLOW			:= \033[1;33m
BLUE			:= \033[1;34m
CYAN			:= \033[1;36m


all: external_libs client server

#CLIENT COMPILATION
client: external_libs ${CLIENT_NAME}
${CLIENT_NAME}:		${OBJS_CLI}
					@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${CLIENT_NAME} ${CLR_RMV}..."
					${CC} ${OBJS_CLI} -L${MLX_DIR} ${MLXFLAGS} ${FLAGS} -o ${CLIENT_NAME}
					@echo "${GREEN}${NAME} client created[0m 🎮 ✔️"

${OBJS_CLI}:		${OBJS_CLI_DIR}/%.o: ${SRC_CLI_DIR}/%.cpp
					@mkdir -p $(@D)
					${CC} -I${INC_CLI_DIR} ${FLAGS} -I. -O3 -c $< -o $@


server: external_libs ${SERVER_NAME}
${SERVER_NAME}:	${OBJS_SERV}
				@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${SERVER_NAME} ${CLR_RMV}..."
				${CC} ${OBJS_SERV} -L${MLX_DIR} ${MLXFLAGS} ${FLAGS} -o ${SERVER_NAME}
				@echo "${GREEN}${SERVER_NAME} server created[0m 🎮 ✔️"

${OBJS_SERV}:	${OBJS_SERV_DIR}/%.o: ${SRC_SERV_DIR}/%.cpp
				@mkdir -p $(@D)
				${CC} -I${INC_SERV_DIR} ${FLAGS} -O3 -c $< -o $@

external_libs:
				${MAKE} -C ${MLX_DIR}

cclean:
				@ ${RM} -rf ${OBJS_CLI_DIR}
				@ ${MAKE} clean -C ${MLX_DIR}
				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}objs ✔️"

sclean:
				@ ${RM} -rf ${OBJS_SERV_DIR}
				@ ${MAKE} clean -C ${MLX_DIR}
				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}objs ✔️"

fclean:			cclean sclean
				@ ${RM} ${CLIENT_NAME}
				@ ${RM} ${SERVER_NAME}
				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}binary ✔️"

re:				fclean all