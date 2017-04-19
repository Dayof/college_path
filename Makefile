OBJ_DIR = obj/
SRC_DIR = src/
HPP_DIR = headers/
CFLAGS = g++ -std=gnu++11

TARGET_MAIN = main
TARGET_REMOVE = rm
TARGET_ALL = all

_DEPS = course_flow.inl
DEPS = $(patsubst %,$(HPP_DIR)%,$(_DEPS))

_OBJ = course_flow.o
OBJ = $(patsubst %,$(OBJ_DIR)%,$(_OBJ))

$(TARGET_ALL): $(TARGET_REMOVE) $(TARGET_MAIN)

$(TARGET_MAIN): $(OBJ)
	$(CFLAGS) -o $@ $^ -I$(HPP_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(DEPS)
	$(CFLAGS) -c -o $@ $< -I$(HPP_DIR)

$(TARGET_REMOVE):
	rm -r $(OBJ_DIR)
	mkdir $(OBJ_DIR)
