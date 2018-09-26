BUILD=build

default: all

$(BUILD): firmware/test/config.h
	mkdir -p $(BUILD)

firmware/test/config.h:
	cp firmware/test/config.h.template firmware/test/config.h

all: $(BUILD) gitdeps
	cd $(BUILD) && cmake ../
	cd $(BUILD) && make

gitdeps:
	simple-deps --config firmware/main/dependencies.sd
	simple-deps --config firmware/test/dependencies.sd

clean:
	rm -rf $(BUILD)

veryclean: clean
	rm -rf gitdeps
