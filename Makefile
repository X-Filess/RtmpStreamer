CC=gcc
CFLAGS=
LDFLAGS=-lpthread -lrtmp
LIB=./lib/librtmp/
#SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "debug") print $$9}')
SUBDIRS=lib src

ROOT_DIR=$(shell pwd)/
TARGET=rtmpStreamer
OBJ_DIR=./obj
BIN_DIR=./bin

SRC_DIR=./src
SRC=${wildcard ${SRC_DIR}/*.c}
OBJ=${patsubst %.c, $(OBJ_DIR)/%.o, ${notdir ${SRC}}}
export CC LDFLAGS LIB BIN OBJ_DIR BIN_DIR ROOT_DIR

all:cmd $(SUBDIRS) $(OBJ) ${TARGET}

cmd:
	@mkdir -p bin obj	

test:
	@echo $(SRC)
	@echo $(OBJ)

${TARGET}: ${OBJ}
	@${CC} ${OBJ} -o $(ROOT_DIR)/$(BIN_DIR)/$@ $(LDFLAGS) -L$(LIB)
	@echo "Compile done."

$(SUBDIRS):ECHO
	make -C $@

ECHO:
	@echo $(SUBDIRS)

clean:
	@rm -rf $(OBJ_DIR)/*.o
	@rm -rf $(BIN_DIR)/*
