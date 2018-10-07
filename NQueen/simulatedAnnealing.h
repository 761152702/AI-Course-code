/**************************************************
	Author: qiuyihao
	Creation date: 2018/10/04
	Finished date: 2018/10/05
	Description:  ʹ��ģ���˻������N�ʺ�����
	Note��ѭ������ÿһ�У������һ״̬���ڵ�ǰ״̬��������ƶ���
		  �����һ״̬���ڻ���ڵ�ǰ״̬������һ���ĸ��ʽ����ƶ���
****************************************************/

#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H
#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>

class simulatedAnnealing {
private:
	int N;              // �ʺ����Ŀ
public:
	// Ĭ�Ϲ��캯��
	simulatedAnnealing(int N) {
		this->N = N;
	}

	// ���㵱ǰ���̴��ڵ��໥�����Ļʺ����
	int getNumofConflicts(vector<int> *chessboard) {
		int numOfConflicts = 0;
		int width = this->N;
		for (int i = 0; i < width; i++) {
			for (int j = i + 1; j < width; j++) {
				// �����ڻʺ�λ�ڶԽ��ߵ�ʱ�� ��ͻ��+1
				if (abs(j - i) == abs((*chessboard)[i] - (*chessboard)[j])) {
					numOfConflicts++;
				}
				// �����ڻʺ�λ��ͬһ�е�ʱ�򣬳�ͻ��+1
				if ((*chessboard)[i] == (*chessboard)[j]) {
					numOfConflicts++;
				}
			}
		}
		return numOfConflicts;
	}

	//����ģ���˻��㷨�õ����еĺ���λ��
	int properPosition(const vector<int> *chessboard, int row) {
		double T = 100.0;          // ��ǰ�¶�
		double Tmin = 1.0;         // ��С�¶�
		double decreaseRate = 0.8; // ��������
		
		// ��ǰ״̬����һ״̬
		vector<int>* currentChessboard = new vector<int>(N);
		vector<int>* nextChessboard = new vector<int>(N);

		for (int i = 0; i < this->N; i++) {
			(*currentChessboard)[i] = ((*chessboard)[i]);
			(*nextChessboard)[i] = ((*chessboard)[i]);
		}

		//int queenPosition = 0;
		// ��ʼģ���˻�
		while (T > Tmin) {
			// �޸���һ״̬���ı�row�еĻʺ�λ��
			for (int queenPosition = 0; queenPosition < this->N; queenPosition++) {
				(*nextChessboard)[row] = queenPosition;
				// �õ�ǰ��״̬��������
				double dE = getNumofConflicts(nextChessboard) - getNumofConflicts(currentChessboard);
				// �����һ�������򣬽��ܸ��ƶ�
				if (dE <= 0) {
					(*currentChessboard)[row] = (*nextChessboard)[row];
					//cout << "���ţ����ܸ��ƶ�" << " pos = " << queenPosition << endl;
				}
				//  �����һ�������һ�����ʽ��ܸ��ƶ��������𽥱�С
				else {
					if (exp((-1) * dE / T) > random(100)* 1.0 / 100) {
					//	cout << "��������ǽ��ܸ��ƶ�" << " pos = " << queenPosition << endl;
						(*currentChessboard)[row] = (*nextChessboard)[row];
					}
					else {
				//		cout << "  �����ܸ��ƶ� pos = " << queenPosition << endl;
					}
				}
			}
			//  ����
				T = decreaseRate * T;
			
		}
	//	cout << "-----------------------------" << endl;
		return (*currentChessboard)[row];
	}

	// ����ģ���˻��㷨�޸ĸ��У��õ�һ�����ʵ�λ��
	//����һ���ǵ�ǰ���ţ���һ�����ʽ���һ������Ľ⣩
	vector<int>* nextState(vector<int> *chessboard, int row) {
		(*chessboard)[row] = properPosition(chessboard, row);
		return chessboard;
	}

	// ������������ڲ�ͬ�����в�����Ѱ��һ�����ʵ�λ��
	vector<int>* solve(vector<int> *chessboard) {
		int rowPosition = 0;
		int step = 0;
		while (getNumofConflicts(chessboard)) {
			if (rowPosition == this->N) {
				rowPosition %= rowPosition;
			}
			chessboard = nextState(chessboard, rowPosition++);
			step++;
		}
		cout << "Solved the problem, totally " << step << " steps. "<< endl;
		return chessboard;
	}

};

#endif // !SIMULATED_ANNEALING_
