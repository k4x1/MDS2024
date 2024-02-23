// GD2P03_ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
using namespace std::chrono;
const unsigned int ROWS = 1024;
const unsigned int COLS = 2048;
void copyYX();
void copyXY();
void copyRand();
int src[ROWS][COLS];
int dst[ROWS][COLS];
int main()
{
	steady_clock::time_point t_start, t_end;
	long long duration;

	t_start = high_resolution_clock::now();
	copyYX();
	t_end = high_resolution_clock::now();

	duration = duration_cast<milliseconds>(t_end - t_start).count();

	std::cout << " time required to compute YX: " << duration << "milliseconds\n";

	t_start = high_resolution_clock::now();
	copyRand();
	t_end = high_resolution_clock::now();

	duration = duration_cast<milliseconds>(t_end - t_start).count();

	std::cout << " time required to compute XY: " << duration << "milliseconds\n";
}

void copyYX()
{
	for (int y = 0; y < ROWS; y++)
	{
		for (int x = 0; x < COLS; x++)
		{
			dst[y][x] = src[y][x];
		}
	}
}

void copyXY()
{
	for (int x = 0; x < COLS; x++)
	{
		for (int y = 0; y < ROWS; y++)
		{
			dst[y][x] = src[y][x];
		}
	}
}
struct linkedList {
	int value = 0;
	linkedList* next = NULL;
};/*
void copyRand() {
	int randRow = 0;
	int randCols = 0;
	int copiedCount = 0;
	linkedList head;
	while (copiedCount < ROWS + COLS) {
		linkedList* temp = &head;
		bool rowDone = false;
		bool colsDone = false;
		while (!rowDone) {
			temp = &head;
			 randRow = rand() % ROWS;
			while (temp->next != NULL) {
				if (randRow == temp->value) {
					return;
				}
				temp = temp->next;

			}
			if (temp->next == NULL) {
				//means the random number attempt succeeded lmao
				rowDone = true;
			}
		}
		while (!colsDone) {
			temp = &head;
			 randCols = rand() % COLS;
			while (temp->next != NULL) {
				if (randCols == temp->value) {
					return;
				}
				temp = temp->next;

			}
			if (temp->next == NULL) {
				//means the random number attempt succeeded lmao
				colsDone = true;
			}
		}

		copiedCount++;
		dst[randRow][randCols] = src[randRow][randCols];


	}

	

}
*/
void copyRand() {
	int copiedCount = 0;
	linkedList* head = nullptr;


	srand(time(NULL));
	while (copiedCount < ROWS * COLS) {

		int randRow = rand() % ROWS;
		int randCol = rand() % COLS;

		bool alreadyCopied = false;
		linkedList* temp = head;
		while (temp != nullptr) {
			if (temp->value == randRow * COLS + randCol) {
				alreadyCopied = true;
				break;
			}
			temp = temp->next;
		}

		if (!alreadyCopied) {
			dst[randRow][randCol] = src[randRow][randCol];

			linkedList* newNode = new linkedList;
			newNode->value = randRow * COLS + randCol;
			newNode->next = head;
			head = newNode;

			copiedCount++;
		}
	}

	linkedList* temp = head;
	while (temp != nullptr) {
		linkedList* toDelete = temp;
		temp = temp->next;
		delete toDelete;
	}
}