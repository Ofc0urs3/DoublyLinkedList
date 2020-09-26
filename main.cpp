#include <iostream>

#include"my.h"

int main(void)
{
    List str;
    const char* filename = "InputA.txt";
    FILE* fin = fopen(filename, "r");

    if(fin == nullptr)
    {
        return -2;
    }


    int res = str.read(fin);
    if (res < 0)
    {
        switch(res)
        {
        case -1:
                printf("Memory fail\n");
                break;
        default:
                printf("Unknown error: %d\n",res);
                break;
        }
        fclose(fin);
        str.clear();
    }
    fclose(fin);

    printf("%s\n","File print:");
    str.print();

    List str1;

    printf("%s\n","New One Equal to Prev:");
    str1 = str;
    str1.print();


    str.push_right("GGGG");
    str.push_left("OOOO");
    printf("%s\n", "Add Some New Elements:");
    str.print();

    printf("Delete head:\n");
    str.removeAt(0);
    str.removeAt(5);
    str.removeAt(4);
    str.print();
    
    printf("%s\n","Sorted");
    int (*comp)(Node*, Node*) = comparator;
    str.quickSort(comp);
    str.print();

    
    return 0;
}
