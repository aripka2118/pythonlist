#include <stdio.h>
#include <stdlib.h>

struct list {
    int *contents;
    size_t length; //Always points to after the last value
    size_t capacity;
};

void initList(struct list *myList){
    myList->length = 0;
    myList->capacity = 2;
    int *moreContents = calloc(myList->capacity, sizeof(int));
    if (moreContents == NULL) {
        fprintf(stderr, "no memory :(\n");
        exit(1);
    }
    myList->contents = moreContents;
}

void memorycopy(int *moreContents, int *source, size_t length) {
    for (size_t i = 0; i < length; i++) {
        moreContents[i] = source[i];
    }
}

void initcopy(struct list *myList, const struct list *copy) {
    myList->capacity = copy->capacity;
    myList->length = copy->length;
    int *moreContents = calloc(myList->capacity, sizeof(int));
    if (moreContents == NULL) {
        fprintf(stderr, "no memory:(\n");
        exit(1);
    }
    memorycopy(moreContents, copy->contents, myList->length);
    myList->contents = moreContents;
}

void printList(struct list *myList) {
    printf("{");
    for (size_t i = 0; i < myList->length; i++) {
        printf("%d%s", myList->contents[i], i + 1 < myList->length ? ", " : "");
    }
    printf("}\n");
}

void adjustmax(struct list *myList, size_t newObjects) {
    while (myList->capacity < myList->length + newObjects) {
        myList->capacity *= 2;
    }

    int *bigger = realloc(myList->contents, myList->capacity * sizeof(int));
    if (bigger == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    myList->contents = bigger;
}

void append(struct list *myList, int myNumbers[], size_t appendLength) {
    size_t currentLength = myList->length;
    adjustmax(myList, appendLength);
    for (size_t i = 0; i < appendLength; i++) {
        myList->contents[currentLength] = myNumbers[i];
        currentLength++;
    }
    myList->length = currentLength;
}

void clear(struct list *myList) {
    free(myList->contents);
    initList(myList);
}

int main(void) {
    struct list myNumbers; initList(&myNumbers);

    //FREE UP EVERYTHING!!!!
    free(myNumbers.contents);
    return 0;
}
