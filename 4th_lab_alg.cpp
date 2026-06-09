#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <fstream>  
#include <sstream> //str
using namespace std;

class Student {
private:
    int id;
    string name;
    int score;
public:

    Student(int ID, const string& n, int Sc) : id(ID), name(n), score(Sc) {}

    int get_id() const {
        return id;
    }
    string get_name() const {
        return name;
    }
    int get_score() const {
        return score;
    }

    void info() const {
        cout << id << " | " << name << " " << score << endl;;
    }
    void setScore(int new_s) { score = new_s; }

    string str_to_file()const {
        return "# " + to_string(id) + " | " + name + " | " + to_string(score);
    }
    
    static Student st_from_file(const string& line) {
        stringstream ss(line);
        string Stid, Stname, Stscore;

        getline(ss, Stid, '|');
        getline(ss, Stname, '|');
        getline(ss, Stscore, '|');

        int id = stoi(Stid);
        int score = stoi(Stscore);

        return Student(id, Stname, score);
    }
};

class Journal {
private:
    map<int, shared_ptr<Student>> StId;
    map <string, shared_ptr<Student>> StName;
    int next;
public:
    Journal() :next(1) {}

    bool add_St(const string& name, int score) {
        if (StName.find(name) != StName.end()) {
            cout << "Student are already in Journal" << endl;
            return false;
        }
        auto student = make_shared<Student>(next, name, score);

        StId[next] = student;
        StName[name] = student;

        next++;
        cout << "Student " << name << " is added" << endl;
        return true;
    }

    bool change_score_byName(const string& name, int new_s) {
        auto curr_st = StName.find(name);
        if (curr_st == StName.end()) {
            cout << "Student " << name << " not foud" << endl;
            return false;
        }
        curr_st->second->setScore(new_s);
        cout << "Student`s score (" << name << ") was changed to " << new_s << endl;
        return true;
    }

    bool change_score_byID(int ID, int new_s) {
        auto curr_st = StId.find(ID);
        if (curr_st == StId.end()) {
            cout << "Student with id: " << ID << " not found" << endl;
            return false;
        }
        curr_st->second->setScore(new_s);
        cout << "Student`s (with id: " << ID << ") score was change to " << new_s << endl;
        return true;
    }

    int get_score_byName(const string& name) {
        auto curr_st = StName.find(name);
        if (curr_st == StName.end()) {
            cout << "Student " << name << " not found" << endl;
            return -1;
        }
        return curr_st->second->get_score();
    }

    int get_score_byID(int ID) {
        auto curr_st = StId.find(ID);
        if (curr_st == StId.end()) {
            cout << "Student with id: " << ID << " not found" << endl;
            return -1;
        }
        return curr_st->second->get_score();
    }

    void print() {
        if (StName.empty()) {
            cout << "Journal is empty" << endl;
            return;
        }
        cout << endl<< "====Journal====" << endl;
        for (const auto& pair : StId) {
            pair.second->info();
        }
        cout << "===============" << endl << endl;
    }

    bool StbyName(const string& name) const {
        return StName.find(name) != StName.end();
    }

    bool StbyId(int id) const {
        return StId.find(id) != StId.end();
    }

   
    bool saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "ERROR: file " << filename << " doesn`t opening for writing" << endl;
            return false;
        }

        for (const auto& pair : StId) {
            file << pair.second->str_to_file() << endl;
        }

        file.close();
        cout << "Journal successfuly added to '" << filename << "'" << endl;
        return true;
    }

    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "ERROR: file " << filename << " doesn`t opening for reading" << endl;
            return false;
        }

        StId.clear();
        StName.clear();

        size_t count;
        file >> count;

        file >> next;
        file.ignore();

        string line;
        int maxId = 0;

        for (size_t i = 0; i < count; i++) {
            getline(file, line);
            if (line.empty()) continue;

            Student student = Student::st_from_file(line);

            shared_ptr<Student> studentPtr = make_shared<Student>(student.get_id(), student.get_name(), student.get_score());

            StId[student.get_id()] = studentPtr;
            StName[student.get_name()] = studentPtr;

            if (student.get_id() > maxId) {
                maxId = student.get_id();
            }
        }

        if (next <= maxId) {
            next = maxId + 1;
        }

        file.close();
        cout << "Journal is loaded from '" << filename << "' (" << StId.size() << " students)" << endl;
        return true;
    }
};

void Menu(Journal& journal) {
    int choice;
    string name;
    int id, score;
    string filename;

    do {
        cout << "\n=== Journal ===" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Set score by name" << endl;
        cout << "3. Set score by ID" << endl;
        cout << "4. Get score by nam" << endl;
        cout << "5. Get score by ID" << endl;
        cout << "6. Show Journal" << endl;
        cout << "7. Export to file" << endl;
        cout << "8. Load from file" << endl;
        cout << "0. Exit" << endl;
        cout << "Select action: ";
        cin >> choice;


        switch (choice) {

        case 1: {
            cout << "Put the student`s name: ";
            cin >> name;
            cout << "Put the score: ";
            cin >> score;
            journal.add_St(name, score);
            break;
        }

        case 2: {
            cout << "Put the student`s name: ";
            cin >> name;
            cout << "Put the new score: ";
            cin >> score;
            journal.change_score_byName(name, score);
            break;
        }

        case 3: {
            cout << "Put the student`s ID: ";
            cin >> id;
            cout << "Put the new score: ";
            cin >> score;
            journal.change_score_byID(id, score);
            break;
        }

        case 4: {
            cout << "Put the student`s name:: ";
            cin >> name;
            score = journal.get_score_byName(name);
            if (score != -1)
                cout << name << "`s score: " << score << endl;
            break;
        }
        case 5: {
            cout << "Put the student`s ID: ";
            cin >> id;
            score = journal.get_score_byID(id);
            if (score != -1)
                cout << "Score student bi ID " << id << ": " << score << endl;
            break;
        }
        case 6: {
            journal.print();
            break;
        }

        case 7: {
            cout << "Filename for saving to: ";
            cin >> filename;
            journal.saveToFile(filename);
            break;
        }
        case 8: {
            cout << "Filename for loading from: ";
            cin >> filename;
            journal.loadFromFile(filename);
            break;
        }
        case 0:
        {
            break;
        }
        }
    } while (choice != 0);

    int answer;
    // Автоматическое сохранение при выходе
    cout << "Save data before exiting? (y/n): ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        cout << "Filename for saving to: ";
        cin >> filename;
        journal.saveToFile(filename);
    }
}

int main() {
    Journal journal;

    Menu(journal);

    return 0;
} 
