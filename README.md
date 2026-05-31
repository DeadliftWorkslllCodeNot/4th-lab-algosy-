# Лабораторная работа №4
Выполнила Пермякова Екатерина Алексеевна ИДБ-25-02

# Электронный журнал группы

## Описание задачи
Необходимо реализовать простой электронный журнал.
Система хранит студентов и их баллы. 
Для каждого студента нужно быстро получать текущий результат по имени или по id.

##  Реализовано:
- [Добавление студента в журнал](#-Добавление-студента-в-журнал)
- [Выставление балла](#-Выставление-балла)
- [Получение балла по имени или id](#-Получение-балла-по-имени-или-id)
- [Вывод всех студентов и их результатов](#-Вывод-всех-студентов-и-их-результатов)
- [Проверка: есть ли студент с заданным именем или id](#-Проверка:-есть-ли-студент-с-заданным-именем-или-id)

## Добавление студента в журнал
```cpp
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
```

## Выставление балла
```cpp
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
```

## Получение балла по имени или id
```cpp
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
```

## Вывод всех студентов и их результатов в консоль
```cpp
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
```

## Вывод всех студентов и их результатов в файл
```cpp
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
```

## Проверка: есть ли студент с заданным именем или id
```cpp
    bool StbyName(const string& name) const {
        return StName.find(name) != StName.end();
    }

    bool StbyId(int id) const {
        return StId.find(id) != StId.end();
    }
```


