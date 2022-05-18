echo

valgrind -q --leak-check=full --errors-for-leak-kinds=all ./binaries/ft_containers
exit $?
