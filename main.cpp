#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
#include <time.h>
#include <string>
#include <windows.h>

using namespace std;

time_t current_date;

#pragma warning(disable: 4996)

class TimeHandle {
public:
    static time_t giveCurrentTime() {
        time_t rawtime;
        struct tm* timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        timeinfo->tm_hour = 23;
        timeinfo->tm_min = 59;
        timeinfo->tm_sec = 59;

        //printf("Current local time and date: %s", asctime(timeinfo));

        return (mktime(timeinfo));

    }
    static time_t giveToDoTime(int month, int day) {
        struct tm* to_do_date;
        time_t rawtime;
        time(&rawtime);
        to_do_date = localtime(&rawtime);
        to_do_date->tm_hour = 0;
        to_do_date->tm_min = 0;
        to_do_date->tm_sec = 0;
        to_do_date->tm_year = 2022 - 1900;
        to_do_date->tm_mon = month - 1;
        to_do_date->tm_mday = day;

        //cout << mktime(to_do_date);

        return mktime(to_do_date);
    }
    static int returnTimeDiff(time_t curr, time_t to_do_time) {
        return (int)difftime(curr, to_do_time);
    }
};

class ToDoItem {

public:
    static int count;
    string quest;
    time_t date;
    int ID;
    bool is_done;
    bool is_important;
    bool archive;

    int counter() {
        return count++;
    }

    ToDoItem(vector < ToDoItem >& vectorOfAllQuests, vector < ToDoItem >& vectorOfUI, vector < ToDoItem >& vectorOfNUI, vector < ToDoItem >& vectorOfUNI, vector < ToDoItem >& vectorOfNUNI) {
        int month, day;

        cout << "What to do:";
        cin >> this->quest;
        cout << "Is it important? 0 - NO 1 - YES";
        cin >> this->is_important;
        cout << "Dedline month:";
        cin >> month;
        cout << "Dedline day:";
        cin >> day;
        this->date = TimeHandle::giveToDoTime(month, day);
        this->is_done = 0;
        this->archive = 0;

        vectorOfAllQuests.push_back(ToDoItem(ID, is_done, is_important, archive, date, quest));
        int i = vectorOfAllQuests.size() - 1;

        if (vectorOfAllQuests[i].is_important == 1 && TimeHandle::returnTimeDiff(current_date, vectorOfAllQuests[i].date) > -259200)
            vectorOfUI.push_back(vectorOfAllQuests[i]);

        else if (vectorOfAllQuests[i].is_important == 1 && TimeHandle::returnTimeDiff(current_date, vectorOfAllQuests[i].date) < -259200)
            vectorOfNUI.push_back(vectorOfAllQuests[i]);

        else if (vectorOfAllQuests[i].is_important == 0 && TimeHandle::returnTimeDiff(current_date, vectorOfAllQuests[i].date) > -259200)
            vectorOfUNI.push_back(vectorOfAllQuests[i]);

        else if (vectorOfAllQuests[i].is_important == 0 && TimeHandle::returnTimeDiff(current_date, vectorOfAllQuests[i].date) < -259200)
            vectorOfNUNI.push_back(vectorOfAllQuests[i]);

        else
            cout << "error";

    }
    ToDoItem(int id, int is_done, int is_important, int archive, int date, string quest) {

        this->ID = counter();
        this->is_done = is_done;
        this->archive = archive;
        this->date = date;
        this->is_important = is_important;
        this->quest = quest;

    }
    void printToDoAll() const {
        cout << "\nquest: " << quest << "\nis_important: " << is_important << "\nis_done: " << is_done << "\narchive: " << archive << "\ndate: " << date << endl;
    }
    void printToDo() const {
        HANDLE hConsole;
        int k = 7;

        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        if (this->is_done == 0) {
            if ((TimeHandle::returnTimeDiff(current_date, this->date) > -259200) && (TimeHandle::returnTimeDiff(current_date, this->date) < 0))
                k = 6;
            else if (TimeHandle::returnTimeDiff(current_date, this->date) >= 0)
                k = 4;
            else
                k = 2;

            SetConsoleTextAttribute(hConsole, k);

        }

        string cross = "[ ]";
        if (is_done == 1)
            cross = "[X]";

        time_t rawtime = date;
        struct tm* timeinfo;
        timeinfo = localtime(&rawtime);

        cout << ID << ". " << cross << " " << timeinfo->tm_mday << "-" << timeinfo->tm_mon + 1 << " " << quest << endl;
        SetConsoleTextAttribute(hConsole, 7);
    }
    static void changeToDoItem(int id, int remove, vector < ToDoItem >& vectorOfAllQuests, vector < ToDoItem >& vectorOfUI, vector < ToDoItem >& vectorOfNUI, vector < ToDoItem >& vectorOfUNI, vector < ToDoItem >& vectorOfNUNI) {

        for (int i = 0; i < vectorOfAllQuests.size(); i++) {
            if (vectorOfAllQuests[i].ID == id)
                if (remove == 0)
                    if (vectorOfAllQuests[i].is_done == 0)
                        vectorOfAllQuests[i].is_done = 1;
                    else
                        vectorOfAllQuests[i].is_done = 0;
                else
                    vectorOfAllQuests[i].archive = 1;
        }

        for (int i = 0; i < vectorOfUI.size(); i++) {
            if (vectorOfUI[i].ID == id)
                if (remove == 0)
                    if (vectorOfUI[i].is_done == 0)
                        vectorOfUI[i].is_done = 1;
                    else
                        vectorOfUI[i].is_done = 0;
                else
                    vectorOfUI[i].archive = 1;
        }
        for (int i = 0; i < vectorOfNUI.size(); i++) {
            if (vectorOfNUI[i].ID == id)
                if (remove == 0)
                    if (vectorOfNUI[i].is_done == 0)
                        vectorOfNUI[i].is_done = 1;
                    else
                        vectorOfNUI[i].is_done = 0;
                else
                    vectorOfNUI[i].archive = 1;
        }
        for (int i = 0; i < vectorOfUNI.size(); i++) {
            if (vectorOfUNI[i].ID == id)
                if (remove == 0)
                    if (vectorOfUNI[i].is_done == 0)
                        vectorOfUNI[i].is_done = 1;
                    else
                        vectorOfUNI[i].is_done = 0;
                else
                    vectorOfUNI[i].archive = 1;
        }
        for (int i = 0; i < vectorOfNUNI.size(); i++) {
            if (vectorOfNUNI[i].ID == id)
                if (remove == 0)
                    if (vectorOfNUNI[i].is_done == 0)
                        vectorOfNUNI[i].is_done = 1;
                    else
                        vectorOfNUNI[i].is_done = 0;
                else
                    vectorOfNUNI[i].archive = 1;
        }

    }

};

