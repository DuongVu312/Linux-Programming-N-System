
# Variables 
LIB_NAME := math

CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/obj
LIB_DIR := $(CUR_DIR)/lib
LIB_STATIC_DIR := $(LIB_DIR)/static
LIB_SHARED_DIR := $(LIB_DIR)/shared

# Create Object Files
create_obj_sharedlib:
	gcc -c -fPIC $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o -I$(INC_DIR)
	gcc -c -fPIC $(SRC_DIR)/math.c -o $(OBJ_DIR)/math.o -I$(INC_DIR)
	gcc -c -fPIC $(SRC_DIR)/version.c -o $(OBJ_DIR)/version.o -I$(INC_DIR)

create_obj_staticlib:
	gcc -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o -I$(INC_DIR)
	gcc -c $(SRC_DIR)/math.c -o $(OBJ_DIR)/math.o -I$(INC_DIR)
	gcc -c $(SRC_DIR)/version.c -o $(OBJ_DIR)/version.o -I$(INC_DIR)

# Create Library
create_sharedlib:
	gcc -shared $(OBJ_DIR)/version.o $(OBJ_DIR)/math.o -o $(LIB_SHARED_DIR)/lib$(LIB_NAME).so

create_staticlib:
	ar rcs $(LIB_STATIC_DIR)/lib$(LIB_NAME).a $(OBJ_DIR)/version.o $(OBJ_DIR)/math.o

# Install Shared Library
install_sharedlib:
	cp -f $(LIB_SHARED_DIR)/lib$(LIB_NAME).so /usr/lib

# Linking Library
linking_sharedlib:
	gcc  $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -l$(LIB_NAME) -o $(BIN_DIR)/use-shared-library

linking_staticlib:
	gcc  $(OBJ_DIR)/main.o -L$(LIB_STATIC_DIR) -l$(LIB_NAME) -o $(BIN_DIR)/use-static-library

all: create_obj_sharedlib create_obj_staticlib create_sharedlib create_staticlib install_sharedlib linking_sharedlib linking_staticlib

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(LIB_SHARED_DIR)/*.so
	rm -rf $(LIB_STATIC_DIR)/*.a
	rm -rf $(BIN_DIR)/*