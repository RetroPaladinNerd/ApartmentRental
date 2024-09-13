#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

// Class Apartment
class Apartment {
private:
    string address;
    int rooms;
    double rent;
    bool isAvailable = true;  // In-class initializer for isAvailable

public:
    // Constructor using string_view
    Apartment(string_view address, int rooms, double rent)
        : address(address), rooms(rooms), rent(rent) {}

    // Function to show apartment info
    void showInfo() const {
        cout << "Address: " << address << endl;
        cout << "Rooms: " << rooms << endl;
        cout << "Rent: " << rent << endl;
        cout << "Availability: " << (isAvailable ? "Available" : "Rented") << endl;
    }

    // Getters and setters for CRUD operations
    string getAddress() const { return address; }
    void setAddress(string_view newAddress) { address = newAddress; }

    int getRooms() const { return rooms; }
    void setRooms(int newRooms) { rooms = newRooms; }

    double getRent() const { return rent; }
    void setRent(double newRent) { rent = newRent; }

    bool getAvailability() const { return isAvailable; }

    // Rent the apartment
    void rentApartment() {
        if (isAvailable) {
            isAvailable = false;
            cout << "Apartment at " << address << " has been rented." << endl;
        }
        else {
            cout << "Apartment at " << address << " is already rented." << endl;
        }
    }

    // Free the apartment
    void freeApartment() {
        isAvailable = true;
        cout << "Apartment at " << address << " is now available for rent." << endl;
    }
};

// Class Tenant
class Tenant {
private:
    string name;
    string phoneNumber;

public:
    // Constructor using string_view
    Tenant(string_view name, string_view phoneNumber)
        : name(name), phoneNumber(phoneNumber) {}

    // Function to show tenant info
    void showInfo() const {
        cout << "Tenant Name: " << name << endl;
        cout << "Phone: " << phoneNumber << endl;
    }

    // Getters and setters for CRUD operations
    string getName() const { return name; }
    void setName(string_view newName) { name = newName; }

    string getPhoneNumber() const { return phoneNumber; }
    void setPhoneNumber(string_view newPhoneNumber) { phoneNumber = newPhoneNumber; }
};

// Class RentalSystem
class RentalSystem {
private:
    vector<Apartment> apartments;
    vector<Tenant> tenants;

public:
    // Create: Add a new apartment
    void addApartment() {
        string address;
        int rooms;
        double rent;
        cout << "Enter apartment address: ";
        cin.ignore(); // To clear input buffer
        getline(cin, address);
        cout << "Enter number of rooms: ";
        cin >> rooms;
        cout << "Enter rent price: ";
        cin >> rent;

        apartments.push_back(Apartment(address, rooms, rent));
        cout << "Apartment added successfully.\n";
    }

    // Create: Add a new tenant
    void addTenant() {
        string name, phoneNumber;
        cout << "Enter tenant name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter tenant phone number: ";
        getline(cin, phoneNumber);

        tenants.push_back(Tenant(name, phoneNumber));
        cout << "Tenant added successfully.\n";
    }

    // Read: Show all apartments
    void showAllApartments() const {
        if (apartments.empty()) {
            cout << "No apartments available.\n";
            return;
        }
        for (const auto& apartment : apartments) {
            apartment.showInfo();
            cout << "------------------------" << endl;
        }
    }

    // Read: Show all tenants
    void showAllTenants() const {
        if (tenants.empty()) {
            cout << "No tenants available.\n";
            return;
        }
        for (const auto& tenant : tenants) {
            tenant.showInfo();
            cout << "------------------------" << endl;
        }
    }

    // Update: Update apartment information
    void updateApartment() {
        int index;
        cout << "Enter apartment index to update: ";
        cin >> index;
        if (index >= 0 && index < apartments.size()) {
            string newAddress;
            int newRooms;
            double newRent;

            cout << "Enter new address: ";
            cin.ignore();
            getline(cin, newAddress);
            cout << "Enter new number of rooms: ";
            cin >> newRooms;
            cout << "Enter new rent price: ";
            cin >> newRent;

            apartments[index].setAddress(newAddress);
            apartments[index].setRooms(newRooms);
            apartments[index].setRent(newRent);
            cout << "Apartment updated successfully.\n";
        }
        else {
            cout << "Invalid apartment index.\n";
        }
    }

    // Update: Update tenant information
    void updateTenant() {
        int index;
        cout << "Enter tenant index to update: ";
        cin >> index;
        if (index >= 0 && index < tenants.size()) {
            string newName, newPhoneNumber;

            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, newName);
            cout << "Enter new phone number: ";
            getline(cin, newPhoneNumber);

            tenants[index].setName(newName);
            tenants[index].setPhoneNumber(newPhoneNumber);
            cout << "Tenant updated successfully.\n";
        }
        else {
            cout << "Invalid tenant index.\n";
        }
    }

    // Delete: Remove an apartment
    void deleteApartment() {
        int index;
        cout << "Enter apartment index to delete: ";
        cin >> index;
        if (index >= 0 && index < apartments.size()) {
            apartments.erase(apartments.begin() + index);
            cout << "Apartment removed successfully.\n";
        }
        else {
            cout << "Invalid apartment index.\n";
        }
    }

    // Delete: Remove a tenant
    void deleteTenant() {
        int index;
        cout << "Enter tenant index to delete: ";
        cin >> index;
        if (index >= 0 && index < tenants.size()) {
            tenants.erase(tenants.begin() + index);
            cout << "Tenant removed successfully.\n";
        }
        else {
            cout << "Invalid tenant index.\n";
        }
    }

    // Rent an apartment
    void rentApartment() {
        int index;
        cout << "Enter apartment index to rent: ";
        cin >> index;
        if (index >= 0 && index < apartments.size()) {
            apartments[index].rentApartment();
        }
        else {
            cout << "Invalid apartment index.\n";
        }
    }

    // Free an apartment
    void freeApartment() {
        int index;
        cout << "Enter apartment index to free: ";
        cin >> index;
        if (index >= 0 && index < apartments.size()) {
            apartments[index].freeApartment();
        }
        else {
            cout << "Invalid apartment index.\n";
        }
    }
};

// Function to display the menu
void displayMenu() {
    cout << "\nApartment Rental System Menu:\n";
    cout << "1. Add Apartment\n";
    cout << "2. Add Tenant\n";
    cout << "3. Show All Apartments\n";
    cout << "4. Show All Tenants\n";
    cout << "5. Update Apartment\n";
    cout << "6. Update Tenant\n";
    cout << "7. Delete Apartment\n";
    cout << "8. Delete Tenant\n";
    cout << "9. Rent Apartment\n";
    cout << "10. Free Apartment\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    RentalSystem system;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            system.addApartment();
            break;
        case 2:
            system.addTenant();
            break;
        case 3:
            system.showAllApartments();
            break;
        case 4:
            system.showAllTenants();
            break;
        case 5:
            system.updateApartment();
            break;
        case 6:
            system.updateTenant();
            break;
        case 7:
            system.deleteApartment();
            break;
        case 8:
            system.deleteTenant();
            break;
        case 9:
            system.rentApartment();
            break;
        case 10:
            system.freeApartment();
            break;
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
