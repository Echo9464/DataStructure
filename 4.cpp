#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX_CHARS 256 // ASCII字符集
const int N =1000;

//InputFilename 输入的文件名
//FileContent   文本文件内容

//函数作用：用户输入一个文件名，函数返回该文件中的字符串
char * FileStrings()
{   static char FileString[N];// 静态变量存储在静态内存中，函数执行完毕后仍然存在
    char InputFilename[100];
    printf("请输入所要读取的文件名:");
    scanf("%s", InputFilename);
    FILE *file = fopen(InputFilename, "r");

    if (file == NULL){
        printf("输入文件无法打开"); 
        return NULL;
    }

    int index = 0;
    char i;
    while (index < N && (i = fgetc(file)) != EOF) {
        FileString[index] = i;
        index++;
    }
    FileString[index] = '\0';

    fclose(file);

    return FileString;
}

int main (){
    char * FileContent=FileStrings();//用FileContent存储文本文件内容

    return 0;
}