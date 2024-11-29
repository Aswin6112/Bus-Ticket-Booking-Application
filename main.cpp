#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;

// Bus class
class Bus {
protected:
    int Bus_no;
    string Bus_Driver_Name;
    string Route_Name;
    string Departing_Time;
    int Tot_no_of_Seats;
    int Seats_Booked;

public:
    // Constructor
    Bus(int a, string b, string c, string d, int e)
    {
        Bus_no=a;
        Bus_Driver_Name=b;
        Route_Name=c;
        Departing_Time=d;
        Tot_no_of_Seats=e;
        Seats_Booked=0;
    }
    

    // Getter functions
    int getBusNumber() const 
    { 
        return Bus_no; 
    }
    string getRoute() const 
    { 
        return Route_Name; 
    }
    int getAvailableSeats() const 
    { 
        return Tot_no_of_Seats - Seats_Booked; 
    }

    // Function for booking seat
    bool Book_Bus_Seat(int seats = 1) 
    {
        if (Seats_Booked + seats <= Tot_no_of_Seats) 
        {
            Seats_Booked += seats;
            return true;
        }
        return false;
    }

    // Display the Bus Details
    virtual void Display_Info() const 
    {
        cout << setw(10) << Bus_no << setw(20) << Bus_Driver_Name
             << setw(30) << Route_Name << setw(15) << Departing_Time
             << setw(10) << getAvailableSeats() << endl;
    }

    virtual ~Bus() {} 
};

// Passenger class
class Passenger {
private:
    string Passenger_Name;
    int Bus_no;
    int Seats_Booked;

public:
    Passenger(string a, int b, int c)
    {
        Passenger_Name=a;
        Bus_no=b;
        Seats_Booked=c;
    }

    // Function for displaying the tickets detail
    void Display_Ticket_Details() const 
    {
        cout << "Passenger Name: " << Passenger_Name << endl;
        cout << "Bus Number: " << Bus_no << endl;
        cout << "Seats Booked: " << Seats_Booked << endl;
    }
};

//  Class for managing buses and bookings
class BusTicketBooking {
private:
    vector<Bus> Buses;
    vector<Passenger> Passengers;

public:
    // Function for loading the buses
    void Create_Buses() {
        Buses.emplace_back(01, "Rajesh", "Chennai to Trichy", "07:30 AM", 40);
        Buses.emplace_back(02, "Dravid", "Delhi to Mumbai", "09:00 AM", 35);
        Buses.emplace_back(03, "Ganesh", "Salem to Madurai", "01:00 PM", 50);
    }

    // Function to display all buses
    void Display_Bus_Info() const 
    {
        cout << setw(10) << "Bus No" << setw(20) << "Driver Name"
             << setw(30) << "Route" << setw(15) << "Departure Time"
             << setw(10) << "Seats Left" << endl;
        cout << string(85, '-') << endl;
        for (const auto &bus : Buses) {
            bus.Display_Info();
        }
    }

    // Function for booking tickets
    void Book_Ticket() {
        string P_Name;
        int S_Bus, Seats_To_Book;

        Display_Bus_Info();
        cout << "Enter Bus Number: ";
        cin >> S_Bus;

        // Finding the bus
        auto it = find_if(Buses.begin(), Buses.end(),
                          [S_Bus](const Bus &B) {
                              return B.getBusNumber() == S_Bus;
                          });

        if (it != Buses.end()) {
            cout << "Enter Passenger Name: ";
            cin.ignore(); // Clear the newline character
            getline(cin, P_Name);

            cout << "Enter Number of Seats: ";
            cin >> Seats_To_Book;

            if (it->Book_Bus_Seat(Seats_To_Book)) {
                Passengers.emplace_back(P_Name, S_Bus, Seats_To_Book);
                cout << "Ticket successfully booked!\n";
            } else {
                cout << "Not enough seats available.\n";
            }
        } else {
            cout << "Invalid Bus Number.\n";
        }
    }

    // Function for displaying passenger tickets
    void Display_Passenger_Tickets() const {
        if (Passengers.empty()) {
            cout << "No tickets booked yet.\n";
            return;
        }
        for (const auto &passenger : Passengers) {
            passenger.Display_Ticket_Details();
            cout << string(30, '-') << endl;
        }
    }
};

// Main function
int main() {
    BusTicketBooking T;
    T.Create_Buses();

    int choice;
    do {
        cout << "\n--- Bus Ticket Booking System ---\n";
        cout << "1. View Buses\n";
        cout << "2. Book Ticket\n";
        cout << "3. View Tickets\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                T.Display_Bus_Info();
                break;
            case 2:
                T.Book_Ticket();
                break;
            case 3:
                T.Display_Passenger_Tickets();
                break;
            case 4:
                cout << "Exiting application...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
