BUILD_ROOT = ../../..

OBJS = estc.o
DEPS = estc.d

include $(BUILD_ROOT)/common_defs.mk

LIB = libestc.a

all: $(LIB)
	@echo "Done"

$(LIB): $(OBJS)
	@echo "Linking library $@"
	$(MAKE_LIBRARY)

clean:
	@echo "Cleaning library directory"
	@rm -f $(OBJS) $(DEPS) $(LIB)
