#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Структура для хранения узла дерева.
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node {
    int key;
    struct node *levo; // ссылка на левого потомка
    struct node *pravo; // ссылка на правого потомка
    struct node *predok; // ссылка на предка
} node;

// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree {
	int value; 
	struct node *koren; // ссылка на корень дерева
	struct node *now;
	struct node *cnt; 
} tree;

// Определение элемента списка
typedef struct node_t {
	struct node *key; // узел дерева 
	struct node_t *sled; // ссылка на следующий элемент списка
} node_t;

// Определение списка
typedef struct list {
	struct node_t *golova; // начало списка
	struct node_t *end; // конец списка
	struct node_t *now; // текущее
} list;

// Проверка списка на пустоту
bool is_empty_spisok(list *l) {
	if (l->golova == NULL) {
		return 1;
	} else {
		return 0;
	}
}

// Инициализация пустого списка
void init_spisok(list *l) {
	l->golova = NULL;
}
// Инициализация дерева
void init(tree* t) {
	t->koren = NULL;
}

// Функция удаления элементов из списка
void clean_spisok(list *l) {
	while (l->golova != NULL) {
		l->now = l->golova;
		l->golova = l->golova->sled;
		free(l->now);
	}
}

// вставка значения в конец списка
// 0 - успешно
int add(list *l, node *t) {
	l->end = l->golova;
	if (l->end != NULL) {
		while (l->end->sled != NULL) {
			l->end = l->end->sled;
		}
		l->now = malloc(sizeof(node_t));
		l->now->key = t;
		l->now->sled = NULL;
		l->end->sled = l->now;
		return 0;
	} else {
		l->now = malloc(sizeof(node_t));
		l->now->key = t;
		l->now->sled = NULL;
		l->golova = l->now;
	}
}

// удалить первый элемент из списка с указанным значением
// 0 - успешно
node_t *del(list *l) {
	node_t *cnt = NULL;
	if (l->golova == NULL) {
		printf("_");
		return 0;
	}
	cnt = l->golova;
	l->golova = l->golova->sled;
	return cnt;
}

// Функция возврата указателя на корень
node *return_koren (tree *q) {
	return q->koren;
}

// Рекурсивная функция для удаления дерева
node *wash(node *q) {
	if (q != NULL) {
		wash(q->levo);
		wash(q->pravo);
		if (q->predok != NULL) {
			q->predok = NULL;
		}
		if (q->levo != NULL) {
			q->levo = NULL;
		}
		if (q->pravo != NULL) {
			q->pravo = NULL;
		}
		free(q);
	}
	return NULL;
}
 
// Удалить все элементы из дерева
void clean(tree* t) {
	node *tru_koren = return_koren(t);
	wash(tru_koren);
	t->koren = NULL;
}

// Поиск элемента по значению. Вернуть NULL если элемент не найден
node* find(tree* t, int value) {
	t->now = t->koren;
	while(t->now->key != value) {
		if(t->now->key > value) {
			t->now = t->now->levo;
		} else {
			t->now = t->now->pravo;
		}
		if (t->now == NULL) {
			return NULL;
		}
	} 
	return t->now;
}

// Функция вывода количества элементов списка
void print_list(tree *t) {
	printf("%d", t->value);
}

// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
int insert(tree* t, int value) {
	node *koren2 = t->koren, *koren3 = NULL;
	t->now = malloc(sizeof(node));
	t->now->key = value;
	if (t->koren == NULL) {
		t->now->predok = NULL;
		t->now->levo = NULL;
		t->now->pravo = NULL;
		t->koren = t->now;
		t->value = 1;
		return 0;
	}
	while (koren2 != NULL) {
		koren3 = koren2;
		if (value == koren2->key) {
			return 1;
		}
		if (value < koren2->key) {
			koren2 = koren2->levo;
		} else {
			koren2 = koren2->pravo;
		}
	}
	t->now->predok = koren3;
	t->now->levo = NULL;
	t->now->pravo = NULL;
	if (value < koren3->key) {
		koren3->levo = t->now;
        t->value++;
		return 0;
	}
	if (value > koren3->key) {
		koren3->pravo = t->now;
		t->value++;
		return 0;
	}
}

// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элемента
int remove_min(node* n) {
	int a;
	node *NOW = n;
	while (NOW->levo != NULL) {
		NOW = NOW->levo;
	}
	a = NOW->key;
	if (NOW->pravo != NULL) {
		if (a < NOW->predok->key) {
			NOW->predok->levo = NOW->pravo;
			free(NOW);
			return a;
		} else {
			NOW->predok->pravo = NOW->pravo;
			free(NOW);
			return a;
		}
	} else {
		if (a < NOW->predok->key) {
			NOW->predok->levo = NULL;
			free(NOW);
			return a;
		} else {
			NOW->predok->pravo = NULL;
			free(NOW);
			return a;
		}
	}
}

// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node(tree* t, int value) {
	int a;
	node *rmdir = find(t, value);
	if (rmdir == NULL) {
		return 1;
	}
	if (rmdir->levo == NULL && rmdir->pravo == NULL) {
		if (rmdir != t->koren) {
			if (rmdir->key < rmdir->predok->key) {
				rmdir->predok->levo = NULL;
				free(rmdir);
				t->value--;
				return 0;
			} else {
				rmdir->predok->pravo = NULL;
				free(rmdir);
				t->value--;
				return 0;
			}
		} else {
			free(rmdir);
			t->koren = NULL;
			t->value = 0;
			return 0;
		}
	}
	if (rmdir->levo == NULL && rmdir->pravo != NULL) {
		if (rmdir != t->koren) {
			if (rmdir->key < rmdir->predok->key) {
				rmdir->predok->levo = rmdir->pravo;
				rmdir->pravo->predok = rmdir->predok;
				free(rmdir);
				t->value--;
				return 0;
			} else {
				rmdir->predok->pravo = rmdir->pravo;
				rmdir->pravo->predok = rmdir->predok;
				free(rmdir);
				t->value--;
				return 0;
			}
     	} else {
			rmdir->pravo->predok = NULL;
			t->koren = rmdir->pravo;
			free(rmdir);
	    	t->value--;
			return 0;
		}
	}
	if (rmdir->levo != NULL && rmdir->pravo == NULL) {
		if (rmdir != t->koren) {
			if (rmdir->key < rmdir->predok->key) {
				rmdir->predok->levo = rmdir->levo;
				rmdir->levo->predok = rmdir->predok;
				free(rmdir);
				t->value--;
				return 0;
			} else {
				rmdir->predok->levo = rmdir->levo;
				rmdir->levo->predok = rmdir->predok;
				free(rmdir);
				t->value--;
				return 0;
			} 
		} else {
			rmdir->levo->predok = NULL;
			t->koren = rmdir->levo;
			free(rmdir);
			t->value--;
			return 0;
		}		
	}
	if (rmdir->pravo != NULL && rmdir->levo != NULL) {
		a = remove_min(rmdir->pravo);
		rmdir->key = a;
		t->value--;
		return 0;
	}
}

// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно 
int rotate_right(node* n) {
	node *b = n;
	node *a = b->levo;
	node *c = a->pravo;
	a->predok = b->predok;
	if (b->predok != NULL) {
		if (b->predok->key > b->key) {
			b->predok->levo = a;
		} else {
			b->predok->pravo = a;
		}
	}
	if (c != NULL) {
		c->predok = b;
	}
	b->levo = c;
	b->predok = a;
	a->pravo = b;
	return 0;
}

int rotate_koren_pravo(tree* t) {
	rotate_right(t->koren);
	if (t->koren->predok != NULL) {
		t->koren = t->koren->predok;
	}
	return 0;
}

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_left(node* n) {
	node *a = n;
	node *b = a->pravo;
	node *c = b->levo;
	b->predok = a->predok;
	if (a->predok != NULL) {
		if (a->predok->key > a->key) {
			a->predok->levo = b;
		} else {
			a->predok->pravo = b;
		}
	}
	if (c != NULL) {
		c->predok = a;
	}
	a->pravo = c;
	a->predok = b;
	b->levo = a;
	return 0;
}
int rotate_koren_levo(tree *t) {
	rotate_left(t->koren);
	if (t->koren->predok != NULL) {
		t->koren = t->koren->predok;
	}
	return 0;
}

// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке. 
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _. 
// Если дерево пусто, вывести -
void print(node* n);

// Вывести все значения дерева t, аналогично функции print
void print_tree(tree* t) {
	if (t->koren == NULL) {
		printf("-\n");
		return;
	}
	struct list first_l;
	struct list second_l;
	int j=0;
	init_spisok(&first_l);
	init_spisok(&second_l);
	add(&first_l, t->koren);
	while (!is_empty_spisok(&first_l) || !is_empty_spisok(&second_l)) {
		while (!is_empty_spisok(&first_l)) {
			node_t *NOW = del(&first_l);
			if (NOW->key == NULL) {
				printf("_ ");
				add(&second_l, NULL);
				add(&second_l, NULL);
			} else {
				j++;
				printf("%d", NOW->key->key);
				printf(" ");
				add(&second_l, NOW->key->levo);
				add(&second_l, NOW->key->pravo);
			}
		}
		printf("\n");
		if (j == t->value) {
			return;
		}
		while (!is_empty_spisok(&second_l)) {
			node_t *NOW = del(&second_l);
			if(NOW->key == NULL) {
				printf("_ ");
				add(&first_l, NULL);
				add(&first_l, NULL);
			} else {
				j++;
				printf("%d", NOW->key->key);
				printf(" ");
				add(&first_l, NOW->key->levo);
				add(&first_l, NOW->key->pravo);
			}
		}
		printf("\n");
		if (j == t->value) {
			return;
		}
	}
}


int main() {
	struct tree m;
	int i, b, m1, m2;

	// пункт 1
	init(&m);
	for (i=0; i<4; ++i) {
		scanf("%d", &b);
		insert(&m, b);
	}
    
	// пункт 2
	print_tree(&m);
	printf("\n");

	// пункт 3
	for (i=0; i<3; ++i) {
		scanf("%d", &b);
		insert(&m, b);
	}
	
	// пункт 4
	print_tree(&m);
	printf("\n");
	
	// пункт 5
	scanf("%d", &m1);
	node *basket = find(&m, m1);
	if(basket==NULL) {
		printf("-");
		printf("\n");
	} else {
		if (basket->predok != NULL) {
			printf("%d", basket->predok->key);
			printf(" ");
		} else {
            printf("_ ");
        }
		if (basket->levo) {
			printf("%d", basket->levo->key);
		} else {
			printf("_");
		}
		printf(" ");
		if(basket->pravo) {
		printf("%d", basket->pravo->key);
		} else {
			printf("_");
		}
		printf("\n");
	}
	printf("\n");

	// пункт 6
	scanf("%d", &m2);
	basket = find(&m, m2);
	if(basket==NULL) {
		printf("-");
		printf("\n");
	} else {
		if (basket->predok != NULL) {
			printf("%d", basket->predok->key);
			printf(" ");
		} else {
            printf("_ ");
        }
		if (basket->levo) {
			printf("%d", basket->levo->key);
		} else {
			printf("_");
		}
		printf(" ");
		if(basket->pravo) {
			printf("%d", basket->pravo->key);
		} else {
			printf("_");
		}
		printf("\n");
	}
	printf("\n");

	// пункт 7
	scanf("%d", &m1);
	remove_node(&m, m1);

	// пункт 8
	print_tree(&m);
	printf("\n");
		
	// пункт 9
	node *tru_koren = return_koren(&m);
	if (tru_koren != NULL) {
		while (tru_koren->pravo != NULL) {
			rotate_koren_levo(&m);
			tru_koren = return_koren(&m);
		}
	}
	printf("\n");

	// пункт 10	
	print_tree(&m);
	
	// пункт 11
	tru_koren = return_koren(&m);
	if (tru_koren != NULL) {
		while (tru_koren->levo != NULL) {
			rotate_koren_pravo(&m);
			tru_koren = return_koren(&m);
		}
	}
	printf("\n");
	// пункт 12	
	print_tree(&m);
	printf("\n");	

	// пункт 13
	print_list(&m);
	printf("\n\n");

	// пункт 14
	clean(&m);

	// пункт 15
	print_tree(&m);
	return 0;
}
