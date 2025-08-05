#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Reservation {
    string name;
    int roomNumber;
    int days;
    float costPerDay;

public:
    void input() {
        cout << "Enter customer name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter room number: ";
        cin >> roomNumber;
        cout << "Enter number of days: ";
        cin >> days;
        cout << "Enter cost per day: ";
        cin >> costPerDay;
    }

    void show() const {
        cout << "Name: " << name << "\nRoom No: " << roomNumber
             << "\nDays: " << days << "\nTotal Cost: " << days * costPerDay << endl;
    }

    int getRoomNumber() const { return roomNumber; }

    string getName() const { return name; }

    void saveToFile() {
        ofstream out("reservations.dat", ios::binary | ios::app);
        out.write((char*)this, sizeof(*this));
        out.close();
    }

    static void viewAll() {
        ifstream in("reservations.dat", ios::binary);
        Reservation r;
        while (in.read((char*)&r, sizeof(r))) {
            r.show();
            cout << "---------------------\n";
        }
        in.close();
    }

    static void search(int room) {
        ifstream in("reservations.dat", ios::binary);
        Reservation r;
        bool found = false;
        while (in.read((char*)&r, sizeof(r))) {
            if (r.getRoomNumber() == room) {
                r.show();
                found = true;
                break;
            }
        }
        if (!found) cout << "No reservation found for room " << room << endl;
        in.close();
    }
};

int main() {
    int choice;
    do {
        cout << "\n===== Hotel Reservation Menu =====\n";
        cout << "1. Add Reservation\n";
        cout << "2. View All Reservations\n";
        cout << "3. Search Reservation\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Reservation r;
                r.input();
                r.saveToFile();
                break;
            }
            case 2:
                Reservation::viewAll();
                break;
            case 3: {
                int room;
                cout << "Enter room number to search: ";
                cin >> room;
                Reservation::search(room);
                break;
            }
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
