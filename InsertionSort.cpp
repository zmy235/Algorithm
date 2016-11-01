//*******************************************
//InsertionSort.cpp   2014/6/1 by Adaq
//@brief: 本文件为Insertion Sort的C++实现。
//*******************************************
#include<iostream>
#include<algorithm>
#include<limits>
template  <typename  T>
T InsertionSort( const T& BeginIter, const T& EndIter)
{
    auto Iter=BeginIter;
    ++Iter;
    while(Iter!=EndIter)
    {
        auto Key=*Iter;
        std::reverse_iterator <T> RIter(Iter);
        std::reverse_iterator <T> RBeginIter(BeginIter);
        while(RIter!=RBeginIter && Key<*RIter)
        {
            auto Iter3=RIter;
            *--Iter3=*RIter++;
        }
        *--RIter=Key;
        ++Iter;
    }
    return Iter;
}


template <typename T>
void MergeSort(const T& BegIter,const T& EndIter)
{
    if(BegIter+1<EndIter)
    {
        auto MidIter=BegIter;
        advance(MidIter,distance(BegIter,EndIter)/2 );
        MergeSort(BegIter,MidIter);
        MergeSort(MidIter,EndIter);
        //CombineResult(BegIter,MidIter,EndIter);
        std::inplace_merge(BegIter,MidIter,EndIter);
    }
}


int main ()
{
    return 0;
}
