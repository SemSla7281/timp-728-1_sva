#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list {
    struct node* head;  // начало списка
    struct node* tail;  // конец списка
} list;

typedef struct node {
    int value;          // значение, которое хранит узел 
    struct node* next;  // ссылка на следующий элемент списка
    struct node* prev;  // ссылка на предыдущий элемент списка
} node;

// инициализация пустого списка
void init(list* l);

// удалить все элементы из списка
void clean(list* l);

// проверка на пустоту списка
bool is_empty(list* l);

// поиск элемента по значению. вернуть NULL если элемент не найден
node* find(list* l, int value);

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list* l, int value);

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list* l, int value);

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list* l, node* n, int value);

// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(list* l, node* n, int value);

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_first(list* l, int value);

// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_last(list* l, int value);

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list* l);

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list* l);

// Собственная функция для указателей на функцию (пункты 9 и 11)
node* catch_in(list* l, int value);

// Собственная функция проверки наличия элемента (пункт 4)
void check_boolean(list* l, int value);

int main() {
    list m;
    int q, n, a, e;   

    // пункт 1
    init(&m);
    scanf("%d", &n);

    // пункт 2
    for (q = 0; q < n; ++q) {
        scanf("%d", &a);        
        push_back(&m, a);
    }
    // пункт 3
    print(&m);
    printf("\n");

    // пункт 4
    for (q = 1; q <= 3; ++q) {
        scanf("%d", &a);        
        check_boolean(&m, a);
    }
    printf("\n");

    // пункт 5
    scanf("%d", &a);    
    push_back(&m, a);

    // пункт 6
    print_invers(&m);
    printf("\n");

    // пункт 7
    scanf("%d", &a);    
    push_front(&m, a);

    // пункт 8
    print(&m);
    printf("\n");

    // пункт 9
    scanf("%d", &a);    
    scanf("%d", &e);
    node* paste_head = catch_in(&m, a);
    insert_after(&m, paste_head, e);

    // пункт 10
    print_invers(&m);
    printf("\n");

    // пункт 11
    scanf("%d", &a);    
    scanf("%d", &e);    
    node* paste_before_head = catch_in(&m, a);
    insert_before(&m, paste_before_head, e);

    // пункт 12
    print(&m);
    printf("\n");

    // пункт 13
    scanf("%d", &a);    
    remove_first(&m, a);

    // пункт 14
    print_invers(&m);
    printf("\n");

    // пункт 15
    scanf("%d", &a);
    remove_last(&m, a);

    // пункт 16
    print(&m);
    printf("\n");

    // пункт 17
    clean(&m);
    return 0;
}

// инициализация пустого списка
void init(list* l) {
    l->head = l->tail = NULL;
}

// удалить все элементы из списка
void clean(list* l) {
    while (l->head->next) {
        l->head = l->head->next;
        free(l->head->prev);
    }
    free(l->head);
}

// проверка на пустоту списка
bool is_empty(list* l) {
    node* ukaz = l->head;
    if (ukaz) {
        return 1; // Список непустой
    }
}
// поиск элемента по значению. вернуть NULL если элемент не найден
node* find(list* l, int value) {
    node* ukaz = l->head;
    while ((ukaz != NULL) && (ukaz->value != value)) {
        ukaz = ukaz->next;
    }
    return ukaz;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list* l, int value) {
    if (is_empty(l)) {
        node* ukaz = l->head;
        while (ukaz->next != NULL) {
            ukaz = ukaz->next;
        }
        ukaz->next = calloc(1, sizeof(node));
        ukaz->next->prev = ukaz;
        l->tail = ukaz->next;
        ukaz->next->value = value;
        ukaz->next->next = NULL;
        return 0;
    } else {
        node* ukaz = calloc(1, sizeof(node));
        ukaz->value = value;
        ukaz->next = l->head;
        l->head = ukaz;
        l->head->prev = NULL;
        l->tail = ukaz;
        return 0;
    }
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list* l, int value) {
    node* ukaz = calloc(1, sizeof(node));
    if (!ukaz) {
        return -1;
    }
    ukaz->value = value;
    ukaz->next = l->head;
    ukaz->prev = NULL;
    l->head = ukaz;
    l->head->next->prev = ukaz;
    return 0;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list* l, node* n, int value) {
    if (n && n->next) {
        node* ukaz = calloc(1, sizeof(node));
        ukaz->value = value;
        ukaz->next = n->next;
        ukaz->prev = n;
        n->next = ukaz;
        n->next->next->prev = ukaz;
        return 0;
    } else {
        push_back(l, value);
    }
    return -1;
}

// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(list* l, node* n, int value) {
    if (n && n->prev) {
        node* ukaz = calloc(1, sizeof(node));
        ukaz->value = value;
        ukaz->prev = n->prev;
        ukaz->next = n;
        n->prev = ukaz;
        n->prev->prev->next = ukaz;
        return 0;
    } else {
        push_front(l, value);
    }
    return -1;
}

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_first(list* l, int value) {
    if (l->head == NULL) {
        return -1;
    }
    node* ukaz = l->head;
    while (ukaz->next) {
        if (ukaz->value == value) {
            if (ukaz->prev == NULL) {
                l->head = ukaz->next;
                ukaz->next->prev = NULL;
                free(ukaz);
                return 0;
            }
            ukaz->prev->next = ukaz->next;
            ukaz->next->prev = ukaz->prev;
            free(ukaz);
            return 0;
        }
        ukaz = ukaz->next;
    }
    if (ukaz->value == value) {
        l->tail = ukaz->prev;
        ukaz->prev->next = NULL;
        free(ukaz);
        return 0;
    }
    return -1;
}

// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_last(list* l, int value) {
    if (l->head == NULL) {
        return -1;
    }
    node* ukaz = l->tail;
    while (ukaz->prev) {
        if (ukaz->value == value) {
            if (ukaz->next == NULL) {
                l->tail = ukaz->prev;
                l->tail->next = NULL;
                free(ukaz);
                return 0;
            }
            ukaz->next->prev = ukaz->prev;
            ukaz->prev->next = ukaz->next;
            free(ukaz);
            return 0;
        }
        ukaz = ukaz->prev;
    }
    if (ukaz->value == value) {
        l->head = ukaz->next;
        ukaz->next->prev = NULL;
        free(ukaz);
        return 0;
    }
    return -1;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list* l) {
    node* ukaz = l->head;
    while (ukaz != NULL) {
        printf("%d ", ukaz->value);
        ukaz = ukaz->next;
    }
}

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list* l) {
    node* ukaz = l->tail;
    while (ukaz != NULL) {
        printf("%d ", ukaz->value);
        ukaz = ukaz->prev;
    }
}

// Собственная функция для указателей на функцию (пункты 9 и 11)
node* catch_in(list* l, int value) {
    if (l->head) {
        node* ukaz = l->head;
        int cnt = 0;
        while ((ukaz != NULL) && (cnt != value - 1)) {
            ukaz = ukaz->next;
            cnt++;
        }
        return ukaz;
    }
    return NULL;
}

// Собственная функция проверки наличия элемента (пункт 4)
void check_boolean(list* l, int value) {
    if (find(l, value) != NULL) {
        printf("1 ");
    } else {
        printf("0 ");
    }
}