int ToDoItem::count = 0;

void bubbleSort(vector < ToDoItem >& a) {
    bool swapp = true;
    while (swapp) {
        swapp = false;
        for (size_t i = 0; i < a.size() - 1; i++) {
            if (a[i].date > a[i + 1].date) {
                a[i].date += a[i + 1].date;
                a[i + 1].date = a[i].date - a[i + 1].date;
                a[i].date -= a[i + 1].date;
                swapp = true;
            }
        }
    }
}

void start(vector < ToDoItem >& vectorOfAllQuests, vector < ToDoItem >& vectorOfUI, vector < ToDoItem >& vectorOfNUI, vector < ToDoItem >& vectorOfUNI, vector < ToDoItem >& vectorOfNUNI) {
    vector < vector < string >> content;
    vector < string > row;
    string line, word;

    fstream file("matrix.csv", ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
        file.close();
    }
    else
        cout << "Could not open the file\n";

    for (int i = 0; i < content.size(); i++) {
        vectorOfAllQuests.push_back(ToDoItem(stoi(content[i][0]), stoi(content[i][1]), stoi(content[i][2]), stoi(content[i][3]), stoi(content[i][4]), content[i][5]));

        if (vectorOfAllQuests[i].is_important == 1 && TimeHandle::returnTimeDiff(current_date, vectorOfAllQuests[i].date) > -259200)
            vectorOfUI.push_back(vectorOfAllQuests[i]);

        else if (vectorOfAllQuests[i].is_important == 1 && TimeHandle::returnTimeDiff(current_date, vectorOfAllQuests[i].date) < -259200)
            vectorOfNUI.push_back(vectorOfAllQuests[i]);

        else if (vectorOfAllQuests[i].is_important == 0 && TimeHandle::returnTimeDiff(current_date, vectorOfAllQuests[i].date) > -259200)
            vectorOfUNI.push_back(vectorOfAllQuests[i]);

        else if (vectorOfAllQuests[i].is_important == 0 && TimeHandle::returnTimeDiff(current_date, vectorOfAllQuests[i].date) < -259200)
            vectorOfNUNI.push_back(vectorOfAllQuests[i]);

        else
            cout << "error";
    }

}
void printMatrix(vector < ToDoItem >& vectorOfAllQuests, vector < ToDoItem >& vectorOfUI, vector < ToDoItem >& vectorOfNUI, vector < ToDoItem >& vectorOfUNI, vector < ToDoItem >& vectorOfNUNI) {

    cout << " \nURGENT & IMPORTANT\n";
    bubbleSort(vectorOfUI);
    for (int i = 0; i < vectorOfUI.size(); i++) {

        if (vectorOfUI[i].archive == 0)
            vectorOfUI[i].printToDo();
    }

    cout << "\n NOT URGENT & IMPORTANT\n";
    bubbleSort(vectorOfNUI);
    for (int i = 0; i < vectorOfNUI.size(); i++) {

        if (vectorOfNUI[i].archive == 0)
            vectorOfNUI[i].printToDo();
    }

    cout << "\n URGENT & NOT IMPORTANT\n";
    bubbleSort(vectorOfUNI);
    for (int i = 0; i < vectorOfUNI.size(); i++) {

        if (vectorOfUNI[i].archive == 0)
            vectorOfUNI[i].printToDo();
    }

    cout << "\n NOT URGENT & NOT IMPORTANT\n";
    bubbleSort(vectorOfNUNI);
    for (int i = 0; i < vectorOfNUNI.size(); i++) {

        if (vectorOfNUNI[i].archive == 0)
            vectorOfNUNI[i].printToDo();
    }
}

