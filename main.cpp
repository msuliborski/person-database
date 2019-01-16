#include <cmath>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person();
    Person(string name);
    ~Person();

    string name;
    string surname;
    string secondName;
    int age;

    void setName(string n);
    string getName();
};
Person::Person() {
    name = "Unknown";
}
Person::Person(string n) {
    name = n;
}
Person::~Person() {
}
void Person::setName(string n) {
    name = n;
}
string Person::getName() {
    return name;
}

static vector<Person> people;

string cleanStringForName(string s) {
    string cleanString = "";
    int i = 0;

    while (i < s.length()) {
        if (((char)s[i] >= 65 && (char)s[i] <= 90) || ((char)s[i] >= 97 && (char)s[i] <= 122) || s[i] == '-') cleanString += s[i];
        i++;
        if ((char)s[i] == 32) break;
    }
    return cleanString;
}
string cleanStringForAge(string s) {
    string cleanString = "";
    int i = 0;

    while (i < s.length()) {
        if (((char)s[i] >= 48 && (char)s[i] <= 57)) cleanString += s[i];
        i++;
        if ((char)s[i] == 32) break;
    }
    return cleanString;
}
string cleanStringForFileName(string s) {
    string cleanString = "";
    int i = 0;
    while (i < s.length()) {
        if (!(s[i] == '<' || s[i] == '>' || s[i] == ':' || s[i] == '"' || s[i] == '/' || ((char)s[i] == 92) || s[i] == '|' || s[i] == '?' || s[i] == '*')) cleanString += s[i];
        i++;
        if ((char)s[i] == 32) break;
    }
    return cleanString;
}

int getNumberFromUser(int from, int to) {
    string input; int inputInt;
    int exception;
    while (true)
    {
        try {
            getline(cin, input); inputInt = atoi(input.c_str());
            if (input.length() != ((int)(log10(inputInt)) + 1)) { throw exception = 1; }
            else if (inputInt < from || inputInt > to) { throw exception = 1; }
            else if ((inputInt == 1 || inputInt == 3 || inputInt == 4) && people.size() == 0) { throw exception = 2; }
            break;
        }
        catch (int exception) {
            if (exception == 1) cout << "Invalid input. Try Again: ";
            else if (exception == 2) cout << "\nNo people. Edit, delete and export not avaliable. Try Again: ";
        }

    }
    return inputInt;
}
string getNameFromUser() {
    string input, cleanInput;
    int exception;
    while (true)
    {
        try {
            getline(cin, input); cleanInput = cleanStringForName(input);
            if (cleanInput.length() > 30) { throw exception = 1; }
            else if (cleanInput != input) { throw exception = 2; }
            break;
        }
        catch (int exception) {
            if (exception == 1) cout << "/nToo long. Try Again: ";
            else if (exception == 2) { cout << "\nName had some invalid characters. Name converted to: " << cleanInput << endl; break; }
        }

    }
    return cleanInput;
}
string getAgeFromUser() {
    string input, cleanInput;
    int exception;
    while (true)
    {
        try {
            getline(cin, input); cleanInput = cleanStringForAge(input);
            if (cleanInput.length() > 3) { throw exception = 1; }
            else if (cleanInput != input) { throw exception = 2; }
            break;
        }
        catch (int exception) {
            if (exception == 1) cout << "/nToo long. Try Again: ";
            else if (exception == 2) { cout << "\nAge had some invalid characters. Age converted to: " << cleanInput << endl; break; }
        }

    }
    return cleanInput;
}
string getFileNameFromUser() {
    string input, cleanInput;
    int exception;
    while (true)
    {
        try {
            getline(cin, input); cleanInput = cleanStringForFileName(input);
            if (cleanInput.length() > 255) { throw exception = 1; }
            else if (cleanInput != input) { throw exception = 2; }
            break;
        }
        catch (int exception) {
            if (exception == 1) cout << "/nToo long. Try Again: ";
            else if (exception == 2) { cout << "\nName had some invalid characters. Name converted to: " << cleanInput << endl; break; }
        }
    }
    return cleanInput;
}

