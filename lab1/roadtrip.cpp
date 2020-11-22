// libraries needed to run..
#include <iostream>
#include <bits/stdc++.h>
#include<stdlib.h>
#include<stdio.h>
#include <bits/stdc++.h>
using namespace std;

//mergesort
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void mergeish(int arr[], int l, int m, int r,int arr1[])
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2],L1[n1],R1[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        L[i] = arr[l + i];
        L1[i] = arr1[l + i];}
    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1+ j];
        R1[j] = arr1[m + 1+ j];}

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            arr1[k] = L1[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            arr1[k] = R1[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1)
    {
        arr[k] = L[i];
        arr1[k] = L1[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2)
    {
        arr[k] = R[j];
        arr1[k] = R1[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSortish(int arr[], int l, int r,int arr1[])
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSortish(arr, l, m,arr1);
        mergeSortish(arr, m+1, r,arr1);

        mergeish(arr, l, m, r,arr1);
    }
}
void merge(int arr[], int l, int m, int r)    
{    
    int i, j, k;    
    int n1 = m - l + 1;    
    int n2 =  r - m;    
    
    /* create temp arrays */    
    int L[n1], R[n2];    
    
    /* Copy data to temp arrays L[] and R[] */    
    for (i = 0; i < n1; i++)    
        L[i] = arr[l + i];    
    for (j = 0; j < n2; j++)    
        R[j] = arr[m + 1+ j];    
    
    /* Merge the temp arrays back into arr[l..r]*/    
    i = 0; // Initial index of first subarray    
    j = 0; // Initial index of second subarray    
    k = l; // Initial index of merged subarray    
    while (i < n1 && j < n2)    
    {    
        if (L[i] <= R[j])    
        {    
            arr[k] = L[i];    
            i++;    
        }    
        else    
        {    
            arr[k] = R[j];    
            j++;    
        }    
        k++;    
    }    
    
    /* Copy the remaining elements of L[], if there  
    are any */    
    while (i < n1)    
    {    
        arr[k] = L[i];    
        i++;    
        k++;    
    }    
    
    /* Copy the remaining elements of R[], if there  
    are any */    
    while (j < n2)    
    {    
        arr[k] = R[j];    
        j++;    
        k++;    
    }    
}    
    
/* l is for left index and r is right index of the  
sub-array of arr to be sorted */    
void mergeSort(int arr[], int l, int r)    
{    
    if (l < r)    
    {    
        // Same as (l+r)/2, but avoids overflow for    
        // large l and h    
        int m = l+(r-l)/2;    
    
        // Sort first and second halves    
        mergeSort(arr, l, m);    
        mergeSort(arr, m+1, r);    
    
        merge(arr, l, m, r);    
    }    
} 

bool binarish(int apostasi[],int K,int T,int ci,int Ts,int Cs, int Tf,int Cf){
    int Time = 0, a=K;
    for(int i = 0; i<=K;i++){
        if(apostasi[a]*Cf <= ci) Time += apostasi[a] * Tf;
        else {
            if(((ci - apostasi[a] * Cs) / (Cf - Cs))<0) return false;
            Time += ((ci - apostasi[a] * Cs) / (Cf - Cs)) * Tf + (apostasi[a] - ((ci - apostasi[a] * Cs) / (Cf - Cs))) * Ts;
        }

        if(Time > T)  return false;
	a--;
    }

    return true;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N,K,T,D, Cs,Cf,Ts,Tf,x;
    cin >> N >> K >> D >> T;
    int *pi,*ci,*distance;
    pi = new int[N];
    ci = new int[N];
    distance = new int[K+2];

    //reading the next N lines
    for(int i = 0;i <=N-1; i++){
        cin >> pi[i] >> ci[i];
    }

    distance[0] = 0;
    distance[K+1] = D;

    // reading the next line
    for(int i = 1;i <=K; i++){
        cin >> x;
        distance[i] = D - x;
    }
//    mergeSort(distance,0,K+1);
    int z= sizeof(distance)/sizeof(distance[0]);
   sort(distance,distance+z); 
    int apostasi[K+1];
    for(int i = 0; i <=K;i++){
        apostasi[i]=distance[i+1] - distance[i];
    }
    cin >> Ts >> Cs >> Tf >> Cf;

    mergeSortish(ci,0,N-1,pi);
    //mergeSort(apostasi,0,K); 
    x = 0;
    for(int i = 0; i < N; i++){
        if(apostasi[K] * Cs > ci[i]) x = i;
        else break;
    }
    int arxi = x, telos = N, mesi = (telos + arxi)/2 , min =-1;
    //int k =-1;
    bool success = false;
    while(true){
        if(binarish(apostasi,K,T,ci[mesi],Ts,Cs,Tf,Cf)){
            if(min==-1 || min > mesi) min = mesi;
            telos = mesi;
            success = true;
            if(mesi == 0 ){min=0; break;}
            mesi = (telos + arxi)/2 ;
           // if(k == mesi) break;
           // k = mesi;
            if(telos==1 ){
                if(binarish(apostasi,K,T,ci[0],Ts,Cs,Tf,Cf)) min =0;
                else min =1;
                break;
            }

        }
        else{
            arxi = mesi;
            mesi = (telos + arxi)/2 ;
            //if(k == mesi) break;
            //k = mesi;
        }
        if(telos == arxi || (abs(telos-arxi)) == 1) break;
    }

    if(!success) cout<<"-1"<<endl;
    else{
        int min1 = pi[min];
        for(int i = min+1; i<N;i++){
            if(min1  > pi[i]) min1 = pi[i];
        }
        cout << min1<<endl;
    }
    return 0;
}
