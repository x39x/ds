#include "list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
        int age;
        struct list_head list;
} person;

int main(int argc, char *argv[]) {
        person *p;
        person person_head;
        person *pos;
        person *n;
        INIT_LIST_HEAD(&person_head.list);

        for (int i = 1; i < 6; i++) {
                p = (person *)malloc(sizeof(person));
                p->age = i * 10;
                list_add(&p->list, &person_head.list);
        }
        list_for_each_entry_safe(pos, n, &person_head.list, list) {
                if (pos->age == 30) {
                        list_del(&(pos->list));
                }
        }

        list_for_each_entry_safe_reverse(pos, n, &person_head.list, list) {
                printf("%d\n", pos->age);
        }
        return 0;
}
