# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pstengl <pstengl@student.42wolfsburg.      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 16:57:38 by pstengl           #+#    #+#              #
#    Updated: 2022/06/11 15:23:35 by pstengl          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Output Name:
NAME:=			ft_containers
# Can be 'library' or 'executable'
TYPE:=			executable

# Folders:
BINARIES:=		./binaries
BUILD:=			./build
INCLUDE:=		./include
SOURCE:=		./source
LIBRARIES:=		./libraries
TESTS:=			./tests

# Other Variables:
COMPILER:=		g++
COMPFLAGS:=		-Wall -Werror -Wextra -g -std=c++98
LIBPATHS:=
STDLIBS:=
NONSTDLIBS:=
NORMFLAGS:=

# Source Files:
SRCFILES:=\
	main.cpp\
	vector.cpp\
	iterator.cpp\
	reverse_iterator.cpp\
	is_integral.cpp\
	enable_if.cpp\
	stack.cpp

# ------------------------------------------
# Do not change anything beyond this point!
# ------------------------------------------

# Process Variables
CC:=		$(COMPILER)
CFLAGS:=\
		$(COMPFLAGS)\
		$(addprefix -I ,$(INCLUDE))\
		$(addprefix -I $(LIBRARIES)/,$(NONSTDLIBS))\
		$(addprefix -I $(LIBRARIES)/,$(addsuffix /include,$(NONSTDLIBS)))\
		$(addprefix -I ,$(addsuffix /include,$(LIBPATHS)))
LDFLAGS:=\
		$(addprefix -L $(LIBRARIES)/,$(NONSTDLIBS))\
		$(addprefix -L $(LIBRARIES)/,$(addsuffix /binaries,$(NONSTDLIBS)))\
		$(addprefix -L ,$(addsuffix /lib,$(LIBPATHS)))
LDLIBS:=\
		$(addprefix -l,$(subst lib,,$(NONSTDLIBS)))\
		$(addprefix -l,$(STDLIBS))
ARFLAGS:=	rcs
SRCS:=		$(addprefix $(SOURCE)/,$(SRCFILES))
OBJS:=		$(SRCS:$(SOURCE)/%.cpp=$(BUILD)/%.o)
NORM:=		$(shell which norminette)

# If we are compiling a library, add .a to the name
ifeq ($(TYPE),library)
	NAME:= $(NAME).a
endif

.PHONY: all clean fclean re bonus norm test

# Catch Rules
all: $(BINARIES)/$(NAME)
$(NAME): $(BINARIES)/$(NAME)

# Compile .cpp files to .o Files
$(OBJS): $(BUILD)%.o : $(SOURCE)%.cpp
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

# Main Build Rule
$(BINARIES)/$(NAME): $(OBJS)
	@for lib in $(NONSTDLIBS); do\
		echo "Compiling $$lib";\
		if [ -f $(LIBRARIES)/$$lib/configure ]; then\
			cd $(LIBRARIES)/$$lib;\
			./configure;\
			cd ../../;\
		fi;\
		$(MAKE) -j $(nprocs) -C $(LIBRARIES)/$$lib;\
	done
	mkdir -p $(BINARIES)
ifeq ($(TYPE),library)
	@echo "Creating Library $(NAME)"
	$(AR) $(ARFLAGS) $(BINARIES)/$(NAME) $(OBJS)
else
	@echo "Compiling executable $(NAME)"
	$(CC) $(CFLAGS) $(OBJS) -o $(BINARIES)/$(NAME) $(LDFLAGS) $(LDLIBS)
endif

# Clean up Objects
clean:
	@for lib in $(NONSTDLIBS); do \
		echo "Cleaning $$lib";\
		$(MAKE) -C $(LIBRARIES)/$$lib clean;\
	done
	@echo "Cleaning $(NAME)"
	$(RM) -r $(BUILD)

# Clean up Executables and static libraries
fclean: clean
	@for lib in $(NONSTDLIBS); do \
		echo "Force Cleaning $$lib";\
		$(MAKE) -C $(LIBRARIES)/$$lib fclean || true;\
	done
	@echo "Force Cleaning $(NAME)"
	$(RM) -r $(BINARIES)

# Clean the re-compile
re: fclean all

# Rule for the Bonus
bonus:
	@echo "No Bonus!"
	@exit 1

# Check the Norm
norm:
ifeq ($(strip $(NORM)),)
	$(error "Norminette not installed")
endif
	@$(NORM) --version
	@$(NORM) $(NORMFLAGS) $(SOURCE) $(INCLUDE) | grep -v "OK!" || true
ifeq ($(strip $(shell $(NORM) $(NORMFLAGS) $(SOURCE) $(INCLUDE) | grep -v "OK!")),)
	@echo "No Norm Errors found. Everything OK!"
else
	@exit 1
endif

# Run the test script
test: norm re
ifeq ($(wildcard $(TESTS)/test.sh),)
	$(error "Test Script test.sh not found in $(TESTS)")
endif
	@./tests/test.sh
