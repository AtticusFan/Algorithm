#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

int ranks[2000]={0};

struct point {
	float x, y;
	int index;
	bool operator<(const point& a) const {
		if (x != a.x)
			return x < a.x;
		return y > a.y;
	}
} points[2000], buffer[2000];
void heapify(point points[], int SIZE, int i){

    int max = i, l = 2*i + 1, r = 2*i + 2;

    if(l < SIZE && points[l].x > points[max].x)
        max = l;

    if(r < SIZE && points[r].x > points[max].x)
        max = r;

    if(max != i)
    {
        std::swap(points[0].x, points[max].x);
        std::swap(points[0].y, points[max].y);
        heapify(points, max, SIZE);
    }
}
void heapsort(point points[], int amount)
{
	int lastNode = amount-1;
    int parent = (lastNode-1)/2;
    //build heap
    for(int i = parent; i >= 0; i--){
		heapify(points, amount, i);
	}
    //sort
   	for(int i = lastNode; i >= 0; i--){
        std::swap(points[0].x, points[i].x);
        std::swap(points[0].y, points[i].y);
        heapify(points, i, 0);
    }
}
void DC(int lower, int upper) {
	//cout<<"Lower/Upper "<<lower<<upper<<endl; 
	if (upper <= lower)
		return;
	int middle = (lower + upper)/2, i = lower, j = middle, k = upper;
	float medianX = points[middle].x;
	DC(lower, middle);
    DC(middle+1, upper);
    for(; i<=middle; i++){
        
        for(j=middle+1; j<=upper; j++){
            if(points[j].y > points[i].y){
                //cout << "l/m/u" << " " << lower << middle << upper << endl;
                //cout<< j <<" "<< i <<endl;
                ranks[j]++;
            }
        }
    }
}

int main() {
    std::fstream file;
	int amount = 0;
    file.open("test2.txt", std::ios::in);
	if (!file) {
		cout << "Can't open the file"<< endl;
		exit(1);
	}
	while (file >> points[amount].x >> points[amount].y) {
		points[amount].index = amount;
        amount++;
	}
	heapsort(points, amount);
	DC(0, amount-1);

	double sum = 0, max = ranks[0], min = ranks[0];
    //cout << "Rank" << endl;
	for (int i = 0; i < amount; i++)
	{
        
        //cout << ranks[i] << endl;
		if (ranks[i] > max)
			max = ranks[i];
		if (ranks[i] < min)
			min = ranks[i];
		
        sum += ranks[i];
	}
	cout << "Total: " << amount << " points" << endl;
    cout << "Max rank: " << max << endl;
    cout << "min rank: " << min << endl;
	cout << "Avg rank: " << fixed << setprecision(2) << sum / amount;
    file.close();
    return 0;
}