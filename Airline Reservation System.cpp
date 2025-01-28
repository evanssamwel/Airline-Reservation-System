#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Struct to store passenger information
struct Passenger {
    string name;
    int age;
    string travelClass;
    string destination;
    string seat;
    double ticketPrice;
};

// Function prototypes
void displayDestinations();
void calculateTicketPrice(Passenger &passenger);
void printBoardingPass(const Passenger &passenger);
void assignSeat(Passenger &passenger, vector<string> &availableSeats);
void displayTotal(const vector<Passenger> &passengers);

// Global constants
const vector<pair<string, double>> destinations = {
    {"Nairobi to Mombasa", 5000.0},
    {"Nairobi to Kisumu", 4000.0},
    {"Nairobi to Eldoret", 3500.0},
    {"Nairobi to Malindi", 4500.0},
    {"Nairobi to Nakuru", 3000.0}
};

const double BUSINESS_CLASS_MULTIPLIER = 1.5;
const double CHILD_DISCOUNT = 0.5;
const int CHILD_AGE_LIMIT = 12;

int main() {
    vector<Passenger> passengers;
    vector<string> availableSeats = {"A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3"};
    char addMore;

    cout << "\nWelcome to the Kenyan Airline Reservation System\n";

    do {
        Passenger passenger;

        // Input passenger details
        cout << "\nEnter passenger name: ";
        getline(cin, passenger.name);

        cout << "Enter passenger age: ";
        cin >> passenger.age;
        cin.ignore(); // Ignore newline character

        // Display destinations
        displayDestinations();

        int destinationChoice;
        cout << "Select a destination (1-" << destinations.size() << "): ";
        cin >> destinationChoice;
        cin.ignore(); // Ignore newline character

        if (destinationChoice < 1 || destinationChoice > destinations.size()) {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        passenger.destination = destinations[destinationChoice - 1].first;

        // Select travel class
        cout << "Select travel class (Economy/Business): ";
        getline(cin, passenger.travelClass);

        // Assign seat
        assignSeat(passenger, availableSeats);

        // Calculate ticket price
        calculateTicketPrice(passenger);

        // Add passenger to the list
        passengers.push_back(passenger);

        cout << "\nPassenger added successfully!\n";
        printBoardingPass(passenger);

        // Ask if more passengers should be added
        cout << "\nAdd another passenger? (Y/N): ";
        cin >> addMore;
        cin.ignore(); // Ignore newline character

    } while (tolower(addMore) == 'y');

    displayTotal(passengers);

    cout << "\nThank you for using the Kenyan Airline Reservation System!\n";

    return 0;
}

void displayDestinations() {
    cout << "\nAvailable Destinations:\n";
    for (size_t i = 0; i < destinations.size(); ++i) {
        cout << i + 1 << ". " << destinations[i].first << " - KES " << destinations[i].second << "\n";
    }
}

void calculateTicketPrice(Passenger &passenger) {
    double basePrice = 0.0;

    // Find the base price for the selected destination
    for (const auto &dest : destinations) {
        if (dest.first == passenger.destination) {
            basePrice = dest.second;
            break;
        }
    }

    // Apply discounts or multipliers
    if (passenger.age <= CHILD_AGE_LIMIT) {
        basePrice *= CHILD_DISCOUNT;
    }

    if (passenger.travelClass == "Business" || passenger.travelClass == "business") {
        basePrice *= BUSINESS_CLASS_MULTIPLIER;
    }

    passenger.ticketPrice = basePrice;
}

void printBoardingPass(const Passenger &passenger) {
    cout << "\n========================================\n";
    cout << "          BOARDING PASS\n";
    cout << "========================================\n";
    cout << "Name: " << passenger.name << "\n";
    cout << "Age: " << passenger.age << "\n";
    cout << "Destination: " << passenger.destination << "\n";
    cout << "Class: " << passenger.travelClass << "\n";
    cout << "Seat: " << passenger.seat << "\n";
    cout << fixed << setprecision(2);
    cout << "Ticket Price: KES " << passenger.ticketPrice << "\n";
    cout << "========================================\n";
}

void assignSeat(Passenger &passenger, vector<string> &availableSeats) {
    if (availableSeats.empty()) {
        cout << "No seats available.\n";
        passenger.seat = "None";
        return;
    }

    passenger.seat = availableSeats.back();
    availableSeats.pop_back();
}

void displayTotal(const vector<Passenger> &passengers) {
    double totalCost = 0.0;

    cout << "\n========================================\n";
    cout << "          TOTAL SUMMARY\n";
    cout << "========================================\n";
    for (const auto &passenger : passengers) {
        totalCost += passenger.ticketPrice;
        cout << "Passenger: " << passenger.name << " - KES " << passenger.ticketPrice << "\n";
    }
    cout << "----------------------------------------\n";
    cout << "Total Cost: KES " << totalCost << "\n";
    cout << "========================================\n";
}