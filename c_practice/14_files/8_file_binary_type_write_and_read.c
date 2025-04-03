#include <stdio.h>

struct point {
    int x, y;
};

int main() {
    struct point p;
    struct point p1;
    FILE *fptr = fopen("important.bin", "wb");

    for (int i = 0; i < 10; i++) {
        p.x = i;
        p.y = i + 1;
        fwrite(&p, sizeof(struct point), 1, fptr);
    }

    fclose(fptr);

    // Reading
    fptr = fopen("important.bin", "rb");

    for (int i = 0; i < 10; i++) {
        fread(&p1, sizeof(struct point), 1, fptr);
        printf("%d %d\n", p1.x, p1.y);
    }

    fclose(fptr);
    return 0;
}