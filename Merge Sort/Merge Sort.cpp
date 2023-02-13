#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include "Person.h"
#include <sstream>

using namespace std;
vector<Person> record;
int comparisons;

// Match the attributes of Person class to the method parameters.
Person::Person(string n, int i, int a, string j, int h) {
    name = n;
    id = i;
    age = a;
    job = j;
    hireyear = h;
}

int Person::getId() {
    return id;
}

string Person::getName() {
    return name;
}

int Person::getAge() {
    return age;
}

string Person::getJob() {
    return job;
}

int Person::getHireYear() {
    return hireyear;
}


// A helper function that prints the ID.
void printIdOnly() {
    for (Person person : record)
    {
        cout << person.getId() << " ";
    }
    cout << endl;
}

// writes the sorted record to a .txt file
void writeToFile() {
    ofstream ofs;
    ofs.open("C:/Users/Jason Tan/OneDrive - Brigham Young University Hawaii/Documents/output.txt");
    for (Person person : record) {
        ofs << person.getName() << "|" << person.getId() << "|" << person.getAge() << "|" << person.getJob() << "|" << person.getHireYear() << endl;
    }
}

void merge(int left, int mid, int right) {
    // splits the data into smaller subarray of left and right with specified size, with midpoint as a marker.
    int subL = mid - left + 1;
    int subR = right - mid;

    vector<Person> L, R;

    for (int i = 0; i < subL; i++) {
        L.push_back(record[left + i]);
    }
    for (int j = 0; j < subR; j++) {
        R.push_back(record[mid + 1 + j]);
    }

    // performs comparison on the values in the smaller sub arrays and replace the elements in the original array at the appropriate index.
    int i = 0;
    int j = 0;
    int k = left;
    while (i < subL && j < subR) {
        comparisons += 1;
        if (L[i].getId() <= R[j].getId()) {
            record[k] = L[i];
            i++;
        }
        else {
            record[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < subL) {
        comparisons += 1;
        record[k] = L[i];
        i++;
        k++;
    }

    while (j < subR) {
        comparisons += 1;
        record[k] = R[j];
        j++;
        k++;
    }
    //printIdOnly();
}

void mergeSort(int left, int right) {
    // divides the input data into half recursively into smaller subproblems until it is small enough to be solved easily, which is a size of 1
    if (left >= right) {
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(left, mid);
    mergeSort(mid + 1, right);
    // Merges the subproblems back together incrementally to form the final solution
    merge(left, mid, right);
}

// agrc = total argument count, argv = the arguments passed into the function
int main(int argc, char** argv) {
    // check for errors: missing argument or file not found
    if (argc == 1) {
        cout << "You forgot the command line parameter" << endl;
        exit(0);
    }
    ifstream ifs;
    ifs.open(argv[1], ios::in);
    if (!ifs) {
        cout << "could not find file " << argv[1] << endl;
        exit(0);
    }

    // checks the first line of the file to determine the number of records in the file, and the number of times to be looped.
    string firstLine;
    // getline gets the first line from the ifstream and stores it into a string variable
    getline(ifs, firstLine);
    // Convert firstLine into an int
    int recordNum = stoi(firstLine);


    for (int i = 0; i < recordNum; i++)
    {
        string nextLine;
        // gets the nextline
        getline(ifs, nextLine);

        string name;
        int id;
        int age;
        string job;
        int hireyear;

        char delimiter = '|';
        string words;
        stringstream ss(nextLine);
        // gets the next word until it spots a pipe "|" delimeter
        // initializing each object's fields with data from the file
        getline(ss, words, delimiter);
        name = words;
        getline(ss, words, delimiter);
        id = stoi(words);
        getline(ss, words, delimiter);
        age = stoi(words);
        getline(ss, words, delimiter);
        job = words;
        getline(ss, words, delimiter);
        hireyear = stoi(words);

        // instantiating a new object for each record in the file
        Person employee(name, id, age, job, hireyear);
        record.push_back(employee);
    }
    mergeSort(0, record.size() - 1);    cout << "It took " << comparisons << " comparisons to sort this list.";
    //writeToFile();
}

// Big O of Merge Sort is O(n log2 n).