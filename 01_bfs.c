#include <stdio.h>
#include <malloc.h>

// узел очереди
typedef struct node {
	const void* now;
	struct node* skip;
} node_t;

// очередь для обхода дерева в ширину
typedef struct {
	node_t* head;
	node_t* tail;
} queue_t;

// бинарное дерево поиска
typedef struct tree {
	int key;
	struct tree* levo;
	struct tree* pravo;
} tree_t;

// вставка элементов в дерево 
tree_t* insert(tree_t** t, int k) {
	tree_t* a = *t;
	while (a != NULL) {
		if (k == a->key) {
			return a;
		} else if (k < a->key) {
			t = &a->levo;
			a = a->levo;
		} else {
			t = &a->pravo;
			a = a->pravo;
		}
	}
	a = (tree_t*)malloc(sizeof(tree_t));
	if (a != NULL) {
		a->key = k;
		a->levo = a->pravo = NULL;
		*t = a;
	}
	return a;
}

// инициализация очереди
void queue_init(queue_t* q) { 
	q->head = q->tail = NULL; 
}

// добавление в очередь
int queue_push(queue_t* c, const void* var) {
	node_t* a = (node_t*)malloc(sizeof(node_t));
	if (a != NULL) {
		a->now  = var;
		a->skip = NULL;
		if (c->head == NULL) {
			c->head = c->tail = a;
		} else {
			c->tail->skip = a;
			c->tail = a;
		}
	}
	return (a != NULL);
}

// удаление из очереди
void queue_pop(queue_t* b) {
	node_t* t;
	if (b->head != NULL) {
		t = b->head;
		b->head = b->head->skip;
		free(t);
		if (b->head == NULL) {
			b->tail = NULL;
		}
	}
}

// обращение к текущему узлу очереди
const void* queue_front(queue_t* q) {
	return q->head->now;
}

// сброс начала очереди
int queue_empty(queue_t* q) {
	return (q->head == NULL);
}

// обход дерева в ширину
void print_tree(FILE* _out, const tree_t* m){
	const tree_t* p;
	queue_t q;
	queue_init(&q);
	queue_push(&q, m);
	while (!queue_empty(&q)) {
		p = (const tree_t*)queue_front(&q);
		queue_pop(&q);
		fprintf(_out, "%d ", p->key);
		if (p->levo != NULL) {
			queue_push(&q, p->levo);
		}
		if (p->pravo != NULL) {
			queue_push(&q, p->pravo);
		}
	}
}

// основная функция
int main(void) {
	int i, b;
	tree_t* m = NULL;
	for(i = 0; i < 7; ++i) {
		scanf("%d", &b);
		insert(&m, b);
	}
	print_tree(stdout, m);
	return 0;
}