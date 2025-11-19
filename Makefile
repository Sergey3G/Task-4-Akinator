CXX = g++

CXXFLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

LIBS = -lcsfml-graphics -lcsfml-window -lcsfml-system

TARGET = program

OBJS_CPP = main.o trees.o graph.o
OBJS_C   = user_interface.o
OBJS = $(OBJS_CPP) $(OBJS_C)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

main.o: main.c trees.h graph.h user_interface.h
	$(CXX) $(CXXFLAGS) -c main.c -o main.o

trees.o: trees.c trees.h user_interface.h
	$(CXX) $(CXXFLAGS) -c trees.c -o trees.o

graph.o: graph.c graph.h trees.h
	$(CXX) $(CXXFLAGS) -c graph.c -o graph.o

user_interface.o: user_interface.c user_interface.h trees.h
	$(CXX) $(CXXFLAGS) -c user_interface.c -o user_interface.o

clean:
	rm -f $(OBJS) $(TARGET)



