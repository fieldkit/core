BUILD ?= $(abspath build)
SHELL := /bin/bash

default: all

$(BUILD): firmware/test/config.h firmware/core/config.h seed
	mkdir -p $(BUILD)

firmware/test/config.h:
	cp firmware/test/config.h.template firmware/test/config.h

firmware/core/config.h:
	cp firmware/core/config.h.template firmware/core/config.h

all: $(BUILD) gitdeps
	cd $(BUILD) && cmake ../
	$(MAKE) -C $(BUILD)

seed:
	echo "// Generated before compile time to seed the RNG." > firmware/core/seed.h
	echo "" >> firmware/core/seed.h
	echo "#define RANDOM_SEED $$RANDOM" >> firmware/core/seed.h

gitdeps:
	simple-deps --config firmware/core/dependencies.sd
	simple-deps --config firmware/test/dependencies.sd

clean:
	rm -rf $(BUILD)

veryclean: clean
	rm -rf gitdeps
