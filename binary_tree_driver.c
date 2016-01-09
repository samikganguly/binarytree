#include <stdio.h>
#include <stdlib.h>
#include "binary_tree_c.h"

int main(void) {
	struct binary_tree* tree = NULL;
	struct node* new_node = NULL, ** flat_tree = NULL;
	char choise, val;
	int key, size, buf[10];
	while(1) {
		fprintf(stdout, "Binary Tree Demo\n\ta)Insert\n\tb)Remove\n\tc)Search\n\td)Display\n\te)Exit\n\tEnter Choise: ");
		fscanf(stdin, " %c", &choise);
		switch(choise) {
			case 'a':
				fprintf(stdout, "\tEnter key(number) and value(character) to Insert: ");
				fscanf(stdin, "%d %c", &key, &val);
				init_node(&new_node, key, val);
				if(!tree)
					init_binary_tree(&tree, new_node);
				else
					binary_tree_insert(tree, new_node);
				fprintf(stdout, "\tInserted %d-%c in the tree, new tree size %d\n", key, val, binary_tree_size(tree));
				break;
			case 'b':
				fprintf(stdout, "\tEnter key(number) to Remove: ");
				fscanf(stdin, "%d", &key);
				binary_tree_remove(tree, key);
				fprintf(stdout, "\tRemoved %d from the tree, new tree size %d\n", key, binary_tree_size(tree));
				break;
			case 'c':
				fprintf(stdout, "\tEnter key(number) to Search value(character): ");
				fscanf(stdin, "%d", &key);
				if(new_node = binary_tree_search(tree, key))
					fprintf(stdout,"\tkey = %d, value = %c\n", new_node->key, (char)(new_node->val));
				break;
			case 'd':
				fprintf(stdout, "\tOrder of Display\n\t\ta)depth-first(in-order)\n\t\tb)depth-first(pre-order)\n\t\tc)depth-first(post-order)\n\t\td)breadth-first\n\t\te)back to previous menu\n\t\tEnter choise: ");	
				fscanf(stdin, " %c", &choise);
				if(choise < 'e' && choise >= 'a') {
					flat_tree = malloc(binary_tree_size(tree) * sizeof(struct node*));
					if(!flat_tree) {
						fprintf(stdout, "can't allocate memory for flattened tree\n");
						exit(EXIT_FAILURE);
					}
					switch(choise) {
						case 'a':
							binary_tree_flatten(tree, IN_ORDER, flat_tree);		
							break;
						case 'b':	
							binary_tree_flatten(tree, PRE_ORDER, flat_tree);
							break;
						case 'c':
							binary_tree_flatten(tree, POST_ORDER, flat_tree);
							break;
						case 'd':
							binary_tree_flatten(tree, BREADTH_FIRST, flat_tree);
					}
					fprintf(stdout,"\t");
					for(size = 0; size < binary_tree_size(tree); size++) {
						fprintf(stdout, "(key = %d, value = %c) ", flat_tree[size]->key, (char)(flat_tree[size]->val));
					}
					fprintf(stdout, "\n");
					free(flat_tree);
				}
				break;
			case 'e':
				if(tree) destroy_binary_tree(&tree);
				exit(EXIT_SUCCESS);
			default:
				fprintf(stdout, "Enter a, b, c, d or e in lower-case\n");
		}
	}
	return 0;
}
