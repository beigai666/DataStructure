#include <iostream>
#include <cmath>
#include <ctime>
#include <String/String.h>
#include <Array/StaticArray.h>
#include <Array/DynamicArray.h>
#include <List/DynamicList.h>
#include <List/LinkList.h>
#include <Stack/LinkStack.h>
#include <Queue/LinkQueue.h>
#include <Tree/BTree.h>
#include <Graph/ListGraph.h>
#include <Graph/MatrixGraph.h>
#include <Tree/BTreeArray.h>
#include <Heap/StaticHeap.h>
#include <Heap/DynamicHeap.h>
#include <Sort/Sort.h>
#include <Exception/Exception.h>
#include <Queue/DualEndQueue.h>

using namespace FinlayLib;
using namespace std;

template <typename T>
void StackCopy(Stack<T>& left, Stack<T>& right)
{
    LinkStack<T> temp;

    while( left.size() )
    {
        temp.push(left.top());
        left.pop();
    }

    while( temp.size() )
    {
        left.push(temp.top());
        right.push(temp.top());
        temp.pop();
    }
}

class Thing : public Object
{
public:
    int weight;
    int value;

    Thing(int w = 0, int v = 0)
    {
        weight = w;
        value = v;
    }
};

void BagToMax(Thing things[], int begin, int end, int max, Thing cv, Stack<int>& cur, Thing& rv, Stack<int>& result)
{
    if( begin <= end )
    {
        for(int i=(begin == -1) ? 0 : begin; i<=end; i++)
        {
            cv.value += things[i].value;
            cv.weight += things[i].weight;

            cur.push(i);

            if( (cv.weight <= max) && (cv.value > rv.value) )
            {
                rv = cv;
                result.clear();
                StackCopy(cur, result);
            }

            if( cv.weight < max )
            {
                BagToMax(things, (begin == -1) ? -1 : (i+1), end, max, cv, cur, rv, result);
            }

            cur.pop();

            cv.value -= things[i].value;
            cv.weight -= things[i].weight;
        }
    }
}

void BagToMax()
{
    Thing things[] = { {5, 6}, {1, 2}, {2, 4}, {3, 4}, {4, 5} };
    int len = sizeof(things)/sizeof(*things);
    int max = 6;
    Thing rv;
    Thing cv;
    LinkStack<int> cur;
    LinkStack<int> result;

    BagToMax(things, -1, len-1, max, cv, cur, rv, result);

    cout << "value: " << rv.value << endl;
    cout << "weight: " << rv.weight << endl;

    while( result.size() )
    {
        int i = result.top();

        cout << "(" << things[i].weight << ", " << things[i].value << "), ";

        result.pop();
    }

    cout << endl;
}

bool IsValid(const String& s)
{
    return (s == "0") || ((s[0] != '0') && (atoi(s.str()) <= 255));
}

void MakeIP(const String& s, int i, List<String>& seg, List<String>& result)
{
    if( (i == s.length()) && (seg.length() == 4) )
    {
        String ip;

        for(i=0; i<seg.length(); i++)
        {
            String tmp;

            seg.get(i, tmp);

            ip += tmp + ".";
        }

        ip.remove(ip.length()-1, 1);

        result.insert(ip);
    }
    else if( i < s.length() )
    {
        String current = "";
        String tmp = "";
        int pos = seg.length() ? (seg.length() - 1) : 0;

        seg.get(pos, current);

        tmp = current + s[i];

        if( IsValid(tmp) && seg.set(pos, tmp) )
        {
            MakeIP(s, i+1, seg, result);

            seg.set(pos, current);
        }

        if( (seg.length() < 4) && seg.insert(s[i]) )
        {
            MakeIP(s, i+1, seg, result);

            seg.remove(seg.length()-1);
        }
    }
}

void MakeIP()
{
    LinkList<String> seg;
    LinkList<String> result;

    MakeIP("12345", 0, seg, result);

    for(result.move(0); !result.end(); result.next())
    {
        cout << result.current().str() << endl;
    }
}

template< int N >
class MazeSolution
{
    struct Move : public Object
    {
        int dx;
        int dy;
    public:
        Move(int dx = 0, int dy = 0)
        {
            this->dx = dx;
            this->dy = dy;
        }
    };

    struct Pos : public Object
    {
        int x;
        int y;

    public:
        Pos(int x = 0, int y = 0)
        {
            this->x = x;
            this->y = y;
        }
    };

    int m_maze[N+2][N+2];
    int m_marker[N+2][N+2];
    LinkStack<Pos> m_path;

    int Init()
    {
        for(int i=0; i<N+2; i++)
        {
            m_maze[0][i] = 1;
            m_maze[N+1][i] = 1;
            m_maze[i][0] = 1;
            m_maze[i][N+1] = 1;

            m_marker[0][i] = 1;
            m_marker[N+1][i] = 1;
            m_marker[i][0] = 1;
            m_marker[i][N+1] = 1;
        }

        for(int i=1; i<=N; i++)
        {
            for(int j=1; j<=N; j++)
            {
                m_maze[i][j] = !(rand() % 4);
                m_marker[i][j] = 0;
            }
        }

        m_maze[1][1] = 0;
        m_maze[N][N] = 0;

        m_path.clear();
        return 0;
    }

