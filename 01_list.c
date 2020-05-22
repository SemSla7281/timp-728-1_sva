#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
    int value;          // значение, которое хранит узел 
    struct node* next;  // ссылка на следующий элемент списка
} node;

typedef struct list {
    struct node* head;  // начало списка
} list;


// инициализация пустого списка
void init(list* l);


// удалить все элементы из списка
void clean(list* l);


// проверка на пустоту списка
bool is_empty(list* l);

// поиск элемента по значению. вернуть NULL если эжемент не найден
node* find(list* l, int value);

// проверка поиска элемента
void check(list* l, int value);

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list* l, int value);


// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list* l, int value);

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node* n, int value);

// поиск элемента по индексу. вернуть NULL если эжемент не найден
node* find_ind(list* l, int j);

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_node(list* l, int value);


// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list* l);


int main() {
    list m;
    int n, a, e, h;

    // пункт 1
    (void)scanf("%d", &n);
    
    // пункт 2
    init(&m);    
    for (e = 1; e <= n; ++e) {
        (void)scanf("%d", &a);
        push_back(&m, a);
    }

    // пункт 3
    print(&m);
    printf("\n");

    // пункт 4
    for (e = 1; e <= 3; ++e) {
        (void)scanf("%d", &a);
        check(&m, a);
    }
    printf("\n");

    // пункт 5
    (void)scanf("%d", &a);
    push_back(&m, a);

    // пункт 6
    print(&m);
    printf("\n");

    // пункт 7
    (void)scanf("%d", &a);
    push_front(&m, a);

    // пункт 8
    print(&m);
    printf("\n");

    // пункт 9
    (void)scanf("%d", &a);
    (void)scanf("%d", &h);
    node* x = find_ind(&m, a);
    insert_after(x, h);

    // пункт 10
    print(&m);
    printf("\n");

    // пункт 11
    (void)scanf("%d", &a);
    remove_node(&m, a);

    // пункт 12
    print(&m);
    printf("\n");
    return 0;

    // пункт 13
    clean(&m);
    bool t = is_empty(&m);
    printf("%d ", t);
    return 0;
}

// инициализация пустого списка
void init(list* l) {
    l->head = NULL;
}


// удалить все элементы из списка
void clean(list* l) {
    node* tmp = NULL;
    while (l->head->next) {
        tmp = l->head;
        l->head = l->head->next;
        free(tmp);
    }
    free(l->head);
}

// проверка на пустоту списка
bool is_empty(list* l) {
    if (l->head) {
        return 1;
    } else {
        return 0;
    }
}

// поиск элемента по значению. вернуть NULL если эжемент не найден
node* find(list* l, int value)
{
    node* ind = l->head;
    while ((ind != NULL) && (ind->value != value)) {
        ind = ind->next;
    }
    return ind;
}

// проверка поиска элемента
void check(list* l, int value) {
    if (find(l, value) != NULL) {
        printf("1 ");
    } else {
        printf("0 ");
    }
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list* l, int value) {
    if (l->head != NULL) {
        node* tmp = l->head;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = (struct node*)malloc(sizeof(node));
        tmp->next->value = value;
        tmp->next->next = NULL;
        return 0;
    } else {
        node* tmp = (struct node*)malloc(sizeof(node));
        tmp->value = value;
        tmp->next = l->head;
        l->head = tmp;
        return 0;
    }
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list* l, int value) {
    node* tmp = (struct node*)malloc(sizeof(node));
    if (!tmp) {
        return 1;
    }
    tmp->value = value;
    tmp->next = l->head;
    l->head = tmp;
    return 0;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node* n, int value) {
    node* num = (struct node*)malloc(sizeof(node));
    num->value = value;
    num->next = n->next;
    n->next = num;
    return 0;
}

// поиск элемента по индексу. вернуть NULL если эжемент не найден
node* find_ind(list* l, int j) {
    node* tmp = l->head;
    int i = 0;
    while ((tmp != NULL) && (i != j - 1)) {
        tmp = tmp->next;
        ++i;
    }
    return tmp;
}

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_node(list* l, int value) {
    if (l->head == NULL) {
        return 1;
    } else {
        node* tmp = l->head;
        node* ind = NULL;
        while (tmp->next != NULL) {
            if (tmp->value == value) {
                if (ind == NULL) {
                    l->head = tmp->next;
                    free(tmp);
                    return 0;
                }
                ind->next = tmp->next;
                free(tmp);
                return 0;
            }
            ind = tmp;
            tmp = tmp->next;
        } 
        return 1;
    }
}


// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list* l) {
    node* num = l->head;
    while (num != NULL) {
        printf("%d ", num->value);
        num = num->next;
    }
}