void addPersonFromFileLineToPeople(string s, int lineNumber) {
    int i = 0; //current line sign
    string name = "", surname = "", secondName = "", age = "";

    while (i < s.length()) {
        name += s[i]; i++;
        if ((char)s[i] == 32) { i++; break; }
    }

    while (i < s.length()) {
        surname += s[i]; i++;
        if ((char)s[i] == 32) { i++; break; }
    }

    while (i < s.length()) {
        secondName += s[i]; i++;
        if ((char)s[i] == 32) { i++; break; }
    }

    while (i < s.length()) {
        age += s[i]; i++;
        if ((char)s[i] == 32) { i++; break; }
    }

    int exception;
    while (true) {
        try {
            name = cleanStringForName(name);
            surname = cleanStringForName(surname);
            secondName = cleanStringForName(secondName);
            age = cleanStringForAge(age);
            if (name == "") { throw exception = 1; }
            else {
                Person person = Person(name);

                if (surname != "") person.surname = surname;
                else person.surname = "Unknown";

                if (secondName != "") person.secondName = secondName;
                else person.secondName = "---";

                if (age != "") person.age = atoi(age.c_str());
                else person.age = 0;

                people.push_back(person);
            }
            break;
        }
        catch (int exception) {
            if (exception == 1) cout << "Cound not get any data from line #" << lineNumber << endl;
            break;
        }
    }

}

void showPeople() {
    if (people.size() == 0) cout << "\nNo people :(\n\n (You cannot edit, delete or export)\n\n";
    for (int i = 0; i < people.size(); i++) {
        cout << "Person #" << i + 1 << ":" << endl;
        cout << "Name: " << people[i].getName() << "\nSurname: " << people[i].surname << "\nSecond Name: " << people[i].secondName << "\nAge: " << people[i].age << endl << endl;
    }
}
void showPeople(int i) {
    if (i >= 0 && i <= people.size())
        cout << "Person #" << i + 1 << ":" << endl;
    cout << "Name: " << people[i].getName() << "\nSurname: " << people[i].surname << "\nSecond Name: " << people[i].secondName << "\nAge: " << people[i].age << endl << endl;
}

void inputFile() {

    ifstream inputFile;

    cout << "\033[2J\033[1;1H";
    cout << "[INPUT PEOPLE FROM FILE]" << endl << endl;
    cout << "Give the name of input file: ";
    int exception;
    while (true) {
        try {
            inputFile.open(getFileNameFromUser());
            if (!inputFile.is_open()) throw exception = 1;
            break;
        }
        catch (int exception) {
            if (exception == 1) {
                cout << "\033[2J\033[1;1H";
                cout << "[INPUT PEOPLE FROM FILE]" << endl << endl;
                cout << "Invalid input. Try Again: ";
            }
        }
    }



    Person tempPerson;
    string tempLine;
    int lineNumber = 1;

    while (getline(inputFile, tempLine)) { addPersonFromFileLineToPeople(tempLine, lineNumber); lineNumber++; }

    inputFile.close();

    cout << "\n--- SUCCESS! ---";
    cout << "\n\nPeople have been imported!";
    cout << endl;  system("pause");
}

int askUserWhatToDo() {
    cout << "\033[2J\033[1;1H";
    showPeople();
    cout << "What do you want to do?\n";
    cout << "1. Edit person's data\n";
    cout << "2. Add new person\n";
    cout << "3. Delete person\n";
    cout << "4. Output all data to file\n";
    cout << "5. Exit the program\n";
    cout << "TYPE NUMBER: ";

    return getNumberFromUser(1, 5);
}

int askUserWhoToEdit() {
    cout << "\033[2J\033[1;1H";
    showPeople();
    cout << "Who do you want to edit?" << endl;
    cout << "TYPE NUMBER: ";
    return getNumberFromUser(1, people.size() + 1);
}
int askUserWhatToEdit(int id) {
    cout << "\033[2J\033[1;1H";
    showPeople(id);
    cout << "What do you want to edit?\n";
    cout << "1. Name\n";
    cout << "2. Surname\n";
    cout << "3. Second name\n";
    cout << "4. Age\n";
    cout << "TYPE NUMBER: ";
    return getNumberFromUser(1, 4);
}
void editValue(int whos, int what) {
    cout << "\033[2J\033[1;1H";
    cout << "[EDIT PERSON #" << whos + 1 << "]" << endl << endl;
    switch (what) {
        case 1:
            cout << "Old name: " << people[whos].name << endl << endl;
            cout << "New name: ";
            people[whos].name = getNameFromUser();
            break;

        case 2:
            cout << "Old surname: " << people[whos].surname << endl;
            cout << "New surname: ";
            people[whos].surname = getNameFromUser();
            break;
        case 3:
            cout << "Old second name: " << people[whos].secondName << endl;
            cout << "New second name: ";
            people[whos].secondName = getNameFromUser();
            break;
        case 4:
            cout << "Old age: " << people[whos].age << endl;
            cout << "New age: ";
            people[whos].age = atoi(getAgeFromUser().c_str());
            break;
        default: editValue(whos, what);
    }

    cout << "\n--- SUCCESS! ---";
    cout << "\n\nPerson has been edited!";
    cout << endl;  system("pause");
}

