#include <stdio.h>

#pragma pack(1)

struct store{
    double price;   // 8 bytes
    union {
        struct {    // 20 bytes (this will taken)
            char *title;    // 8 bytes
            char *author;   // 8 bytes
            int num_pages;  // 4 bytes
        } book;

        struct {    // 16 bytes (this will not be taken)
            int color;      // 4 bytes
            int size;       // 4 bytes
            char *design;   // 8 bytes
        } shirt;
    } item;
}; // 8 + 20 = 28 bytes


int main() {
    struct store s;
    s.item.book.title = "Book 1";
    s.item.book.author = "Author 1";
    s.item.book.num_pages = 223;
    printf("%s\n", s.item.book.title);
    printf("size of struct is %lu bytes\n", sizeof(s));
    return 0;
}