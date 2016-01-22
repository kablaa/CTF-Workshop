#include <stdio.h>
#include <stdio.h>

int x;
void func()
{
    char buf[10];
    puts("enter your name: ");
    scanf("%s", buf);
}
int main()
{
    puts("enter your age: ");
    scanf("%d",&x);
    func();
    return 0;
}
