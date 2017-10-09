#设置编译器
CC=gcc
CFLAGS=
LDFLAGS=-lpthread -lrtmp
LIB=./lib/librtmp/
#debug文件夹里的makefile文件需要最后执行，所以这里需要执行的子目录要排除debug文件夹，这里使用awk排除了debug文件夹，读取剩下的文件夹
#SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "debug") print $$9}')
SUBDIRS=lib src

#记住当前工程的根目录路径
ROOT_DIR=$(shell pwd)/
TARGET=rtmpStreamer
OBJ_DIR=./obj
BIN_DIR=./bin

SRC_DIR=./src
SRC=${wildcard ${SRC_DIR}/*.c}
OBJ=${patsubst %.c, $(OBJ_DIR)/%.o, ${notdir ${SRC}}}
#将以下变量导出到子shell中，本次相当于导出到子目录下的makefile中
export CC LDFLAGS LIB BIN OBJ_DIR BIN_DIR ROOT_DIR
#注意这里的顺序，需要先执行SUBDIRS最后才能是DEBUG
all:cmd $(SUBDIRS) $(OBJ) ${TARGET}
#递归执行子目录下的makefile文件，这是递归执行的关键

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
