#include <stdio.h>

int main(void) {
        // int a;
        // printf("Enter your age: ");
        // scanf("%d", &a);
        // printf("Your age is %d\n", a);

        char buffer[100];
        fputs("Enter your age: ", stdout);
        fflush(stdout);
        fgets(buffer, sizeof(buffer), stdin);
        printf("Your age is %s!\n", buffer);
        return 0;
}
