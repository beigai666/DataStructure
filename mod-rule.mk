
.PHONY : all

MODULE := $(realpath .)
MODULE := $(notdir $(MODULE))
DIR_OUTPUT := $(addprefix $(DIR_BUILD)/, $(MODULE))

OUTPUT := $(MODULE).a
OUTPUT := $(addprefix $(DIR_BUILD)/, $(OUTPUT))
DIRS = $(shell find $(realpath .) -maxdepth 3 -type d)  
#SRCS := $(wildcard $(DIR_SRC)/*$(TYPE_SRC))
SRCS := $(notdir $(foreach dir, $(DIRS), $(wildcard $(dir)/*$(TYPE_SRC)))) 

OBJS := $(SRCS:$(TYPE_SRC)=$(TYPE_OBJ))
OBJS := $(addprefix $(DIR_OUTPUT)/, $(OBJS))
DEPS := $(SRCS:$(TYPE_SRC)=$(TYPE_DEP))
DEPS := $(addprefix $(DIR_OUTPUT)/, $(DEPS))

vpath %$(TYPE_INC) $(DIR_INC)
vpath %$(TYPE_INC) $(DIR_COMMON_INC)
vpath %$(TYPE_SRC) $(DIRS)
-include $(DEPS)

all : $(OUTPUT)
	@echo $(DIRS)
	@echo $(SRCS)
	@echo $(OBJS)
	@echo "Success! Target ==> $(OUTPUT)"
	
$(OUTPUT) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
	
$(DIR_OUTPUT)/%$(TYPE_OBJ) : %$(TYPE_SRC)
	@echo $^
	$(CC) $(CFLAGS) -o $@ -c $(filter %$(TYPE_SRC), $^)
	
	
$(DIR_OUTPUT)/%$(TYPE_DEP) : %$(TYPE_SRC)
	@echo "Creating $@ ..."
	@set -e; \
	$(CC) $(CFLAGS) -MM -E $(filter %$(TYPE_SRC), $^) | sed 's,\(.*\)\.o[ :]*,$(DIR_OUTPUT)/\1$(TYPE_OBJ) $@ : ,g' > $@
