#include<stdio.h>
#include<stdlib.h>
#define MAX_CHARS 256 // ASCII字符集
const int N =1000;

// 结点结构定义
typedef struct Node {
    char character;
    int freq;
    struct Node *left, *right;
} Node;

// 创建一个新的结点
Node* createNode(char character, int freq) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = character;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 统计字符数组中字符的词频
void countFrequency(const char* content, int freq[]) {
    for (int i = 0; content[i] != '\0'; i++) {
        freq[(unsigned char)content[i]]++;
    }
}

// 构建哈夫曼树
Node* buildHuffmanTree(int freq[]) {
    Node *nodes[MAX_CHARS], *temp;
    int nodeCount = 0;

    // 创建包含字符和频率的结点
    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            nodes[nodeCount++] = createNode((char)i, freq[i]);
        }
    }

    // 构建哈夫曼树
    while (nodeCount > 1) {
        // 找到频率最小的两个结点
        int minIdx1 = 0, minIdx2 = 1;
        for (int i = 0; i < nodeCount; i++) {
            if (nodes[i]->freq < nodes[minIdx1]->freq) {
                minIdx2 = minIdx1;
                minIdx1 = i;
            } else if (nodes[i]->freq < nodes[minIdx2]->freq) {
                minIdx2 = i;
            }
        }

        // 合并两个最小频率的结点
        temp = createNode('$', nodes[minIdx1]->freq + nodes[minIdx2]->freq);
        temp->left = nodes[minIdx1];
        temp->right = nodes[minIdx2];

        // 删除已合并的结点
        nodes[minIdx1] = temp;
        nodes[minIdx2] = nodes[--nodeCount];
    }

    return nodes[0]; // 返回根结点
}

// 保存字符对应的哈夫曼编码
void saveHuffmanCode(Node* root, char* huffmanCode, int top) {
    if (root->left) {
        huffmanCode[top] = '0';
        saveHuffmanCode(root->left, huffmanCode, top + 1);
    }

    if (root->right) {
        huffmanCode[top] = '1';
        saveHuffmanCode(root->right, huffmanCode, top + 1);
    }

    if (!root->left && !root->right) {
        huffmanCode[top] = '\0';
        printf("字符 %c 的哈夫曼编码为: %s\n", root->character, huffmanCode);
    }
}
static char FileString[N];// 静态变量存储在静态内存中，函数执行完毕后仍然存在

char * FileStrings()
{   
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
    char * FileContent=FileStrings();
    int freq[MAX_CHARS] = {0}; // 初始化频率数组
    countFrequency(FileContent, freq); // 统计词频

    Node* root = buildHuffmanTree(freq); // 构建哈夫曼树

    char huffmanCode[MAX_CHARS];
    saveHuffmanCode(root, huffmanCode, 0); // 保存哈夫曼编码
    return 0;
}