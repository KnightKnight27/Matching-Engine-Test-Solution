.PHONY: build
build: ## Kicks off a build
	mkdir -p build
	g++ -o build/match_engine main.cpp order.cpp matching_engine.cpp

.PHONY: clean
clean: ## Cleans the build directory
	rm -rf build/*