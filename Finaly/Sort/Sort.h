#pragma once
#include <Array/Array.h>
#include <Heap/DynamicHeap.h>
#include <Object/Object.h>
namespace FinlayLib {
	class Sort : public Object
	{
	private:
		Sort();
		Sort(const Sort&);
		Sort& operator= (const Sort&);
		template <typename T>
		static void Swap(T& a, T& b)
		{
			T c(a);
			a = b;
			b = c;
		}

	public:
		template <typename T>
		static void Heap(T array[],int len, bool min2max = true)
		{
			DynamicHeap<T> heap(len, !min2max);
			for (int i = 0; i < len; i++)
			{
				heap.add(array[i]);
			}
			for (int i = 0; i < len; i++)
			{
				array[i] = heap.front();
				heap.remove();
			}
		} 
		template <typename T>
		static void Heap(Array<T>& array, bool min2max = true)
		{
			Heap(array.array(), array.length(), min2max);
		}
		/*
		*	选择排序
		* 选择排序的基本思想
		* 每次(例如第i次，i=0,....n-2)从后面n-i个待排序的数据中
		* 选出关键字最小的元素，作为有序元素序列第i个元素
		* 
		*/
		template<typename T>
		static void Select(T array[], int length,bool min2max=true) {
			for (int i = 0; i < length; i++)
			{
				/*
				*选择从i开始以后的数据中最小的数，并将最小的数放入i位置
				*/
				int min = i;
				for (int j = i+1; j < length; j++)
				{
					if ( min2max? (array[min] > array[j]) : (array[min] < array[j]) )
					{
						min = j;
					}
				}
				if (i != min) 
				{
					Swap(array[i], array[min]);
				}
			}
		}
		/**
		* 插入排序的基本思想
		* - 当插入第i（i>=1）个数据元素，前面V[0],V[1],....,
		* V[i-1]已经排好序；这时,用V[i]的关键字与V[i-1]，
		* V[i-2]，...V[0]的关键字进行比较，找到位置后将V[i]插入，
		* 原来位置上的对象向后顺移。
		*/
		template <typename T>
		static void Insert(T array[], int length, bool min2max = true)
		{
			for (int i = 1; i < length; i++)
			{
				int k = i;
				T e = array[i];
				for (int j = i-1; (j >=0)&&(min2max ? (array[j]>e) : (array[j]<e) ); j--)
				{
					array[j + 1] = array[j];
					k = j;
				}
				if (k != i)
				{
					array[k] = e;
				}
			}
		}
		/*
		* 冒泡排序的基本思想
		* 每次从后向前进行（假设第i次），j=n-1,n-2,...,i,
		* 两两比较V[j-1]和V[j]的关键字；如果发生逆序，则
		* 交换V[j-1]和V[j]。
		*/
		template <typename T>
		static void Bubble(T array[], int len, bool min2max = true) {
			bool exchange = true;
			for (int i = 0; (i < len) && exchange; i++)
			{
				exchange = false;
				for (int j = len -1; j > i; j--)
				{
					if (min2max ? ( array[j] < array[j - 1]) : (array[j] > array[j - 1])) {
						Swap(array[j], array[j - 1]);
						exchange = true;
					}
				}
			}
		}
		/*
		*希尔排序的基本思想
		* - 将待排序序列分为若干组，在每一组内进行插入排序，以
		* 使整个序列基本有序，然后在对整个序列进行插入排序
		*/
		template <typename T>
		static void Shell(T array[], int length, bool min2max = true)
		{
			int d = length;
			do
			{
				d = d / 3 + 1;
				for (int i = d; i < length; i+=d)
				{
					int k = i;
					T e = array[i];
					for (int j = i - d; (j >= 0) && (min2max ? (array[j] > e) : (array[j] < e)); j-=d)
					{
						array[j + d] = array[j];
						k = j;
					}
					if (k != i)
					{
						array[k] = e;
					}
				}
			} while (d>1);
		}

