#include <iostream>
#include <algorithm>
#include <ostream>
#include <istream>
#include <iomanip>
#include <iosfwd>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <exception>
#include <stdexcept>
using namespace std;

template <typename T>
void PrintSet(const set<T>& set) {
  for (const T& s : set) {
    cout << s << " " << endl;
  }
  cout << endl;
}

template <typename T1, typename T2>
void printMap(const map<T1, set<T2> >& map) {
  for (const auto& item : map) {
    cout << item.first << ": " << endl;
    PrintSet(item.second);
  }
  cout << endl;
}
// Реализуйте функции и методы классов и при необходимости добавьте свои
class Date {
    int year;
    int month;
    int day;
public:
    Date(int y = 1900, int m = 1, int d = 1): year(y), month(m), day(d) {}
public:
    int GetYear() const{ return year;}
    int GetMonth() const{ return month;}
    int GetDay() const{ return day;}
};

/**
 * @brief operator <<
 * @param stream for date
 * @param date
 * @return
 */
ostream& operator<<(ostream& stream, const Date& date){
    stream << date.GetYear() << "-" << date.GetMonth() << "-" << date.GetDay();
    return stream;
}

bool operator<(const Date& lhs, const Date& rhs){
    if(lhs.GetYear() < rhs.GetYear()){
        return true;
    } else if (lhs.GetYear() == rhs.GetYear()) {
        if(lhs.GetMonth() < rhs.GetMonth()){
            return true;
        } else if (lhs.GetMonth() == rhs.GetMonth()){
            return (lhs.GetDay() < rhs.GetDay());
        } else {
            return false;
        }
    } else {
       return false;
    }
}

class Database {
public:
    void AddEvent(const Date& date, const string& new_event) {
        if (this->dataBaseStorage.count(date) > 0) {
            set<string> key_set = dataBaseStorage.at(date);
            key_set.insert(new_event);
            this->dataBaseStorage[date] = key_set;
            cout << new_event << endl;
        } else {
            set<string> event;
            event.insert(new_event);
            this->dataBaseStorage[date] = event;
            cout << new_event << endl;
        }
    }
    bool DeleteEvent(const Date& date, const string& event){
        if (dataBaseStorage.count(date) > 0) {
            set<string> key_set = dataBaseStorage.at(date);
            auto event_iter = key_set.find(event);
            if(event_iter != key_set.end()){
                key_set.erase(event_iter);
                this->dataBaseStorage[date] = key_set;
                cout << event << " deleted successfully!" << endl;
                return true;
            } else {
                cout << "Event: " << event << " not found!" << endl;
                return false;
            }
        } else {
            cout << "Date " << date << " not found!" << endl;
            return false;
        }

    }
    unsigned int  DeleteDate(const Date& date){
        unsigned int N = 0;
        if (dataBaseStorage.count(date) > 0) {
            set<string> key_set = dataBaseStorage.at(date);
            N = key_set.size();
            auto date_key = dataBaseStorage.find(date);
            dataBaseStorage.erase(date_key);
            cout << "Deleted "<< N << " events" << endl;
            return N;
        } else {
            cout << "Deleted "<< N << " events" << endl;
            return N;
        }
    }

  set<string> Find(const Date& date) const {
      if (dataBaseStorage.count(date) > 0) {
          return dataBaseStorage.at(date);
      } else {
          return {string("dataBase does not contain events in that day")};
      }
  }

  void Print() const {
      cout << "----------" << "START" << "----------" <<  endl;
      printMap(this->dataBaseStorage);
      cout << "----------" << "END" << "----------" <<  endl;
  }
private:
  map<Date, set<string> > dataBaseStorage;
};

int main() {
  Database db;

  string command;
  /*
  while (getline(cin, command)) {
    // Считайте команды с потока ввода и обработайте каждую
      cout << command << endl;
  }
*/

    db.AddEvent({0,1,2}, "event1");
    db.AddEvent({0,1,2}, "event3");
    db.AddEvent({1,2,3}, "event2");
    PrintSet(db.Find({0,1,2}));
    db.Print();
    db.DeleteDate({0,1,2});
    cout << "-----------------" << endl;
  //  db.DeleteDate({99,99,99});
  //  db.Print();

   PrintSet(db.Find({7,8,9}));
  return 0;
}
