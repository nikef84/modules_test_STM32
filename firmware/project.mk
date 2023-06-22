# C source files
PROJECT_CSRC 	= 	src/main.c \
					src/terminal_write.c \
					src/i2c/i2c_lld.c \
					src/i2c/laser_rangefinder.c \
					src/i2c/led_matrix.c \
					src/i2c/gyro.c \
					
					

					
					
TESTSRC 	= 		tests/i2c/laser_rangefinder_test.c \
					tests/i2c/i2c_test.c \
					tests/i2c/led_matrix_test.c \
					tests/i2c/gyro_test.c \
					
					

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