#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

// бинарное дерево поиска
typedef struct tree_node {
	int cnt;
	bool input;
	struct tree_node* levo;
	struct tree_node* pravo;
} tree_node_t;

// вставка элементов в дерево
tree_node_t* insert(tree_node_t** t, int k) {	
	tree_node_t* a = *t;
	while (a != NULL) {
		if (k == a->cnt) {
			return a;
		} else if (k < a->cnt) {
			t = &a->levo;
			a = a->levo;
		} else {
			t = &a->pravo;
			a = a->pravo;
		}
	}
	a = (tree_node_t*)malloc(sizeof(tree_node_t));
	if (a != NULL) {
		a->cnt = k;
		a->levo = a->pravo = NULL;
		*t = a;
	}
	return a;
}

// реализация стека
struct node {
	void* member;
	struct node* skip;
};

typedef struct node* stack;

// инициализация стека
stack get_noda(void* member){
	stack tmp = (stack)malloc(sizeof(struct node));	
	tmp->member = member;
	tmp->skip = NULL;
	return tmp;
}

// вставка элемента в стек
void push_into_stack(stack* high_uk, void* cnt) {	
	stack tmp = get_noda(cnt);
	if (*high_uk == NULL) {		
		tmp->skip = NULL;
		*high_uk = tmp;
		return;
	}
	tmp->skip = *high_uk;
	*high_uk = tmp;
}

// проверка стека на пустоту
bool check_stack(stack top) {
	if (top == NULL) {
		return true;
	}
	else {
		return false;
	}
}

// извлечение элемента из стека
void* pop_from_stack(stack* high_uk) {
	if (!check_stack(*high_uk)) {
		stack tmp = *high_uk;
		*high_uk = tmp->skip;
		tmp->skip = NULL;
		return tmp->member;
	}
}

// вывод дерева
void print_tree(tree_node_t* tree) {	
	stack high_stack = NULL;	
	tree_node_t* now = tree;
	do {
		while (now != NULL) {
			printf("%d ", now->cnt);
			push_into_stack(&high_stack, (void*)now->pravo);
			now = now->levo;
		}		
		if (!check_stack(high_stack)) {
			now = pop_from_stack(&high_stack);		
		}
	} while (!check_stack(high_stack) || now != NULL);
}

// основная функция
int main(void) {	
	tree_node_t* tree_root = NULL;
	int i, a;
	for (i = 0; i < 7; ++i) {
        scanf("%d", &a);
		insert(&tree_root, a);
    }
	print_tree(tree_root);
}