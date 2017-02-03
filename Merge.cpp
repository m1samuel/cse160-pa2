// Merge two lists
// 

#include <cstdlib>
#include <iostream>     // std::cout

#include <algorithm>    // std::sort

#include <thread>
#include <time.h>
#include "mergeSort.h"

//
// Globals
//
  extern control_block cb;
//
// Merge two lists on the interval (l0:l1), that is,
// (l0:mid-1) and (mid-1:n1), where mid = l0 + n/2
// This is a serial implementation Serial
// 

void Merge(std::vector<int> *keysIn, std::vector<int> *keysOut,
           int l0, int l1){
    int n = (l1-l0) + 1;
    int mid = l0 + n/2;
    int min1 = l0, max1 = mid-1;
    int min2 = mid, max2 = l1;

#ifdef DEBUG
// Output the keys if N is <= 16
    if (n <= 16){
        for (int i=min1;i<=max1;i++) 
            std::cout<<(*keysIn)[i]<<" ";
        std::cout<<std::endl;
        for (int i=min2;i<=max2;i++) 
            std::cout<<(*keysIn)[i]<<" ";
        std::cout<<std::endl;
    }
#endif
    int l=min1;
    int r=min2;
    int i;
    for (i=0; i < max2-min1+1 ; i++) {  
      if ((*keysIn)[l]<(*keysIn)[r]) {
          (*keysOut)[i+min1]=(*keysIn)[l++];
          if (l>max1) break;
      } else {
          (*keysOut)[i+min1]=(*keysIn)[r++];
          if (r>max2) break;
      }
    }
    while (l<=max1) {
        i++;
        (*keysOut)[i+min1]=(*keysIn)[l++];
    }
    while (r<=max2) {
        i++;
        (*keysOut)[i+min1]=(*keysIn)[r++];
    }
}
