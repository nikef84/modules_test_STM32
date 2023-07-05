# C source files
PROJECT_CSRC 	= 	src/main.c \
					src/terminal_write.c \
					src/i2c/i2c_lld.c \
					src/i2c/laser_rangefinder.c \
					src/i2c/led_matrix.c \
					src/i2c/oled_display/oled_animation_cat.c \
					src/i2c/oled_display/oled_basic_img.c \
					src/i2c/oled_display/oled_basic.c \
					src/i2c/oled_display/oled_fonts.c \
					src/i2c/oled_display/oled_text.c \
					src/i2c/oled_display/oled_geom.c \

					

					
					
TESTSRC 	= 		tests/i2c/laser_rangefinder_test.c \
					tests/i2c/i2c_test.c \
					tests/i2c/led_matrix_test.c \
					tests/i2c/oled_display/oled_animation_cat_test.c \
					tests/i2c/oled_display/oled_basic_test.c \
					tests/i2c/oled_display/oled_geom_test.c \
					tests/i2c/oled_display/oled_text_test.c \
					
					

# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= 	include \
				  	include/i2c \
				  	include/i2c/oled_display \
				  	
 

# Additional libraries
PROJECT_LIBS	= -lm
# Compiler options
PROJECT_OPT     = -DCHPRINTF_USE_FLOAT=1 -specs=nano.specs -specs=nosys.specs

# Additional .mk files are included here
CSRC = $(ALLCSRC) \
       $(TESTSRC) \
       $(PROJECT_CSRC) \
       $(CHIBIOS)/os/various/evtimer.c