
char MaxDupChar(const char* s, int& n)
{
	return 0;
}


bool IsIntStr(const char* s, int& n)
{
	if (*s == 0) {
		return true;
	}
	int num = (char)*s - 48;
	if (num >= 0 && num <= 9) {
		n = n * 10 + num;
	}
	else
	{
		n = 0;
		return false;
	}
	return IsIntStr(++s, n);

}
template <typename T>
static int Partition(T array[],int index, int begin, int end, bool min2max = true)
{
	int ret = 0;
	T pv = array[index];
	while (begin < end)
	{
		while ((begin < end) && (min2max ? (array[end] > pv) : (array[end] < pv)))
		{
			end--;
		}
		ret = end;
		//Swap(array[begin], array[end]);
		begin++;
		while ((begin < end) && (min2max ? (array[begin] <= pv) : (array[begin] >= pv)))
		{
			begin++;
		}
		end--;
		//Swap(array[begin], array[end]);
		ret = begin;
	}
	return ret;
}
int FindMid(int a[], int n)
{
	int num = Partition<int>(a, 0, n-1, true);
	return num;
}