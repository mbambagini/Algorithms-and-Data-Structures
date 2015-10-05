CC		= g++

SRC_FILES := $(shell ls *.cc; ls examples/*.cc; ls others/*.cc)
OBJ_FILES := $(SRC_FILES:%.cc=%.o)

all: compile

### COMPILE ###

compile: $(OBJ_FILES)

%.o : %.cc
	@$(CC) $< -o $@

### TEST ###

test: $(OBJ_FILES)
	@for f in $^; do ./$$f; done

### CLEAN ###

clean:
	@rm -f *.o
	@rm -f examples/*.o
	@rm -f others/*.o
