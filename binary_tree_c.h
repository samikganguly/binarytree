struct node {
	int key;
	void* val;
	struct node* l_child;
	struct node* r_child;
};
struct binary_tree {
	struct node* root;
	int size;
};
enum travarse_mode {
	PRE_ORDER, POST_ORDER, IN_ORDER, DEPTH_FIRST, BREADTH_FIRST
};
void init_node(struct node** new_node, const int key, const void* val);
void init_binary_tree(struct binary_tree** tree, const struct node* root);
void destroy_binary_tree(struct binary_tree** tree);
struct node* binary_tree_search(const struct binary_tree* tree, const int key);
void binary_tree_insert(struct binary_tree* tree, const struct node* new_node);
void binary_tree_remove(struct binary_tree* tree, const int key);
int binary_tree_size(const struct binary_tree* tree);
void binary_tree_flatten(const struct binary_tree* tree, enum travarse_mode t_mode, struct node** container);
