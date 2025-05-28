typedef struct Node *rb_tree;

int color(struct Node *H);
void change_color(struct Node *H);
struct Node *left_rotation(struct Node *A);
struct Node *right_rotation(struct Node *A);
struct Node *move_to_left_red(struct Node *H);
struct Node *move_to_right_red(struct Node *H);
struct Node *balance(struct Node *H);
struct Node * insert_node(struct Node *H, int value, int *answer);
int insert_tree(rb_tree *root, int value);
struct Node *remove_node(struct Node *H, int value);
int remove_tree(rb_tree *root, int value);
struct Node *remove_smaller(struct Node *H);
struct Node *search_smallest(struct Node *current);
int search_tree(rb_tree *root, int value);
void print_in_order(rb_tree root);
/*
rb_tree *create_tree();
void free_tree(rb_tree *root);
int insert_tree(rb_tree *root, int value);
int remove_tree(rb_tree *root, int value);
int is_empty(rb_tree *root);
int total_node(rb_tree *root);
int height_tree(rb_tree *root);
int search_tree(rb_tree *root, int value);

void print_in_order(rb_tree root);*/