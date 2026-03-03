 // ArrayFile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cmath>
#include <windows.h>

using namespace std;

//////////////////////////////////////////////////////////////
// Enable console encoding
//////////////////////////////////////////////////////////////
void initConsole()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
}

//////////////////////////////////////////////////////////////
// 3.1 Input array and save to TEXT file
//////////////////////////////////////////////////////////////
void inputArrayText(vector<int>& arr)
{
    int n;
    cout << "Enter array size: ";
    cin >> n;

    arr.resize(n);
    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    ofstream file("array.txt");
    for (int x : arr)
        file << x << " ";

    file.close();
}

//////////////////////////////////////////////////////////////
// 3.2 Generate random array + input T + save files
//////////////////////////////////////////////////////////////
void randomArrayBinary()
{
    srand(time(0));
    int n;

    cout << "Enter array size: ";
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
        arr[i] = rand() % 201 - 100;

    // INPUT VALUE T
    int T;
    cout << "Enter value T: ";
    cin >> T;

    // save T
    ofstream tfile("T.txt");
    tfile << T;
    tfile.close();

    // save array
    ofstream file("array.bin", ios::binary);
    file.write((char*)&n, sizeof(n));
    file.write((char*)arr.data(), n * sizeof(int));
    file.close();

    cout << "Array generated and saved.\n";
    cout << "Value T saved to file.\n";
}

//////////////////////////////////////////////////////////////
// Read array from TEXT file
//////////////////////////////////////////////////////////////
vector<int> readTextArray()
{
    ifstream file("array.txt");
    vector<int> arr;
    int x;

    while (file >> x)
        arr.push_back(x);

    return arr;
}

//////////////////////////////////////////////////////////////
// Read array from BINARY file
//////////////////////////////////////////////////////////////
vector<int> readBinaryArray()
{
    ifstream file("array.bin", ios::binary);
    int n;
    file.read((char*)&n, sizeof(n));

    vector<int> arr(n);
    file.read((char*)arr.data(), n * sizeof(int));

    return arr;
}

//////////////////////////////////////////////////////////////
// Read value T from file
//////////////////////////////////////////////////////////////
int readT()
{
    ifstream file("T.txt");
    int T;
    file >> T;
    return T;
}

//////////////////////////////////////////////////////////////
// Remove negative elements
//////////////////////////////////////////////////////////////
void removeNegative(vector<int>& arr)
{
    vector<int> result;

    for (int x : arr)
        if (x >= 0)
            result.push_back(x);

    arr = result;
}

//////////////////////////////////////////////////////////////
// Find first maximum negative before T
//////////////////////////////////////////////////////////////
void firstMaxNegativeBeforeT(const vector<int>& arr, int T)
{
    int maxNeg = -1000000;
    int index = -1;

    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == T)
            break;

        if (arr[i] < 0 && arr[i] > maxNeg)
        {
            maxNeg = arr[i];
            index = i;
        }
    }

    if (index == -1)
        cout << "No negative elements found before T\n";
    else
        cout << "Index of first maximum negative: " << index << endl;
}

//////////////////////////////////////////////////////////////
// Average distance to school
//////////////////////////////////////////////////////////////
void averageDistance()
{
    double sx, sy;
    int n;

    cout << "\nEnter school coordinates (x y): ";
    cin >> sx >> sy;

    cout << "Enter number of houses: ";
    cin >> n;

    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        double x, y;
        cout << "House " << i + 1 << " (x y): ";
        cin >> x >> y;

        double dist = sqrt(pow(x - sx, 2) + pow(y - sy, 2));
        sum += dist;
    }

    cout << "Average distance: " << sum / n << endl;
}

//////////////////////////////////////////////////////////////
// Solve tasks and save result
//////////////////////////////////////////////////////////////
void solveTasks()
{
    vector<int> arr = readTextArray();

    cout << "\nArray from file:\n";
    for (int x : arr) cout << x << " ";
    cout << endl;

    removeNegative(arr);

    ofstream out("result.txt");
    out << "Array without negative values:\n";

    for (int x : arr)
    {
        cout << x << " ";
        out << x << " ";
    }

    cout << endl;
    out.close();
}

//////////////////////////////////////////////////////////////
// Read binary file to vector
//////////////////////////////////////////////////////////////
void readToVector()
{
    vector<int> arr = readBinaryArray();

    cout << "\nData from binary file:\n";
    for (int x : arr)
        cout << x << " ";

    cout << endl;
}

//////////////////////////////////////////////////////////////
// MAIN MENU
//////////////////////////////////////////////////////////////
int main()
{
    initConsole();

    vector<int> arr;
    int choice;

    do
    {
        cout << "\n========== MENU ==========\n";
        cout << "1 - Input array (text file)\n";
        cout << "2 - Generate array + input T\n";
        cout << "3 - Remove negatives (from file)\n";
        cout << "4 - Find max negative before T\n";
        cout << "5 - Average distance to school\n";
        cout << "6 - Read binary to vector\n";
        cout << "0 - Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            inputArrayText(arr);
            break;

        case 2:
            randomArrayBinary();
            break;

        case 3:
            solveTasks();
            break;

        case 4:
        {
            vector<int> arr = readTextArray();
            int T = readT();
            firstMaxNegativeBeforeT(arr, T);
            break;
        }

        case 5:
            averageDistance();
            break;

        case 6:
            readToVector();
            break;
        }

    } while (choice != 0);
}