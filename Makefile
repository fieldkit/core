BUILD=build

default: all

$(BUILD): firmware/test/config.h firmware/core/config.h
	mkdir -p $(BUILD)

firmware/test/config.h:
	cp firmware/test/config.h.template firmware/test/config.h

firmware/core/config.h:
	cp firmware/core/config.h.template firmware/core/config.h

all: $(BUILD) gitdeps
	cd $(BUILD) && cmake ../
	$(MAKE) -C $(BUILD)

gitdeps:
	simple-deps --config firmware/core/dependencies.sd
	simple-deps --config firmware/test/dependencies.sd

clean:
	rm -rf $(BUILD)

veryclean: clean
	rm -rf gitdeps
