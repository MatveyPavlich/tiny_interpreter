SRC_DIR = src
BUILD_DIR = build
LAB_DIR = lab

main: 
	gcc -std=c99 -Wall -Werror -g    \
		-I./$(SRC_DIR)/intf      \
		$(SRC_DIR)/impl/main.c   \
		$(SRC_DIR)/impl/lexer.c  \
		$(SRC_DIR)/impl/parser.c \
		-o $(BUILD_DIR)/main 
	# gcc -std=c99 -Wall -Werror     \
	# 	-I./$(LAB_DIR)/intf    \
	# 	$(LAB_DIR)/impl/main.c \
	# 	$(LAB_DIR)/impl/lexer.c \
	# 	$(LAB_DIR)/impl/parser.c \
	# 	-o $(BUILD_DIR)/main 
clean:
	rm -rf $(BUILD_DIR)/*

run:
	$(BUILD_DIR)/main
