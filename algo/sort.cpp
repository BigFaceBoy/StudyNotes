#include <iostream>
#include <stdlib.h>

/**
 * 所有排序都以从小到大的顺序排列 
 **/

static void swap(int* array, int i, int j){
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

static void printArray(int* array, int len){
    std::cout<< "array:";
    for (int i = 0; i < len; i++)
    {
        std::cout << array[i]<<" ";
    }
    std::cout<<std::endl;
}

static void bubbleSort(int *array, int len){
    for (int i = 0; i < len; i++){
        for(int j = i + 1; j < len; j++){
            if(array[i] > array[j]){
                swap(array, i , j);
            }
        }
    }
}

static void bubbleSortBetter(int *array, int len){
    int flag = true;
    for (int i = 0; i < len && flag; i++){
        flag = false;
        for(int j = i + 1; j < len; j++){
            if(array[i] > array[j]){
                swap(array, i , j);
                flag = true;
            }
        }
    }
}

//每次从序列中找到最小的一个，放到未排序的第一个位置
static void selectSort(int *array, int len){
    int minIndex;
    for(int i = 0; i < len; i++){
        minIndex = i;
        for(int j = i+1; j < len; j++){
            if(array[minIndex] > array[j]){
                minIndex = j;
            }
        }
        swap(array, minIndex, i);
    }
}

//插入排序 当序列基本有序时，插入排序效类较高

static void insertSort(int *array, int len){
    for(int i = 1; i < len; i++){
        int j = i;
        while (j > 0 )
        {
            if(array[j] < array[j-1]){
                swap(array, j , j-1);
                j--;
            }else{
                break;
            }
        }
    }    
}

//在插入排序的基础上，创造基本有序的条件：将距离一定的数据记为一组，对每个组进行排序，最后进行一次插入排序
static void shellSort(int *array, int len){
    int stride  = len;
    while (stride >= 1)
    {
        stride = stride / 3;
        if(stride == 0) break;
        for(int i = 0; i < len; i = i+stride){
            int j = i + stride;
            while (j > 0 && j < len)
            {
                if(array[j] < array[j - stride]){
                    swap(array, j , j - stride);
                    j -= stride;
                }else{
                    break;
                }
            }
        }
    }
}

/**
 * 堆排序
 * 大顶堆：每个节点的值都大于其左右孩子节点的值
 * 小顶堆：每个节点的值都小于其左右孩子节点的值
 * 
 * 堆排序原理：将待排序的序列构造成一个大顶堆(小顶堆)，此时整个序列的最大值
*/
static void heapSprt(){}


/**
 * 快速排序优化方案：
 * 1、优化 pivot 的选取策略
 * 2、优化不必要的交换
 * 3、优化小数组时的排序方案:当数组长度小于某个值时，使用插入排序
 * 4、优化递归操作
*/

// pivot 选取策略：三数曲中
static doPartition1(int* array, int begin , int end){
    //三数取中
    int mid = begin + (end - begin)/2;
    if(array[begin] > array[end])
        swap(array,begin , end);
    if(array[mid] > array[end])
        swap(array,mid , end);
    if(array[mid] >array[begin])
        swap(array, begin, mid);
    int pivot = array[begin];

    while (begin < end)
    {
        while (begin < end && array[end] >= pivot)
        {
            end--;
        }
        swap(array, begin, end);
        while (begin < end && array[begin] <= pivot)
        {
            begin++;
        }
        swap(array,begin, end);
    }
    return begin; 
}

//优化交换
static doPartition2(int* array, int begin , int end){
    //三数取中
    int mid = begin + (end - begin)/2;
    if(array[begin] > array[end])
        swap(array,begin , end);
    if(array[mid] > array[end])
        swap(array,mid , end);
    if(array[mid] >array[begin])
        swap(array, begin, mid);
    int pivot = array[begin];


    while (begin < end)
    {
        while (begin < end && array[end] >= pivot)
        {
            end--;
        }
        array[begin] = array[end];
        while (begin < end && array[begin] <= pivot)
        {
            begin++;
        }
        array[end] = array[begin];
    }
    array[begin] = pivot;
    return begin; 
}

//优化递归:尾递归
static void doQuick1(int *array, int begin, int end){
    while(begin < end){
        int index = doPartition2(array, begin, end);
        doQuick(array, begin, index-1);
        begin = index + 1;
    }
}




static doPartition(int* array, int begin , int end){
    int pivot = array[begin];
    while (begin < end)
    {
        while (begin < end && array[end] >= pivot)
        {
            end--;
        }
        swap(array, begin, end);
        while (begin < end && array[begin] <= pivot)
        {
            begin++;
        }
        swap(array,begin, end);
    }
    return begin;
    
}

static void doQuick(int *array, int begin, int end){
    if(begin < end){
        int index = doPartition2(array, begin, end);
        doQuick(array, begin, index-1);
        doQuick(array, index+1, end);
    }
}



static void quickSort(int *array, int len){
    doQuick(array,0, len-1);
}

int main(){
    int array[10] = {5, 6, 4, 9, 3, 1, 2, 8, 0, 7};
    quickSort(array, 10);

    printArray(array, 10);
}