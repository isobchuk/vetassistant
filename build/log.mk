# Colors
RESET  := \033[0m
RED    := \033[31m
GREEN  := \033[32m
YELLOW := \033[33m
BLUE   := \033[34m
CYAN   := \033[36m
BOLD   := \033[1m

LOG_CXX 	= @printf "$(BLUE)$(BOLD)[CXX]$(RESET)\t"
LOG_CC 		=  @printf "$(BLUE)$(BOLD)[CC]$(RESET)\t"
LOG_AR 		=  @printf "$(YELLOW)$(BOLD)[AR]$(RESET)\t"
LOG_LD 		=  @printf "$(YELLOW)$(RED)[LD]$(RESET)\t"
LOG_SIZE 	=  @printf "$(YELLOW)$(GREEN)[SIZE]$(RESET)\t"