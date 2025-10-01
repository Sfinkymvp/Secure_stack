FLAGS = -ggdb3 -std=c++17 -O0 \
	-Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat \
	-Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts \
	-Wconditionally-supported -Wconversion -Wctor-dtor-privacy \
	-Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security \
	-Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
	-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked \
	-Wpointer-arith -Winit-self -Wredundant-decls -Wshadow \
	-Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 \
	-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types \
	-Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef \
	-Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros \
	-Wno-literal-suffix -Wno-missing-field-initializers \
	-Wno-narrowing -Wno-old-style-cast -Wno-varargs \
    -fcheck-new -fsized-deallocation -fstack-protector \
	-fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer \
	-Wlarger-than=16384 -Wstack-usage=8192 -pie -fPIE -Werror=vla \
	-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr


FILES = $(OBJDIR)/main.o $(OBJDIR)/stack.o $(OBJDIR)/stack_error.o


OUTPUT_NAME = stack


OBJDIR = obj
$(OBJDIR):
	@mkdir -p $(OBJDIR)


debug: FLAGS += -DDEBUG -DHASH -DCANARY -DPOISON
debug: FILES += $(OBJDIR)/stack_hash.o $(OBJDIR)/stack_tests.o

debug: $(FILES) $(OBJDIR)/stack_hash.o $(OBJDIR)/stack_tests.o
	@g++ $(FILES) $(FLAGS) -o $(OUTPUT_NAME)


release: $(FILES)
	@g++ $(FILES) $(FLAGS) -o $(OUTPUT_NAME)


$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	@g++ -c main.cpp $(FLAGS) -o $(OBJDIR)/main.o


$(OBJDIR)/stack.o: stack.cpp | $(OBJDIR)
	@g++ -c stack.cpp $(FLAGS) -o $(OBJDIR)/stack.o


$(OBJDIR)/stack_error.o: stack_error.cpp | $(OBJDIR)
	@g++ -c stack_error.cpp $(FLAGS) -o $(OBJDIR)/stack_error.o


$(OBJDIR)/stack_hash.o: stack_hash.cpp | $(OBJDIR)
	@g++ -c stack_hash.cpp $(FLAGS) -o $(OBJDIR)/stack_hash.o


$(OBJDIR)/stack_tests.o: stack_tests.cpp | $(OBJDIR)
	@g++ -c stack_tests.cpp $(FLAGS) -o $(OBJDIR)/stack_tests.o
