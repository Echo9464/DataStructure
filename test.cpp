#include <iostream> 
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <math.h>
#include <vector>
#include <utility>

using namespace std;

const int n=512;

//输出随机复制后的数组
void print(vector<int>& array,int n){
    int flag = 0;
    cout << "随机赋值后的数组：" << endl;
    for(int i = 0; i < n; ++i) {
        flag++;
        if(flag%10==0) {cout <<"第"<<setw(3)<<i+1<<"个人的得分为:"<< setw(3) << array[i]<<endl;}
        else cout <<"第"<<setw(3)<<i+1<<"个人的得分为:"<< setw(3) << array[i]<<" ";
        if(flag==n) cout <<endl;
    }
}

void heapify(vector<int>& array,int n,int i) {
    int largest = i;  // 假设根节点最大
    int left = 2 * i + 1; // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点比根节点大，则更新最大值索引
    if (left < n && array[left] > array[largest])
        largest = left;

    // 如果右子节点比当前最大值大，则更新最大值索引
    if (right < n && array[right] > array[largest])
        largest = right;

    // 如果最大值不是根节点，则交换并继续堆化
    if (largest != i) {
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;
        heapify(array, n, largest);
    }
}

void buildHeap(vector<int>& array,int n) {
    // 从最后一个非叶子节点开始向上构建堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }
}

void printArray(vector<int>& array,int n){
    for (int i = 0; i < n; ++i)
        printf("%d ", array[i]);
    printf("\n");
}

void Heapsearch(vector<int>& array,int n){
    int arr[512]={0};
    for (int i=0; i<n; i++){
        arr[i]=array[i];
    }
    int Pmax=0;
    int Pmaxx=0;
    printf("原始数组: \n");
    printArray(array, n);

    buildHeap(array, n);
    printf("%d\n",array[0]);
    printf("转换为堆后的数组: \n");
    printArray(array, n);
    for(int i = 0; i < n; i++){
       if (arr[i] == array[0]) {
            Pmax = i;
            break;
        }
    }
    // 查找次高分在原数组中的匹配索引
    for(int i = 0; i < n; i++){
        if (arr[i] == array[1]&&i!=Pmax) {
            Pmaxx = i;
            break;
        }
    }
    cout<<"使用堆排序查找法时的结果:"<<endl;
    cout<<"第"<<setw(3)<<Pmax +1<<"个人得最高分,"<<"最高分为:"<<array[0]<<endl;
    cout<<"第"<<setw(3)<<Pmaxx+1<<"个人得次高分,"<<"次高分为:"<<array[1]<<endl;
}



int main() {
    vector<int> array(n);
    srand(static_cast<unsigned int>(time(0)));
    // 为数组赋随机整数值
    for (int i = 0; i < n; ++i) {
        array[i] = rand() % 1000; // 生成0~999之间的随机数
    }
    print(array,n);
    cout << endl;
    Heapsearch(array,n);
    // printf("原始数组: \n");
    // printArray(array, n);

    // buildHeap(array, n);
    // printf("%d\n",array[0]);
    // printf("转换为堆后的数组: \n");
    // printArray(array, n);

    return 0;
}
