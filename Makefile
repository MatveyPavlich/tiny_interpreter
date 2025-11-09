SRC_DIR = src
BUILD_DIR = build
LAB_DIR = lab

main: 
	gcc -std=c99 -Wall -Werror     \
		-I./$(SRC_DIR)/intf    \
		$(SRC_DIR)/impl/main.c \
		$(SRC_DIR)/impl/lexer.c \
		-o $(BUILD_DIR)/main 

clean:
	rm -rf $(BUILD_DIR)/*

run:
	$(BUILD_DIR)/main
