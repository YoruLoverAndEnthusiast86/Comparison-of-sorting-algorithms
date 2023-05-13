#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>

long long array[100000001] ;
long long c[100000001] ;
long long count[1000] ;

void CreateRandomArray(long long maxNrDigits,long long minNrDigits,long long *location,long long nrOfElements)
{
    if(minNrDigits > maxNrDigits)
        return ;
    long long maxNr = 9 ;
    long long minNr = 9 ;
    while(maxNrDigits != 1)
    {
        maxNr = maxNr*10+9 ;
        maxNrDigits-- ;
    }
    if(minNrDigits != 1)
    {
        minNrDigits-- ;
        while(minNrDigits != 1)
        {
            minNr = minNr*10+9 ;
            minNrDigits-- ;
        }
        minNr++ ;
    }
    else
        minNr = 0 ;
    //printf("Min nr is : %d \nMax nr is : %d\n", minNr,maxNr) ;
    for(int i = 0 ; i < nrOfElements ; i++)
    {
        //printf("%d ", i) ;
        location[i] = (minNr + (rand()%(maxNr+1-minNr))) ;
    }
}

void CountingSort(long long *arr, long long n)
{
    long long i ;
    for( i = 0 ; i < 1000 ; i++)
        count[i] = 0 ;
    for (i = 0; i < n; i++)
        count[arr[i]]++ ;
    for (i = 1; i < 1000; i++)
        count[i] += count[i - 1] ;
    for (i = 0; i < n; i++) {
        c[count[arr[i]]-1] = arr[i];
        count[arr[i]]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = c[i];
}

void mergee(long long *array,long long li,long long mid,long long ls)
{
    long long i=li;
    long long k=0;
    long long j=mid+1;
    while(i<=mid && j<=ls)
    {
        if(array[i]<array[j])
            c[++k]=array[i++];
        else
            c[++k]=array[j++];
    }
    while(i<=mid)
        c[++k]=array[i++];
    while(j<=ls)
        c[++k]=array[j++];
    for(k=1,i=li;i<=ls;i++,k++)
        array[i]=c[k];
}
void mergesort(long long *array,long long li,long long ls)
{
    if(li<ls)
    {
        long long mid=(li+ls)/2;
        mergesort(array,li,mid);
        mergesort(array,mid+1,ls);
        mergee(array,li,mid,ls);
    }
}

void MergeSortCaller(long long *array,long long size)
{
    mergesort(array,0,size-1) ;
}

void PrintArray(long long *array,long long size)
{
    for(long long i = 0 ; i < size ; i++)
        printf("%lli ", array[i]) ;
    printf("\n") ;
}

void swap(long long *a,long long *b)
{
    long long aux = *a ;
    *a = *b ;
    *b = aux ;
}

void quick_sort(long long *v,long long li,long long ls)
{
    if(li >= ls)
        return ;
    long long pivot = (rand() % (ls-li+1))+li ;
    long long i = li,j = li ;
    swap(v+pivot,v+ls) ;
    while(j < ls)
    {
    if(v[j] < v[ls])
    {
        swap(v+j,v+i) ;
        i++ ;
    }
    j++ ;
    }
    swap(v+i,v+ls) ;
    quick_sort(v,li,i-1) ;
    quick_sort(v,i+1,ls) ;
}

void ReverseQuickSort(long long *v,long long li,long long ls)
{
     if(li >= ls)
        return ;
    long long pivot = (rand() % (ls-li+1))+li ;
    long long i = li,j = li ;
    swap(v+pivot,v+ls) ;
    while(j < ls)
    {
    if(v[j] > v[ls])
    {
        swap(v+j,v+i) ;
        i++ ;
    }
    j++ ;
    }
    swap(v+i,v+ls) ;
    ReverseQuickSort(v,li,i-1) ;
    ReverseQuickSort(v,i+1,ls) ;
}

void BubbleSort(long long *array,long long size)
{
    for(long long i = size-2 ; i >=0 ; i--)
        for(long long j = 0 ; j <= i ; j++)
            if(array[j]>array[j+1])
                swap(array+j,array+j+1) ;
}

void RandomlySortedTest(int times,int indexMax,void (*sorting)(long long *array,long long currentSize))
{
    long long ns[9] = {0,10,100,1000,10000,100000,1000000,10000000,100000000} ;  //indexMax is the index at wich it stops in this array,ie max size
    double timeSum = 0 ;
    printf("These are the sorting times for the randomly generated data sets!\n") ;
    for(int i = 1 ; i <= indexMax ; i++){
        long long currentSize = ns[i] ;
        for(int t = 1 ; t <= times ; t++)
            {
                CreateRandomArray(3,1,array,currentSize) ;
                auto begin = std::chrono::high_resolution_clock::now();
                sorting(array,currentSize) ;
                //PrintArray(array,currentSize) ;
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                timeSum += (double)(elapsed.count() * 1e-9) ;
                //printf("Ellapsed time : %lf\n",ellapsedTime) ;
            }
    printf("Average time for an array of size %lli is : %lf\n",currentSize,timeSum/(double)times) ;
    }
    printf("\n") ;
}

void QuickSortCaller(long long *array,long long size)
{
    quick_sort(array,0,size-1) ;
}

void ReverseMergeSort(long long *array,long long size)
{
    MergeSortCaller(array,size) ;
    for(int i = 0 ; i < size ; i++)
        c[i] = array[size-1-i] ;
    for(int i = 0 ; i < size ; i++)
        array[i] = c[i] ;
}

void ReverseCountingSort(long long *array,long long size)
{
    CountingSort(array,size);
    for(long long i = 0 ; i < size ; i++)
        array[i] = c[size-1-i] ;
}

void DescendingSortedTest(int times,int indexMax,void (*sorting)(long long *array,long long currentSize))
{
    long long ns[9] = {0,10,100,1000,10000,100000,1000000,10000000,100000000} ;
    double timeSum = 0 ;
    printf("These are the sorting times for the randomly generated descendingly sorted data sets!\n") ;
    for(int i = 1 ; i <= indexMax ; i++){
        long long currentSize = ns[i] ;
        for(int t = 1 ; t <= times ; t++)
            {
                CreateRandomArray(3,1,array,currentSize) ;
                ReverseCountingSort(array,currentSize) ;
                auto begin = std::chrono::high_resolution_clock::now();
                sorting(array,currentSize) ;
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                timeSum += (double)(elapsed.count() * 1e-9) ;
                //printf("Ellapsed time : %lf\n",ellapsedTime) ;
            }
    printf("Average time for an array of size %lli is : %lf\n",currentSize,timeSum/(double)times) ;
    }
    printf("\n") ;
}

void InsertionSort(long long *array,long long size)
{
     for(long long i = 1 ; i < size ; i++)
        for(long long j = i ; j >= 1 ; j--)
          if(array[j-1]>array[j])
                swap(array+j-1,array+j) ;
         else
            break ;
}

void SelectionSort(long long *array,long long size)
{
    for(long long i = 0 ; i < size-1 ; i++)
        for(long long j = i+1 ; j < size ; j++)
            if(array[j]<array[i])
                swap(array+i,array+j) ;
}

void AscendingSortedTest(int times,int indexMax,void (*sorting)(long long *array,long long currentSize))
{
    long long ns[9] = {0,10,100,1000,10000,100000,1000000,10000000,100000000} ;
    double timeSum = 0 ;
    printf("These are the sorting times for the randomly generated ascendingly sorted data sets!\n") ;
    for(int i = 1 ; i <= indexMax ; i++){
        long long currentSize = ns[i] ;
        for(int t = 1 ; t <= times ; t++)
            {
                CreateRandomArray(3,1,array,currentSize) ;
                CountingSort(array,currentSize-1) ;
                auto begin = std::chrono::high_resolution_clock::now();
                sorting(array,currentSize) ;
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                timeSum += (double)(elapsed.count() * 1e-9) ;
                //printf("Ellapsed time : %lf\n",ellapsedTime) ;
            }
    printf("Average time for an array of size %lli is : %lf\n",currentSize,timeSum/(double)times) ;
    }
    printf("\n") ;
}

void Heapify(long long *array,long long index,long long size)
{
    long long left = 2*index ;
    long long right = 2*index+1 ;
    long long maxim = index ;
    if(left <= size && array[left] > array[maxim])
        maxim = left;
    if(right <= size && array[right] > array[maxim])
        maxim = right ;
    if(maxim != index)
    {
        swap(array+index,array+maxim) ;
        Heapify(array,maxim,size) ;
    }
}

void HeapSort(long long *array,long long size)
{
    for(long long i = size/2 - 1 ; i >= 0 ; i--)
        Heapify(array,i,size-1) ;

    for(long long i = size-1 ; i > 0 ; i--)
    {
        swap(array+0,array+i) ;
        Heapify(array,0,i-1) ;
    }
}

void countSort(long long*arr, long long n, int exp)
{
    long long i ;
     for( i = 0 ; i < 10 ; i++)
        count[i] = 0 ;
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = 0; i < n; i++) {
        c[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
}
    for (i = 0; i < n; i++)
        arr[i] = c[i];
}

long long getMax(long long *arr, long long n)
{
    long long mx = arr[0];
    for (long long i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
void RadixSort(long long *arr, long long n)
{
    long long m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int main()
{
    srand(time(NULL)) ;
    RandomlySortedTest(50,7,&RadixSort) ; // first parameter is the amount of times you want to run the sort, the second parameter is the max power of 10 you want to test for
    //ex if you put 5 it's going to test for input sizes of 10-10^5
    //The 3rd parameter is the sorting algorithm, for Merge sort and quick sort,use MergeSortCaller and QuickSortCaller
    AscendingSortedTest(50,7,&RadixSort) ;
    DescendingSortedTest(50,7,&RadixSort) ;

    return 0 ;
}