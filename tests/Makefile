.PHONY: dynamic_array prefix_tree

all: dynamic_array prefix_tree cleanup

dynamic_array:
	gcc dynamic_array.c -lunity -o dynamic_array && ./dynamic_array

prefix_tree:
	gcc prefix_tree.c -lunity -o prefix_tree && ./prefix_tree

cleanup:
	rm ./dynamic_array ./prefix_tree