    bool Run(Pos cp)
    {
        bool ret = false;

        m_marker[cp.x][cp.y] = 1;

        if( (cp.x == N) && (cp.y == N) )
        {
            ret = true;
        }
        else
        {
            static Move s_dir[] = {Move(1, 0), Move(0, 1), Move(-1, 0), Move(0, -1)};
            static const int s_dl = sizeof(s_dir)/sizeof(*s_dir);

            for(int i=0; i<s_dl; i++)
            {
                Pos next;

                next.x = cp.x + s_dir[i].dx;
                next.y = cp.y + s_dir[i].dy;

                if( !m_maze[next.x][next.y] && !m_marker[next.x][next.y] )
                {
                    m_path.push(next);

                    if( (ret = Run(next)) )
                    {
                        break;
                    }
                    else
                    {
                        m_path.pop();
                    }
                }
            }
        }

        return ret;
    }
public:
    MazeSolution()
    {
        srand((unsigned)time(NULL));
    }

    bool Run()
    {
        int ret = true;
        Pos start(1, 1);

        Init();

        m_path.push(start);

        if( !(ret = Run(start)) )
        {
            m_path.pop();
        }

        return ret;
    }

    void Print()
    {
        LinkList<Pos> pl;

        while( m_path.size() )
        {
            Pos p = m_path.top();

            pl.insert(0, p);

            m_path.pop();

            m_maze[p.x][p.y] = 2;
        }

        for(int i=0; i<N+2; i++)
        {
            for(int j=0; j<N+2; j++)
            {
                switch( m_maze[i][j] )
                {
                case 0:
                    cout << " ";
                    break;
                case 1:
                    cout << "#";
                    break;
                case 2:
                    cout << ".";
                    break;
                }
            }

            cout << endl;
        }

        cout << "Path: ";

        for(pl.move(0); !pl.end(); pl.next())
        {
            Pos cp = pl.current();

            cout << "(" << cp.x << ", " << cp.y << ") ";

            m_path.push(cp);
        }

        cout << endl;
    }
};

void Maze()
{
    MazeSolution<15> ms;

    while( 1 )
    {
        cout << ms.Run() << endl;

        ms.Print();

        cin.get();
    }
}

class PrefixSortSolution
{
    /*
    * 表示烙饼的数组
    */
   DynamicArray<int> m_cake;
   /*
   * 表示每次反转的结果
   */
   DynamicArray<int> m_stepArray;
   /*
   * 用来记录反转的步骤
   */
   DynamicArray<int> m_swapArray;
   /*
   * 将得到的最小反转次数保持到m_minStep和反转记录保存到m_swapResut
   */
   DynamicArray<int> m_swapResut;
   int m_minStep;

   int UpperBound()
   {
       return 2 * m_cake.length();
   }

   void Reverse(Array<int>& arr, int begin, int end)
   {
       for(int i=begin, j=end; i<j; i++, j--)
       {
           swap(arr[i], arr[j]);
       }
   }

   bool IsSorted()
   {
       bool ret = true;

       for(int i=1; i<m_stepArray.length(); i++)
       {
           ret = ret && (m_stepArray[i-1] <= m_stepArray[i]);
       }

       return ret;
   }

   void Init()
   {
       m_cake[0] = 5;
       m_cake[1] = 3;
       m_cake[2] = 1;
       m_cake[3] = 4;
       m_cake[4] = 2;
#if 0
       for(int i=0; i<m_cake.length(); i++)
       {
           m_cake[i] = i + 1;
       }
       /*
       * 对数组中的元素随机交换
       */
       for(int i=0; i<m_cake.length(); i++)
       {
           int x = rand() % m_cake.length();
           int y = rand() % m_cake.length();

           swap(m_cake[x], m_cake[y]);
       }
#endif
       m_stepArray = m_cake;

       for(int i=0; i<m_swapArray.length(); i++)
       {
           m_swapArray[i] = 0;
       }

       m_minStep = UpperBound();
   }

   int LowerBound()
   {
       int ret = 0;

       for(int i=1; i<m_stepArray.length(); i++)
       {
           if( abs(m_stepArray[i-1] - m_stepArray[i]) != 1 )
           {
               ret++;
           }
       }

       return ret;
   }

   void Run(int step)
   {
       if( step + LowerBound() > m_minStep )
       {

       }
       else if( IsSorted() )
       {
           if( step < m_minStep )
           {
               m_minStep = step;
               m_swapResut = m_swapArray;
           }
       }
       else
       {
           for(int i=1; i<m_stepArray.length(); i++)
           {
               Reverse(m_stepArray, 0, i);
               m_swapArray[step] = i;
               Run(step + 1);
               Reverse(m_stepArray, 0, i);
           }
       }
   }

public:
   PrefixSortSolution(int n)
   {
       m_cake.resize(n);
       m_stepArray.resize(n);
       m_swapArray.resize(UpperBound() + 1);

       srand((unsigned)time(NULL));
   }

   void Run()
   {
       Init();
       Run(0);
   }

   void Print()
   {
       cout << "Step: " << m_minStep << endl;
       cout << "Original:  ";

       for(int i=0; i<m_cake.length(); i++)
       {
           cout << m_cake[i] << " ";
       }

       cout << endl;
       cout << "Reverse: " << endl;

       m_stepArray = m_cake;

       for(int i=0; i<m_minStep; i++)
       {
           cout << "0 <--> " << m_swapResut[i] << "   ";

           Reverse(m_stepArray, 0, m_swapResut[i]);

           for(int j=0; j<m_stepArray.length(); j++)
           {
               cout << m_stepArray[j] << " ";
           }

           cout << endl;
       }
   }
};

void PrefixSort()
{
    PrefixSortSolution pss(5);

    while( 1 )
    {
        pss.Run();
        pss.Print();
        cin.get();
    }
}

int start()
{
    // BagToMax();
    // MakeIP();
    // Maze();
     PrefixSort();
    return 0;
}
