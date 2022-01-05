#pragma once
#include <iostream>
using namespace std;
namespace FinlayLib {
	template <int SIZE>
	class QueneSolution : public Object
	{
	protected:
		enum
		{
			N = SIZE + 2
		};

		struct Pos : public Object
		{
			int x;
			int y;
			Pos(int px = 0, int py = 0) :x(px), y(py) {}
		};
		int m_chessboard[N][N];
		Pos m_direction[3];
		LinkList<Pos> m_solution;
		int m_count;

		void init()
		{
			m_count = 0;
			for (int i = 0; i < N; i += (N - 1))
			{
				for (int j = 0; j < N; j++)
				{
					m_chessboard[i][j] = 2;
					m_chessboard[j][i] = 2;
				}
			}

			for (int i = 1; i < SIZE; i++)
			{
				for (int j = 1; j < SIZE; j++)
				{
					m_chessboard[i][j] = 0;
				}
			}

			m_direction[0].x = -1;
			m_direction[0].y = -1;
			m_direction[1].x = 0;
			m_direction[1].y = -1;
			m_direction[2].x = 1;
			m_direction[2].y = -1;

		}


		void print()
		{
			for (m_solution.move(0); !m_solution.end(); m_solution.next())
			{
				cout << "(" << m_solution.current().x << "," << m_solution.current().y << ") ";
			}
			cout << endl;

			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					switch (m_chessboard[i][j])
					{
					case 0: cout << "-"; break;
					case 1: cout << "#"; break;
					case 2: cout << "*"; break;
					}
				}
				cout << endl;
			}
			cout << endl;
		}
		bool check(int x, int y, int d)
		{
			bool flag = true;
			do
			{
				x += m_direction[d].x;
				y += m_direction[d].y;
				flag = flag && (m_chessboard[x][y] == 0);
			} while (flag);
			return(m_chessboard[x][y] == 2);
		}

		void run(int j)
		{
			if (j <= SIZE)
			{
				for (int i = 1; i <= SIZE; i++)
				{
					if (check(i, j, 0) && check(i, j, 1) && check(i, j, 2))
					{
						m_chessboard[i][j] = 1;
						m_solution.insert(Pos(i, j));
						run(j + 1);
						m_chessboard[i][j] = 0;
						m_solution.remove(m_solution.length() - 1);
					}
				}
			}
			else
			{
				m_count++;
				print();
			}
		}


	public:
		QueneSolution() {
			init();
			print();
		}

		void run()
		{
			run(1);
			cout << "Total: " << m_count << endl;
		}

		~QueneSolution()
		{

		}

	private:

	};
}
