MAKEFLAGS += --no-print-directory
GREEN = \033[1;32m
RESET = \033[0m

all:
	@cmake -B build
	@make -C build -j
	@mv build/Particle-System .
	@echo "$(GREEN)Particle-System is ready to use : ./Particle-System [options] <json config> $(RESET)"

clean:
	@rm -rf build

fclean: clean
	@rm -f Particle-System

re: fclean all

.PHONY: all clean fclean re