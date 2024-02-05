#include <iostream>
#include <string>
using namespace std;

class Room {
public:
    int roomNumber;
    string type;
    double nightlyRate;
    bool isBooked;

    Room(int number, const string& roomType, double rate)
        : roomNumber(number), type(roomType), nightlyRate(rate), isBooked(false) {}

    double calculateCost(int nights) {
        return nightlyRate * nights;
    }

    void displayDetails() {
        cout << "Room Number: " << roomNumber << "\nType: " << type << "\nNightly Rate: $" << nightlyRate << "\n";
        if (isBooked) {
            cout << "Status: Booked\n";
        } else {
            cout << "Status: Available\n";
        }
        cout << "--------------------------\n";
    }

    void bookRoom() {
        if (!isBooked) {
            isBooked = true;
            cout << "Room " << roomNumber << " booked successfully.\n";
        } else {
            cout << "Sorry, Room " << roomNumber << " is already booked.\n";
        }
    }
};

class StandardRoom : public Room {
public:
    StandardRoom(int number)
        : Room(number, "Standard", 100.0) {}
};

class DeluxeRoom : public Room {
public:
    DeluxeRoom(int number)
        : Room(number, "Deluxe", 150.0) {}
};

class ExecutiveRoom : public Room {
public:
    ExecutiveRoom(int number)
        : Room(number, "Executive", 200.0) {}
};

class Hotel {
private:
    Room* rooms[100];

public:
    Hotel(int numStandardRooms, int numDeluxeRooms, int numExecutiveRooms) {
        // Standard rooms
        for (int i = 1; i <= numStandardRooms; ++i) {
            rooms[i - 1] = new StandardRoom(i);
        }

        // Deluxe rooms
        for (int i = 1; i <= numDeluxeRooms; ++i) {
            rooms[i - 1 + numStandardRooms] = new DeluxeRoom(i + numStandardRooms);
        }

        // Executive rooms
        for (int i = 1; i <= numExecutiveRooms; ++i) {
            rooms[i - 1 + numStandardRooms + numDeluxeRooms] = new ExecutiveRoom(i + numStandardRooms + numDeluxeRooms);
        }
    }

    ~Hotel() {
        for (int i = 0; i < 100; ++i) {
            delete rooms[i];
        }
    }

    void displayRooms() {
        cout << "Hotel Rooms:\n";
        for (int i = 0; i < 100 && rooms[i] != nullptr; ++i) {
            rooms[i]->displayDetails();
        }
    }

    void bookRoom(int roomNumber) {
        for (int i = 0; i < 100 && rooms[i] != nullptr; ++i) {
            if (rooms[i]->roomNumber == roomNumber) {
                rooms[i]->bookRoom();
                return;
            }
        }
        cout << "Invalid room number. Room not found.\n";
    }
};

int main() {
    // Create an instance of the Hotel class
    Hotel myHotel(5, 5, 5);

    // Display the available rooms
    myHotel.displayRooms();

    // Take user input for booking a room
    int roomToBook;
    cout << "Enter the room number you want to book: ";
    cin >> roomToBook;

    // Book a room
    myHotel.bookRoom(roomToBook);

    // Display the updated status of rooms
    myHotel.displayRooms();

    return 0;
}