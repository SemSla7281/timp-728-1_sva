#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

// бинарное дерево поиска
struct tree_node {
	int cnt;
	bool input;
	struct tree_node* levo;
	struct tree_node* pravo;
};

typedef struct tree_node* var;

// инициализация дерева
var catch_tree_noda(int k) {	
	var ptr = (var)malloc(sizeof(struct tree_node));
    ptr->cnt = k;
    ptr->levo = ptr->pravo = NULL;
    return ptr;
}

// рекурсивная вставка элементов в дерево
void insert(var* tree_uk, int k) {
    if ((*tree_uk) == NULL) {
        var ptr = catch_tree_noda(k);
        *tree_uk = ptr;
        return;
    }
    if (k < (*tree_uk)->cnt) {
        insert(&(*tree_uk)->levo, k);
    } else if (k > (*tree_uk)->cnt) {
        insert(&(*tree_uk)->pravo, k);
    }
}

// рекурсивный вывод дерева
void print_tree(var t) {	
	if (t != NULL) {
        print_tree(t->levo);
        print_tree(t->pravo);
        printf("%d ", t->cnt);
    }	
}

// основная функция
int main(void) {	
	var tree_root = NULL;
	int i, a;
	for (i = 0; i < 7; ++i) {
        scanf("%d", &a);
		insert(&tree_root, a);
    }
	print_tree(tree_root);
}