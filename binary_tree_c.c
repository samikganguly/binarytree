#include <stdio.h>
#include <stdlib.h>
#include "binary_tree_c.h"
#define TRV_OPR_FLT 0
#define TRV_OPR_SRCH 1
#define TRV_OPR_FREE 2
#define MOD_OPR_INS 1
#define MOD_OPR_DEL 0

static int _travarse(struct node**, enum travarse_mode, struct node**, const unsigned char, const int, struct node**, int, int); 
static int _modify(struct node**, struct node**, struct node*, const unsigned char);
void init_node(struct node** new_node, const int key, const void* val) {
	*new_node = malloc(sizeof(struct node));
	if(!*new_node) {
		fprintf(stderr, "can't allocate memory for new tree node\n");
		exit(EXIT_FAILURE);
	}
	(*new_node)->key = key;
	(*new_node)->val = val;
	(*new_node)->l_child = NULL;
	(*new_node)->r_child = NULL;
}
void init_binary_tree(struct binary_tree** tree, const struct node* root) {
	*tree = malloc(sizeof(struct binary_tree));
	if(!*tree) {
		fprintf(stderr, "can't allocate memory for the tree\n");
		exit(EXIT_FAILURE);
	}
	(*tree)->root = root;
	(*tree)->size = root ? 1 : 0;
}
void destroy_binary_tree(struct binary_tree** tree) {
	if(*tree) {
		_travarse(&((*tree)->root), POST_ORDER, NULL, TRV_OPR_FREE, 0, NULL, 0, (*tree)->size);
		free(*tree);
		*tree = NULL;
	}
}
int binary_tree_size(const struct binary_tree* tree) {
	if(tree) return tree->size;
	else return 0;
}
struct node* binary_tree_search(const struct binary_tree* tree, const int key) {
	auto struct node* srch_node = NULL;
	if(tree) _travarse(&(tree->root), IN_ORDER, NULL, TRV_OPR_SRCH, key, &srch_node, 0, tree->size);
	return srch_node;
}
void binary_tree_flatten(const struct binary_tree* tree, enum travarse_mode t_mode, struct node** container) {
	if(tree) _travarse(&(tree->root), t_mode, container, TRV_OPR_FLT, 0, NULL, 0, tree->size);
}
void binary_tree_insert(struct binary_tree* tree, const struct node* new_node) {
	if(tree) tree->size += _modify(NULL, &(tree->root), new_node, MOD_OPR_INS);
}
void binary_tree_remove(struct binary_tree* tree, const int key) {
	auto struct node* ctr;
	init_node(&ctr, key, NULL);
	if(tree) tree->size += _modify(NULL, &(tree->root), ctr, MOD_OPR_DEL);
	free(ctr);
}
static int _modify(struct node** parent_node, struct node** curr_node, struct node* key_node, const unsigned char operation) {
	int count = 0;
	auto struct node* tmp, * parent_tmp;
	if(!*curr_node) {
		if(operation == MOD_OPR_INS) {
			*curr_node = key_node;
			count++;
		}			
	} else if((*curr_node)->key > key_node->key) {
		if((*curr_node)->l_child)
			count = _modify(curr_node, &((*curr_node)->l_child), key_node, operation);
		else if(operation == MOD_OPR_INS) {
			(*curr_node)->l_child = key_node;
			count++;
		}
	} else if((*curr_node)->key < key_node->key){
		if((*curr_node)->r_child)
			count = _modify(curr_node, &((* curr_node)->r_child), key_node, operation);
		else if(operation == MOD_OPR_INS) {
			(*curr_node)->r_child = key_node;
			count++;
		}
	} else {
		if(operation == MOD_OPR_INS)
			(*curr_node)->val = key_node->val;
		else if(operation == MOD_OPR_DEL) {
			if((*curr_node)->l_child && (*curr_node)->r_child) {
				tmp = (*curr_node)->r_child;
				parent_tmp = *curr_node;
				while(tmp->l_child) {
					parent_tmp = tmp;
					tmp = tmp->l_child;
				}
				if(parent_tmp->l_child == tmp && tmp->r_child)
					parent_tmp->l_child = tmp->r_child;
				else if(parent_tmp->l_child == tmp && !(tmp->r_child))
					parent_tmp->l_child = NULL;
				else if(parent_tmp->r_child == tmp && tmp->r_child)
					parent_tmp->r_child = tmp->r_child;
				else if(parent_tmp->r_child == tmp && !(tmp->r_child))
					parent_tmp->r_child = NULL;
				(*curr_node)->key = tmp->key;
				(*curr_node)->val = tmp->val;
				free(tmp);
			} else if((*curr_node)->l_child || (*curr_node)->r_child) {
				tmp = (*curr_node)->l_child ? (*curr_node)->l_child : (*curr_node)->r_child;
				**curr_node = *tmp;
				free(tmp);
			} else {
				if(parent_node) {
					if((*parent_node)->l_child == *curr_node)
						(*parent_node)->l_child = NULL;
					else
						(*parent_node)->r_child = NULL;
				}
				free(*curr_node);
			}
			count--;
		}
	}
	return count;
}
static int _travarse(struct node** curr_node, enum travarse_mode t_mode, struct node** ctr, const unsigned char operation, const int key, struct node** srch_node, int flat_tree_index, int tree_size) {
	int ctr_index = flat_tree_index, visited = 0;
	if(*curr_node) {
		if(operation == TRV_OPR_SRCH && key == (*curr_node)->key) {
			*srch_node = *curr_node;
			return ctr_index;
		}
		switch(t_mode) {
			case DEPTH_FIRST:
			case PRE_ORDER:
				if(operation == TRV_OPR_FLT && ctr) { ctr[ctr_index] = *curr_node; ctr_index++; }
				if((*curr_node)->l_child) {
					ctr_index = _travarse(&((*curr_node)->l_child), t_mode, ctr, operation, key, srch_node, ctr_index, tree_size);
				}
				if((*curr_node)->r_child) {
					ctr_index = _travarse(&((*curr_node)->r_child), t_mode, ctr, operation, key, srch_node, ctr_index, tree_size);
				}
				break;
			case POST_ORDER:
				if((*curr_node)->l_child) {
					ctr_index = _travarse(&((*curr_node)->l_child), t_mode, ctr, operation, key, srch_node, ctr_index, tree_size);
				}
				if((*curr_node)->r_child) {
					ctr_index = _travarse(&((*curr_node)->r_child), t_mode, ctr, operation, key, srch_node, ctr_index, tree_size);
				}
				if(operation == TRV_OPR_FLT && ctr) { ctr[ctr_index] = *curr_node; ctr_index++; }
				else if(operation == TRV_OPR_FREE) {
					free(*curr_node);
				}
				break;
			case IN_ORDER:
				if((*curr_node)->l_child) {
					ctr_index = _travarse(&((*curr_node)->l_child), t_mode, ctr, operation, key, srch_node, ctr_index, tree_size);
				}
				if(operation == TRV_OPR_FLT && ctr) { ctr[ctr_index] = *curr_node; ctr_index++; }
				if((*curr_node)->r_child) {
					ctr_index = _travarse(&((*curr_node)->r_child), t_mode, ctr, operation, key, srch_node, ctr_index, tree_size);
				}
				break;
			case BREADTH_FIRST:
				if(operation == TRV_OPR_FLT && ctr) {
					ctr[visited] = *curr_node; ctr_index++;
					while(ctr_index < tree_size) {
						if((ctr[visited])->l_child)
							{ ctr[ctr_index] = (ctr[visited])->l_child; ctr_index++; }
						if((ctr[visited])->r_child)
							{ ctr[ctr_index] = (ctr[visited])->r_child; ctr_index++; }
						visited++;
					}
				}
				break;
		}
	}
	return ctr_index;
}
