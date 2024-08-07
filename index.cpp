#include <bits/stdc++.h>
using namespace std;

void storeToFile(string password)
{
    ofstream file;
    file.open("npmstart.csv", ios::app);
    if (file.is_open())
    {
        file << password << endl;
        file.close();
    }
    else
    {
        cerr << "Unable to open file for writing." << endl;
    }
}

int main()
{
    srand(time(0)); // Khởi tạo seed cho hàm rand()
    set<int> uniqueNumbers;
    while (uniqueNumbers.size() < 250)
    {
        int randomIndex = rand() % 2501; // Tạo số ngẫu nhiên từ 0 đến 2500
        if (uniqueNumbers.find(randomIndex) == uniqueNumbers.end())
        {
            uniqueNumbers.insert(randomIndex);
            string index = to_string(randomIndex);
            storeToFile(index);
        }
    }
    return 0;
}

// g++ index.cpp -o index