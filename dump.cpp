// [Problem]

// There are magnetic objects on a table. Different colors are applied according to the properties of the magnetic objects. The blue ones are attracted to N polar while the red ones are attracted to the S polar.

 

// Create a program returning the number of standstill magnetic objects left on the table after crashing to each other as some time has passed after a strong magnetic field is applied to the table in a specific interval as shown in the example.

 

// Following figure shows the table with the magnetic objects as seen from the above.



 

// The red magnetic objects marked A are attracted to the S polar and dropped below the table.

// The blue magnetic objects marked B are attracted to the N polar and dropped below the table.

// Other magnetic objects crash to each other and become standstill.

// As shown by the magnetic objects marked D, the objects will be standstill if there is a magnetic object moving in the opposite direction even if there are many magnetic objects moving to a direction.

// It is regarded as a standstill even when there are three or more magnetic objects crashing with each other and stuck together like those marked D.

// Although C and D are adjacent to each other, they are considered different standstills and thus regarded as two standstills.

// Like the case of E, there can be two or more standstills on a line.

// In the above example, the program should return 5 since there are 5 standstills on the table.

 

 

// [Constraints]

// A magnetic object only reacts to the N polar or S polar at the top and bottom of the table. It does not react to another magnetic object.

// A table is sized 100x100. (It should be noted that the above example uses a 7x7 table just for explanation.)

 

// [Input]

// The first line of the input file provides the length of a side of the square shaped table. The test cases are given in next lines. Total of 10 test cases are given. 1 means the magnetic object with N polar property and 2 means the magnetic object with S polar property. It is assumed that the N polar is located at the top of the table while the S polar is located at the bottom.

 

 

// [Output]

// The output file outputs the test case number following the ‘#’ symbol. It is followed by a space and then the number of standstills.

 

 

// [Input Example] 

// 100
// 1 0 0 0 0 0 0 0 2 0 0 0 1 0 1 1 0 2 0 0 1 0 2 0 2 2 1 0 0 0 0 0 1 0 0 2 0 0 0 0 0 1 2 0 0 0 1 1...

// 0 0 0 0 0 0 0 0 0 0 1 0 0 2 0 0 0 0 0 2 0 0 1 0 0 0 0 0 1 2 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0...

// 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 2 2 0 2 0 0 0 0 0 1 0 0...

// 0 0 0 2 0 0 0 0 1 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 1 0 1 0 0 0 0 0 0 2 0 2 0...

// 0 0 0 0 2 0 2 0 0 0 2 0 0 0 0 0 0 2 1 1 0 2 0 0 0 1 2 2 2 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0...

// 0 0 2 0 0 0 1 1 1 0 0 0 0 0 0 0 0 1 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0...

// ...


// 100
// 0 0 0 0 0 0 0 0 0 2 0 0 2 0 0 0 0 0 0 2 0 0 0 1 0 0 0 0 0 0 1 0 2 0 2 0 1 0 1 0 0 0 0 1 0 0 0 0...

// 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0...

// 0 0 0 0 2 0 0 0 1 2 1 0 0 0 0 1 0 0 0 0 0 2 0 0 0 0 0 2 2 1 2 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 0...

// 2 2 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 1 2 0 2 0 0 0...

// 0 1 1 0 2 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 2 0 0 0 2 0 0 0 0...

// 1 0 0 0 0 1 0 2 0 0 0 0 2 0 2 0 0 0 0 0 0 0 0 0 2 0 0 1 2 0 0 0 0 1 0 0 1 0 0 0 2 0 0 2 2 0 0 0...

// ...


 

// [Output Example]

// #1 471
// #2 446
#include <iostream>

using namespace std;

int grid[100][100];

int stack[1000];
int top;

void init(){
	top = -1;
}

void push(int val) {
	top++;
	stack[top] = val;
}

void pop() {
	top--;
}

bool isEmpty() {
	return top == -1;
}

int peek() {
	return stack[top];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int T;
	T = 10;
	for(int tc = 1; tc <= T; tc++) {
		int N;
		cin >> N;
		int count = 0;
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				cin >> grid[j][i];				//1 DO    2 XANH
			}
		}
		for(int i = 0; i < N; i++) {
			init();
			for(int j = 0; j < N; j++) {
				if(!grid[i][j]) continue;
				if(grid[i][j] == 1) push(grid[i][j]);
				if(grid[i][j] == 2) {
					if(isEmpty()) continue;
					if(peek() == grid[i][j]) continue;
					push(grid[i][j]);
				}
			}
			while(!isEmpty()) {
				if(peek() == 2) count++;
				pop();
			}
		}
		cout << '#' << tc << ' ' << count << '\n';
	}
	return 0;
}
// ...
