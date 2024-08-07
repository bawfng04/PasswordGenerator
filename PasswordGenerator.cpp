#include <bits/stdc++.h>
using namespace std;

string generator(int length, mt19937 &gen, int specialStringLength = 0)
{
    uniform_int_distribution<> distr(33, 126);
    string password = "";
    for (int j = 0; j < length - specialStringLength - 2; j++)
    {
        char c = (char)distr(gen);
        while (c == ',')
            c = (char)distr(gen);
        password += c;
    }
    return password;
}

string shuffleString(string str)
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    int random = rand() % (random_device()() % 100);
    seed = seed ^ random;
    shuffle(str.begin(), str.end(), default_random_engine(seed));
    return str;
}

string addSpecialString(string password, string specialString, int length, mt19937 &gen)
{
    specialString = shuffleString(specialString);
    uniform_int_distribution<> distr(0, length - specialString.length() - 2);
    int randomIndex = distr(gen);
    password.insert(randomIndex, "[" + specialString + "]");
    return password;
}

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
    random_device rd;
    unsigned seed = rd() ^ static_cast<unsigned>(time(0));
    mt19937 gen(seed);

    while (1)
    {
        int time = 0;
        cout << "enter the time to generate password: ";
        cin >> time;
        string specialString;
        cout << "Enter the special string: ";
        cin >> specialString;
        int length = 0;
        cout << "Enter the length of the password: ";
        cin >> length;
        for (int i = 0; i < time; i++)
        {
            string password = generator(length, gen, specialString.length());
            password = addSpecialString(password, specialString, length, gen);
            cout << password << endl;
            storeToFile(password);
        }
    }
    return 0;
}

// g++ -o passwordGenerator passwordGenerator.cpp