void addPerson() {
    cout << "\033[2J\033[1;1H";
    string name = "", surname = "", secondName = "", age = "";

    cout << "[ADD PERSON #" << people.size() + 1 << "]" << endl << endl;
    cout << "Person #" << people.size() + 1 << ":" << endl;
    cout << "Name: ";
    name = getNameFromUser();
    cout << "Surname: ";
    surname = getNameFromUser();
    cout << "Second name: ";
    secondName = getNameFromUser();
    cout << "Age: ";
    age = getAgeFromUser();

    if (name != "") {
        Person person = Person();
        person.name = name;
        person.surname = surname;
        person.secondName = secondName;
        person.age = atoi(age.c_str());
        people.push_back(person);

        cout << "\n--- SUCCESS! ---";
        cout << "\n\nNew person added:\n\n";

        showPeople(people.size() - 1);

        cout << endl;  system("pause");
    }
    else {
        cout << "\n--- FAILED! ---";
        cout << "\n\nNo data provided!";
        cout << endl;  system("pause");
    }
}

int askUserWhoToDelete() {
    cout << "\033[2J\033[1;1H";
    showPeople();
    cout << "Who do you want to delete?\n";
    cout << "TYPE NUMBER: ";
    return getNumberFromUser(1, people.size() + 1);
}
void deletePerson(int id) {
    cout << "\033[2J\033[1;1H";
    string tmp;
    Person person = Person();
    cout << "[DELETE PERSON #" << id + 1 << "]" << endl << endl;
    showPeople(id);

    cout << "Are you sure you want to delete?\n";
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cout << "TYPE NUMBER: ";

    if (getNumberFromUser(1, 2) == 1) {
        people.erase(people.begin() + id);
        cout << "\n--- SUCCESS! ---";
        cout << "\n\nPerson deleted!";
        cout << endl;  system("pause");
    }
}

void outputFile() {
    cout << "\033[2J\033[1;1H";
    cout << "[OUTPUT PEOPLE TO FILE]" << endl << endl;
    cout << "Give the name of output file or type 'exit' to abort exporting to file: ";

    string outputFileName = getFileNameFromUser();
    if (outputFileName == "exit") return;

    ofstream outputFile(outputFileName, ios::out);

    for (int i = 0; i < people.size(); i++) {
        outputFile << people[i].name << " " << people[i].surname << " " << people[i].secondName << " " << people[i].age << endl;
    }

    outputFile.close();
    cout << "\n--- SUCCESS! ---";
    cout << "\n\nAll people have been exported to file: " << outputFileName;
    cout << endl;  system("pause");

}

int main() {

    inputFile();

    showPeople();

    int id;
    while (true) {
        switch (askUserWhatToDo()) {
            case 1: //edit
                id = askUserWhoToEdit() - 1;
                editValue(id, askUserWhatToEdit(id)); break;
            case 2: //add
                addPerson(); break;
            case 3: //del
                deletePerson(askUserWhoToDelete() - 1); break;
            case 4: //export
                outputFile(); break;
            case 5: //exit
                return 0;
            default: break;
        }
    }
}

/*
The program specification :

1. In the program code you should define the class Person or Car or Building
with three different fields of any data type (all public),
2 constructors (one default and one with parameters),
destructor.
-done
-verify default values in constuctors

2. Program should ask the user for the name of the file to open.
-done

3. Program should open the file with name provided by the user in read mode
and in a loop till the file end program should read line by line the values

of the subsequent values of the class Person fields, create the subsequent
objects of the class Person and using constructor or in any other way the
program should assign the values obtained from the file to the fields of the created object.

The example file content:
Jaime Fernandez Molina
Javier Madueno Entrenas
Alberto Fern�ndez Calvo

The example of the first Person object fields values after the first file line reading operation:
FirstName<= Jaime
SecondName<=Fernandez
ThirdName<=Molina

4. Program should add every created object to the dynamic table or list (#include<list>)
or vector structure (#include<vector>).

5. After reading all file lines program should print on a screen the
values of all objects fields for all created objects using table, vector or list iteration.

6. After that the program should ask the user whether to change the
values of the any created object fields, add the new object to the
table or list or vector or delete the specified object. If the user
asks the program to perform the change, addition or removal operation the program should do so.

7. The final operation is to ask the user the name of the output file.
The program should open that file in write mode and write all created
objects fields values to this file one line per object.

8. All operations related to the user input and the file operations
should be enclosed in the try catch blocks in order to handle the exceptions.

Good luck.


I�m waiting for your answer and a program code on my e-mail.
Best regards.
Jan Rogowski

*/