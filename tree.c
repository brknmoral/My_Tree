#include "Tree.h"

/*Debug mode*/
int debug_mode = 0;

/*Color define*/
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define PINK    "\033[1;35m"
#define RESET   "\033[0m"

/*Some dbg macroses*/
#define SAY_FUNC(   func_name){printf("Im in %s\n", func_name);}
#define DUMP_PEREM( name_x, x){printf("%s == <%d>\n", name_x, x);}

/*my macros*/
#define MAKEPROBLEM(ret_value, ...){                                         \
    printf(RED "ERROR, err = %d, in %s:%d\n" RESET, ret_value, __FILE__, __LINE__); \
    printf("\n");                                                                   \
    return ret_value;                                                               \
}

/*Constants*/
const int tree_count      =   1;
const int cnt_of_new_node =   1;
const int POISON_VALUE    = -17;

/*Tree structure*/
struct Node
{
    double value;
    struct Node* left;
    struct Node* right;
    struct Node* parent;

};

/*List Errors*/
enum List_ERRORS
{
    LIST_OK           =  0,
    LIST_ERR_ZERO_PTR = -7,
};

/*Func Prototypes*/
int _main                   (void);
int Tree_Init               (struct Node* root);
struct Node* Create_New_Node(double data);
struct Node* Insert_New_Elem(struct Node* new_tree_elem , struct Node* node);
void Preorder_Dump          (struct Node* cur_node);
int Tree_Dump               (const struct Node* root);
int log_file_create         (FILE* file);
int log_write               (FILE* file, struct Node* cur_node);
void log_file_close         (FILE* file);
void Check_Empty_Tree       (struct Node* tree);
void Tree_Clear             (struct Node* node);


/*Programm beginning*/
int main (int arg_c, char* arg_v[])
{
    for (int i  = 0; i < arg_c; i++)
    {
        if (strcmp(arg_v[i], "--debug") && (i + 1 < arg_c))
        {
            debug_mode = atoi(arg_v[i + 1]);
            if (debug_mode < 0) {debug_mode == 0;}
            if (debug_mode > DBG_INFO) {debug_mode == DBG_INFO;}
            i++;
        }     
    }

    _main();

    return 0;
}

int _main(void)
{
    //static FILE* f = NULL;
    //log_file_create(f);

    struct Node* root = (struct Node*)calloc(tree_count, sizeof(*root));
    Tree_Init(root);
    root->value = 67;

    struct Node* node1 = Create_New_Node(50);
    Insert_New_Elem(node1, root);

    struct Node* node2 = Create_New_Node(40);
    Insert_New_Elem(node2, root);

    struct Node* node3 = Create_New_Node(70);
    Insert_New_Elem(node3, root);

    Preorder_Dump(root);

    //log_file_close(f);
    return -1;
}

int log_file_create(FILE* file)
{
    file = fopen("logs1.log", "a");

    if (file == NULL)
    {
        return -EINVAL;
    }
    return 0;
}

int log_write(FILE* file, struct Node* cur_node)
{
    fprintf(file, BLUE "============================\n" RESET);
    fprintf(file, "Current Node Info\n");
    fprintf(file, "value = {%lg}, left_ child = <%p>, right_child = <%p>, parent = <%p>\n",
        cur_node->value,   cur_node->left,   cur_node->right,   cur_node->parent);
        
        return 0;
}
    
void log_file_close(FILE* file)
{
    fclose(file);
    file = NULL;
    return;
}

int Tree_Init(struct Node* root)
{
    SAY_FUNC("Tree_Init");
    if (root == NULL){MAKEPROBLEM(LIST_ERR_ZERO_PTR);}

    root->value  = POISON_VALUE;
    root->parent = NULL;
    root->left   = NULL;
    root->right  = NULL;
    
    return LIST_OK;
}

struct Node* Create_New_Node(double data)
{
    struct Node* new_node = (struct Node*)calloc(cnt_of_new_node, sizeof(*new_node));

    if (new_node == NULL){MAKEPROBLEM((struct Node*)LIST_ERR_ZERO_PTR);}

