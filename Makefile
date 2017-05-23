#Nom de l'exécutable
NAME = xen_compiler_midi
#Fichiers source (.cpp)
SRC = main.cpp ArgsParser.cpp strUtils.cpp MidiCompiler.cpp XenTrack.cpp XenNote.cpp\
	  XenWriter.cpp
#Flags de compilation
FLAGS = -Werror -Wall -Wextra

OBJ = $(addprefix obj/, $(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ) midifile
	@g++ -o $(NAME) -std=c++11 $(OBJ) -Lmidifile/lib -lmidifile

obj/%.o: src/%.cpp
	@echo "Compilation > $@"
	@mkdir -p $(dir $@)
	@g++ $(FLAGS) -std=c++11 -I include -I midifile/include -c $^ -o $@

midifile:
	make -C midifile library

clean:
	@make -C midifile clean
	@rm -rf obj
	@rm -f $(NAME)

re: clean all

.PHONY: midifile
