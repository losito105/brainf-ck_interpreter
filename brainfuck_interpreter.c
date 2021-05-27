#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *in  = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    if(in == NULL || out == NULL){
        printf("Error: Invalid input/output file\n");
        exit(-1);
    }

    fwrite("#include <stdio.h>\n", strlen("#include <stdio.h>\n"), 1, out);
    fwrite("int main(int argc, char *argv[]){\n", strlen("int main(int argc, char *argv[]){\n"), 1, out);
    fwrite("char array[30000] = {0};\n", strlen("char array[30000] = {0};\n"), 1, out);
    fwrite("char *ptr = array;\n", strlen("char *ptr = array;\n"), 1, out);

    char c = '\0';
    while(c != EOF){
        c = fgetc(in);
        switch(c){
            case '>':
                fwrite("ptr++;\n", 7, 1, out);
                break;
            case '<':
                fwrite("ptr--;\n", 7, 1, out);
                break;
            case '+':
                fwrite("(*(char *)ptr)++;\n", 18, 1, out);
                break;
            case '-':
                fwrite("(*(char *)ptr)--;\n", 18, 1, out);
                break;
            case '.':
                fwrite("putchar(*(char *)ptr);\n", 23, 1, out);
                break;
            case ',':
                fwrite("*(char *)ptr = getchar();\n", 26, 1, out);
                break;
            case '[':
                fwrite("while(*(char *)ptr){\n", 21, 1, out);
                break;
            case ']':
                fwrite("}\n", 2, 1, out);
                break;
        }
   }
   fwrite("}\n", 2, 1, out);

   fclose(in);
   fclose(out);

   system("gcc -o output -Wall output.c");
   system("./output");
}