    new_node->value  = data;
    new_node->left   = NULL;
    new_node->right  = NULL;
    new_node->parent = NULL;

    return new_node;
}

struct Node* Insert_New_Elem( struct Node* new_tree_elem , struct Node* node)
{
    if(new_tree_elem == NULL)
    {
        return node; // just return tree ptr
    }

    if (node == NULL) 
    {
        return new_tree_elem;
    }

    printf(YELLOW "============================\n" RESET);
    SAY_FUNC("Insert_New_Elem");

    printf(PINK"Current Node Info:\n"RESET);
    printf("Node <%p>\n", node);
    printf("value = {%lg}, left_ child = <%p>, right_child = <%p>, parent = <%p>\n",
           node->value,          node->left,       node->right,       node->parent);
    
    printf(GREEN "New node INFO:\n" RESET);
    printf("New_node <%p>\n", new_tree_elem);
    printf("value = {%lg}, left_child = <%p>, right_child = <%p>, parent = <%p>\n",
           new_tree_elem->value, new_tree_elem->left, new_tree_elem->right, new_tree_elem->parent);
    

    if (new_tree_elem->value > node->value)
    {
        node->right = Insert_New_Elem(new_tree_elem, node->right);
        node->right->parent = node;

    }

    if (new_tree_elem->value < node->value)
    {
        node->left = Insert_New_Elem(new_tree_elem, node->left);
        node->left->parent = node;
    }

    printf("\n");
    printf("After checks:\n");

    printf(PINK"Current Node Info:\n"RESET);
    printf("Node <%p>\n", node);
    printf("value = {%lg}, left_ child = <%p>, right_child = <%p>, parent = <%p>\n",
           node->value,          node->left,       node->right,       node->parent);
    
    printf(GREEN "New node INFO:\n" RESET);
    printf("New_node <%p>\n", new_tree_elem);
    printf("value = {%lg}, left_ child = <%p>, right_child = <%p>, parent = <%p>\n",
           new_tree_elem->value, new_tree_elem->left, new_tree_elem->right, new_tree_elem->parent);
    printf(BLUE"--------------------------\n"RESET);

    return node;
}

int Tree_Dump(const struct Node* root)
{
    FILE* f = fopen("TreeDump.dot","w");
    //for()
    //{

    //}

    fprintf(f,"}");
    fclose(f);
    system("dot -Tpng -o TreeDump.png TreeDump.dot");
    return -1;
}

void Preorder_Dump(struct Node* cur_node)
{
    printf("(");
    printf("%lg",cur_node->value);
    if (cur_node->left != NULL)
    {
        //printf(BLUE "value = {%lg}, left_ child = <%p>, right_child = <%p>, parent = <%p>\n" RESET,
          // cur_node->value, cur_node->left, cur_node->right, cur_node->parent);
        Preorder_Dump(cur_node->left); 
    }

    if (cur_node->right != NULL)
    {
        //printf(PINK"value = {%lg}, left_ child = <%p>, right_child = <%p>, parent = <%p>\n" RESET,
        //cur_node->value, cur_node->left, cur_node->right, cur_node->parent);
        Preorder_Dump(cur_node->right);
    }
    printf(")");
}

// void Inorder_Dump(struct Node* cur_node)
// {
//     printf(" value = {%lg}, left_ child = <%p>, right_child = <%p>, parent = <%p>\n",
//            cur_node->value,   cur_node->left,   cur_node->right,   cur_node->parent);

// }

// void Postorder_Dump(struct Node* cur_node)
// {
//     printf(" value = {%lg}, left_ child = <%p>, right_child = <%p>, parent = <%p>\n",
//            cur_node->value,   cur_node->left,   cur_node->right,   cur_node->parent);
// }

void Check_Empty_Tree(struct Node* tree)
{
    if (tree == NULL)
    {
        printf("Tree is empty\n");
    }
    else
    {
        printf("Elements exist");
    }
}

void Tree_Clear(struct Node* node)
{
    if (node != NULL)
    {
        Tree_Clear(node->left);
        Tree_Clear(node->right);
    }
    free(node);
}