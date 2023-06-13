# C source files
PROJECT_CSRC 	= 	src/main.c \
					src/i2c/i2c_lld.c \
					src/terminal_write.c \

					
					
TESTSRC 	= 		tests/i2c/laser_rangefinder.c \

					

# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= 	include \
				  	include/i2c \
				  	
 

# Additional libraries
PROJECT_LIBS	= -lm
# Compiler options
PROJECT_OPT     = -DCHPRINTF_USE_FLOAT=1 -specs=nano.specs -specs=nosys.specs

# Additional .mk files are included here
CSRC = $(ALLCSRC) \
       $(TESTSRC) \
       $(PROJECT_CSRC) \
       $(CHIBIOS)/os/various/evtimer.c