		template <typename T>
		static void Merge(T src[], int helper[], int begin, int mid, int end, bool min2max = true)
		{
			int i = begin;
			int j = mid + 1;
			int k = begin;
			while ((i <= mid) && (j <= end))
			{
				if (min2max? (src[i] < src[j]) : (src[i] > src[j]))
				{
					helper[k++] = src[i++];
				}
				else
				{
					helper[k++] = src[j++];
				}
			}
			while (i <= mid)
			{
				helper[k++] = src[i++];
			}
			while (j <= end)
			{
				helper[k++] = src[j++];
			}
			for (i = 0; i <= end; i++)
			{
				src[i] = helper[i];
			}
		}
		/*
		*归并排序的基本思想
		* - 将两个或两个以上的有序序列合并成一个新的有序序列
		* 有序序列V[0]....V[m]和V[m+1]...V[n-1]
		*					↓↓↓
		*				V[0]...V[n-1]
		* 这个归并方法称为2路归并。
		*/
		template <typename T>
		static void Merge(T src[], T helper[], int begin, int end, bool min2max = true)
		{
			if (begin < end)
			{
				int mid = (begin + end) / 2;
				Merge(src, helper, begin, mid, min2max);
				Merge(src, helper, mid + 1, end, min2max);
				Merge(src, helper, begin, mid, end, min2max);
			}
		}

		template <typename T>
		static void Merge(T array[], int length, bool min2max = true)
		{
			T* helper = new T[length];
			if (helper != NULL)
			{
				Merge(array, helper, 0, length - 1, min2max);
			}
			delete[] helper;
		}


		template <typename T>
		static int Partition(T array[], int begin,int end, bool min2max = true)
		{
			T pv = array[begin];
			while (begin < end)
			{
				while ( (begin  <end) && (min2max ? ( array[end] > pv) : (array[end] < pv) ))
				{
					end--;
				}
				Swap(array[begin], array[end]);
				
				while ((begin < end) && (min2max ? (array[begin] <= pv):(array[begin] >= pv)))
				{
					begin++;
				}
				Swap(array[begin], array[end]);
			}
			return begin;
		}
		/*
		* 快速排序的基本思想
		* - 任取序列中的某个数据元素作为基准将整个序列划分为左右
		* 两个子序列
		*	. 左侧子序列中所有元素都小于或等于基准元素
		*	. 右侧子序列所有元素都大于基准元素
		*	. 基准元素排在这两个子序列中间
		* 
		* - 分别对这两个子序列重复进行划分，直到所有的数据元素
		* 都排在相应位置为止
		*/
		template <typename T>
		static void Quick(T array[], int begin, int end, bool min2max = true)
		{
			if (begin < end)
			{
				int pivot= Partition(array, begin, end, min2max);
				Quick(array, begin, pivot - 1, min2max);
				Quick(array, pivot + 1, end ,min2max);
			}
		}
		template <typename T>
		static void Quick(T array[], int len, bool min2max = true)
		{
			Quick(array, 0, len - 1, min2max);
		}

		template<typename T>
		static void Select(FinlayLib::Array<T>& array,bool min2max =true) {
			Select(array.array(), array.length(),min2max);
		}

		template<typename T>
		static void Insert(FinlayLib::Array<T>& array, bool min2max = true) {
			Insert(array.array(), array.length(), min2max);
		}

		template<typename T>
		static void Bubble(FinlayLib::Array<T>& array, bool min2max = true) {
			Bubble(array.array(), array.length(), min2max);
		}

		template<typename T>
		static void Shell(FinlayLib::Array<T>& array, bool min2max = true) {
			Shell(array.array(), array.length(), min2max);
		}

		template<typename T>
		static void Merge(FinlayLib::Array<T>& array, bool min2max = true) {
			Merge(array.array(), array.length(), min2max);
		}

		template<typename T>
		static void Quick(FinlayLib::Array<T>& array, bool min2max = true) {
			Quick(array.array(), array.length(), min2max);
		}
	};


}