void saveAndQuit(vector < ToDoItem >& vectorOfAllQuests, vector < ToDoItem >& vectorOfUI, vector < ToDoItem >& vectorOfNUI, vector < ToDoItem >& vectorOfUNI, vector < ToDoItem >& vectorOfNUNI) {

    std::ofstream myfile;
    std::ofstream myfile2;
    myfile.open("archive.csv", ios::app);
    myfile2.open("matrix.csv");
    //myfile << "This is the first cell in the first column.\n";
    for (int i = 0; i < vectorOfAllQuests.size(); i++) {
        if ((vectorOfAllQuests[i].archive == 1) || (vectorOfAllQuests[i].is_done == 1)) {
            myfile << 0 << "," << vectorOfAllQuests[i].is_done << "," << vectorOfAllQuests[i].is_important << "," << vectorOfAllQuests[i].archive << "," << vectorOfAllQuests[i].date << "," << vectorOfAllQuests[i].quest << "\n";
        }
        else
            myfile2 << 0 << ", " << vectorOfAllQuests[i].is_done << ", " << vectorOfAllQuests[i].is_important << ", " << vectorOfAllQuests[i].archive << "," << vectorOfAllQuests[i].date << "," << vectorOfAllQuests[i].quest << "\n";
    }
    myfile.close();
    myfile2.close();

    exit(0);
}
int main() {

    current_date = TimeHandle::giveCurrentTime();
    vector < ToDoItem > vectorOfAllQuests;
    vector < ToDoItem > vectorOfUI;
    vector < ToDoItem > vectorOfNUI;
    vector < ToDoItem > vectorOfUNI;
    vector < ToDoItem > vectorOfNUNI;
    start(vectorOfAllQuests, vectorOfUI, vectorOfNUI, vectorOfUNI, vectorOfNUNI);
    while (true) {
        int menu_choice;
        cout << "1.ADD TO DO ITEM\n2.SHOW MATRIX\n3.SAVE AND QUIT\nChoise:";
        cin >> menu_choice;
        if (menu_choice == 1)
            ToDoItem::ToDoItem(vectorOfAllQuests, vectorOfUI, vectorOfNUI, vectorOfUNI, vectorOfNUNI);
        else if (menu_choice == 2) {
            printMatrix(vectorOfAllQuests, vectorOfUI, vectorOfNUI, vectorOfUNI, vectorOfNUNI);
            int menu_choice2;
            cout << "1.MARK DONE/UNMARK DONE\n2.REMOVE\n3.BACK TO MENU\nChoise:";
            cin >> menu_choice2;
            if (menu_choice2 == 1) {
                cout << "Choose ID:";
                int id;
                cin >> id;
                ToDoItem::changeToDoItem(id, 0, vectorOfAllQuests, vectorOfUI, vectorOfNUI, vectorOfUNI, vectorOfNUNI);
            }
            else if (menu_choice2 == 2) {
                cout << "Choose ID:";
                int id;
                cin >> id;
                ToDoItem::changeToDoItem(id, 1, vectorOfAllQuests, vectorOfUI, vectorOfNUI, vectorOfUNI, vectorOfNUNI);
            }

        }
        else if (menu_choice == 3)
            saveAndQuit(vectorOfAllQuests, vectorOfUI, vectorOfNUI, vectorOfUNI, vectorOfNUNI);

    }

    start(vectorOfAllQuests, vectorOfUI, vectorOfNUI, vectorOfUNI, vectorOfNUNI);
    printMatrix(vectorOfAllQuests, vectorOfUI, vectorOfNUI, vectorOfUNI, vectorOfNUNI);
    printMatrix(vectorOfAllQuests, vectorOfUI, vectorOfNUI, vectorOfUNI, vectorOfNUNI);

    return 0;
}