#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct item {
    int info;
    struct list_head list_member;
};

void add_item(int info, struct list_head* head) {

    struct item* pitem = (struct item*) malloc(sizeof(struct item));
    assert(pitem != NULL);

    pitem->info = info;
    INIT_LIST_HEAD(&pitem->list_member);
    list_add(&pitem->list_member, head);

}

void display(struct list_head *head) {
    struct list_head* iter;
    struct item* objPtr;

    __list_for_each(iter, head) {
        objPtr = list_entry(iter, struct item, list_member);
        printf("%d ", objPtr->info);
    }
    printf("\n");
}

int find_first_and_delete(int arg, struct list_head *head) {
    struct list_head *iter;
    struct item* objPtr;

    __list_for_each(iter, head) {
        objPtr = list_entry(iter, struct item, list_member);
        if (objPtr->info == arg) {
            list_del(&objPtr->list_member);
            free(objPtr);
            return 1;
        }
    }

    return 0;
}

void delete_all(struct list_head *head) {
    struct list_head* iter;
    struct item* objPtr;
                
    redo:
    __list_for_each(iter, head) {
        objPtr = list_entry(iter, struct item, list_member);
        list_del(&objPtr->list_member);
        free(objPtr);
        goto redo;
    }
}

int main(int argc, char* argv[]) {

    LIST_HEAD(listHead);

    add_item(10, &listHead);
    add_item(20, &listHead);
    add_item(25, &listHead);
    add_item(30, &listHead);

    display(&listHead);
    find_first_and_delete(20, &listHead);
    display(&listHead);
    delete_all(&listHead);
    display(&listHead);

    return 0;
}
