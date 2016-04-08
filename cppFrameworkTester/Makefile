
#-------------------------------------------------
# Makefile to build
#-------------------------------------------------
TARGET=cppFrameworkTester

#-------------------------------------------------
# Specify objects to build
#-------------------------------------------------
OBJECT_FILES = \
	../CallStacks/BaseStackMessage.o \
	../CallStacks/BaseStack.o \
	../CallStacks/AbsoluteStack.o \
	../CallStacks/Queue.o \
	../Debug/assertion.o \
	../Memory/RAM.o \
	../Threading/ErnoBaseTranslator.o \
	../Threading/Mutex.o \
	../Threading/Thread.o \
	../Timing/Chrono.o \
	../Timing/Timing.o \
	../Tools/Conversion/SizeFileConversion.o \
	../Tools/Hardware/CPU.o \
	tester/testCallstacksBaseMessage.o \
	tester/testCallstacksQueue.o \
	tester/testCallstacksAbsouteStack.o \
	tester/testThreadingMutex.o \
	tester/testTimingChrono.o \
	tester/testMemoryRam.o \
	cppFrameworkTester.o 

#-------------------------------------------------
# Specify user includes dir
#-------------------------------------------------
COMP_INCLUDES = \
	-I. \
	-I.. \
	-I../../ \
	-Itester
#-------------------------------------------------
# Specify user lib
#-------------------------------------------------	
LIBS = \
    -lpthread 

#-------------------------------------------------
# Specify user lib dir
#-------------------------------------------------	
LIBS_DIR = \
    -L. \
    -L../dist

#-------------------------------------------------
# define the compiler and linker
#-------------------------------------------------
CC=g++

COMP_CFLAGS= -DLINUX -D_DEBUG -Wall -m32 -Wno-unknown-pragmas

###############################################################################
###############################################################################

# macro for ultimate target
all: clean $(TARGET)

# build objects
%.o : %.cpp
	@echo -------------------------------------------------------
	@echo Running Compile of file $@
	@echo -------------------------------------------------------
	$(CC) -c $(COMP_INCLUDES) $(COMP_CFLAGS) $< -o $@

# link objects
$(TARGET): $(OBJECT_FILES)
	@echo -------------------------------------------------------
	@echo Link target $@
	@echo -------------------------------------------------------
	@mkdir -p ../dist/
	${CC} -o ../dist/$@ $(OBJECT_FILES) ${LIBS_DIR} ${LIBS} $(COMP_CFLAGS)

# clean project	
clean:
	@echo -------------------------------------------------------
	@echo Clean $(TARGET)
	@echo -------------------------------------------------------	
	rm -rf $(OBJECT_FILES)
	rm -rf $(TARGET)
	rm -rf ../dist/$(TARGET)
