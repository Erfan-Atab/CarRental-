#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h> // For _getch()
#include <limits>  // For numeric_limits

using namespace std;

struct Customer 
{
    int customerId;
    int customerPass;
    int rentedCarId;
    int licenceId;
    string customerName;
};

class Car 
{
protected:
    int carId;
    int year;
    int rate;
    string nameOfCar;
    string isAvailable;

public:
    Car() : carId(0), year(0), rate(0), nameOfCar(""), isAvailable("No") {}
    Car(int id, int yr, int rt, const string& name, const string& avail)
        : carId(id), year(yr), rate(rt), nameOfCar(name), isAvailable(avail) {}

    void displayInfo() 
    {
        cout << "Car ID: " << carId
             << ", Name: " << nameOfCar
             << ", Year: " << year
             << ", Rate: " << rate
             << ", Available: " << isAvailable
             << endl;
    }

    bool isAvailability() 
    
    {
        return (isAvailable == "Yes" || isAvailable == "yes" || isAvailable == "Y" || isAvailable == "y");
    }
};

// Helper function for masked password input
int getPasswordInput()
{
    int password = 0;
    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (password != 0)
            {
                password /= 10;
                cout << "\b \b"; 
            }
        }
        else if (ch >= '0' && ch <= '9')
        {
            password = password * 10 + (ch - '0');
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

class RegisterSystem 
{
public:
    Customer customer;

    void registerUser() 
    {
        cout << "Please Enter your full name: ";
        cin >> customer.customerName;
        cout << "Please Enter your password: ";
        customer.customerPass = getPasswordInput();

        ofstream info_file("Customer_info", ios::app);
        if (!info_file.is_open()) 
        {
            cout << "Cannot open file!!!" << endl;
            return;
        }
        info_file << customer.customerName << "," << customer.customerPass << endl;
        info_file.close();

        cout << "Your information has been saved successfully" << endl;
    }

    bool login(Customer &customer) 
    {
        string inputName;
        int inputPass;
        cout << "Please Enter your full name: ";
        cin >> inputName;
        cout << "Please Enter your password: ";
        inputPass = getPasswordInput();

        ifstream info_file_in("Customer_info");
        if (!info_file_in.is_open()) 
        {
            cout << "Cannot open file!!!" << endl;
            return false;
        }

        string line;
        while (getline(info_file_in, line)) 
        {
            size_t pos = line.find(',');
            if (pos == string::npos)  // string::npos means not found
                continue;
            string fileName = line.substr(0, pos);
            int filePassword = stoi(line.substr(pos + 1)); // str becomes int by using stoi
            if (filePassword == inputPass && fileName == inputName) 
            {
                customer.customerName = fileName;
                customer.customerPass = filePassword;
                cout << "Welcome, " << fileName << endl;
                info_file_in.close();
                return true;
            }
        }
        info_file_in.close();
        cout << "Login failed. Incorrect name or password." << endl;
        return false;
    }

    void displayInfo() 
    {
        cout << "Name: " << customer.customerName << endl;
        cout << "Password: " << customer.customerPass << endl;
    }
};

class Bill 
{
public:
    float calculateBill(int carRate, int rentDate, int returnDate) 
    {
        return rentDate * carRate;
    }
};

class RentalSystem : private Car 
{
private:
    void addCar()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer
        cout << "Enter the brand and model of the car: ";
        getline(cin, nameOfCar);  // Use getline to handle spaces in car name
        
        cout << "Enter the year car was built in: ";
        cin >> year;
        
        cout << "Enter the car ID: ";
        cin >> carId;
        
        cout << "Enter the car rate: ";
        cin >> rate;
        
        cout << "Enter whether it is available (Yes/No): ";
        cin >> isAvailable;

        ofstream carinfo_file("car_list", ios::app);
        if (!carinfo_file.is_open()) {
            cout << "Cannot open file!!!" << endl;
            return;
        }
        carinfo_file << nameOfCar << "," << year << "," << carId << "," << rate << "," << isAvailable << endl;
        carinfo_file.close();
        cout << "Car added successfully." << endl;
    }

    void removeCar() 
    {
        int inputCarId;
        cout << "Enter the car ID to remove: ";
        cin >> inputCarId;

        ifstream carinfo_file_in("car_list");
        if (!carinfo_file_in.is_open()) 
        {
            cout << "Cannot open file!!!" << endl;
            return;
        }
        ofstream temp_file("temp_car_list");
        string line;
        bool found = false;
        while (getline(carinfo_file_in, line)) 
        {
            istringstream iss(line);
            vector<string> tokens;
            string token;
            while (getline(iss, token, ',')) 
                tokens.push_back(token);
            if (tokens.size() != 5) 
                continue;
            int id = stoi(tokens[2]);
            if (id == inputCarId) 
            {
                found = true;
                continue;
            }
            temp_file << line << endl;
        }
        carinfo_file_in.close();
        temp_file.close();
        remove("car_list");
        rename("temp_car_list", "car_list");
        if (found) 
            cout << "Car removed successfully." << endl;
        else 
            cout << "Car ID not found." << endl;
    }

    void listOfCars() 
    {
        ifstream carinfo_file_in("car_list");
        if (!carinfo_file_in.is_open()) 
        {
            cout << "Cannot open file!!!" << endl;
            return;
        }
        string line;
        while (getline(carinfo_file_in, line)) 
        {
            istringstream iss(line);
            vector<string> tokens;
            string token;
            while (getline(iss, token, ',')) 
                tokens.push_back(token);
            if (tokens.size() != 5) 
                continue;
            nameOfCar = tokens[0];
            year = stoi(tokens[1]);
            carId = stoi(tokens[2]);
            rate = stoi(tokens[3]);
            isAvailable = tokens[4];
            displayInfo();
        }
        carinfo_file_in.close();
    }

    void rentCar() 
    {
        int inputCarId;
        cout << "Enter the car ID to rent: ";
        cin >> inputCarId;

        ifstream carinfo_file_in("car_list");
        if (!carinfo_file_in.is_open()) 
        {
            cout << "Cannot open file!!!" << endl;
            return;
        }
        ofstream temp_file("temp_car_list");
        string line;
        bool found = false;
        while (getline(carinfo_file_in, line)) 
        {
            istringstream iss(line);
            vector<string> tokens;
            string token;
            while (getline(iss, token, ',')) 
                tokens.push_back(token);
            if (tokens.size() != 5) 
                continue;
            int id = stoi(tokens[2]);
            if (id == inputCarId && (tokens[4] == "Yes" || tokens[4] == "yes")) 
            {
                tokens[4] = "No";
                found = true;
            }
            temp_file << tokens[0] << "," << tokens[1] << "," << tokens[2] << "," << tokens[3] << "," << tokens[4] << endl;
        }
        carinfo_file_in.close();
        temp_file.close();
        remove("car_list");
        rename("temp_car_list", "car_list");
        if (found) 
            cout << "Car rented successfully." << endl;
        else 
            cout << "Car not available or ID not found." << endl;
    }

    void returnCar() 
    {
        int inputCarId;
        int rentDate, returnDate;
        cout << "Enter the car ID to return: ";
        cin >> inputCarId;
        cout << "Enter how many days have you had the car: ";
        cin >> rentDate;

        ifstream carinfo_file_in("car_list");
        if (!carinfo_file_in.is_open()) 
        {
            cout << "Cannot open file!!!" << endl;
            return;
        }
        ofstream temp_file("temp_car_list");
        string line;
        bool found = false;
        int carRate = 0;
        while (getline(carinfo_file_in, line)) 
        {
            istringstream iss(line);
            vector<string> tokens;
            string token;
            while (getline(iss, token, ',')) 
                tokens.push_back(token);
            if (tokens.size() != 5) 
                continue;
            int id = stoi(tokens[2]);
            if (id == inputCarId && (tokens[4] == "No" || tokens[4] == "no")) 
            {
                tokens[4] = "Yes";
                found = true;
                carRate = stoi(tokens[3]);
            }
            temp_file << tokens[0] << "," << tokens[1] << "," << tokens[2] << "," << tokens[3] << "," << tokens[4] << endl;
        }
        carinfo_file_in.close();
        temp_file.close();
        remove("car_list");
        rename("temp_car_list", "car_list");
        if (found) 
        {
            Bill bill;

            float total = bill.calculateBill(carRate, rentDate, returnDate);
            cout << "Car returned successfully. Your bill is: " << total << endl;
            string answer;
            cout << "Do you want pay it?(Yes/No)   ";
            cin >> answer;
            if(answer == "Yes" || answer == "yes")
            {
                cout << "Payment successful.Thanks";
            }
            else
            {
                cout << "You robbed me!!!";
            }
        } 
        else 
        {
            cout << "Car ID not found or not rented." << endl;
        }
    }

public:
    void adminMenu() 
    {
        int intake;
        do 
        {
            cout << "\n\t Admin menu \t" << endl
                 << "----------------------------" << endl
                 << "1. Add car" << endl
                 << "2. Remove car" << endl
                 << "3. List cars" << endl
                 << "4. Sign out" << endl;
            cout << "Please choose an option: ";
            cin >> intake;
            switch (intake)
            {
            case 1: 
                addCar(); 
                break;
            case 2: 
                removeCar(); 
                break;
            case 3: 
                listOfCars(); 
                break;
            case 4: 
                cout << "Signing out..." << endl; 
                break;
            default: 
                cout << "Invalid choice!" << endl;
            }
        } while (intake != 4);
    }

    void menu() 
    {
        int choice;
        do 
        {
            cout << "\n\t Rental Car System \t" << endl
                 << "----------------------------" << endl
                 << "1. View cars" << endl
                 << "2. Rent car" << endl
                 << "3. Return car" << endl
                 << "4. Sign out" << endl;
            cout << "Please choose an option: ";
            cin >> choice;
            switch (choice) 
            {
            case 1: 
                listOfCars(); 
                break;
            case 2: 
                rentCar(); 
                break;
            case 3: 
                returnCar(); 
                break;
            case 4: 
                cout << "Signing out..." << endl; 
                break;
            default: 
                cout << "Invalid choice!" << endl;
            }
        } while (choice != 4);
    }
};

int main() 
{
    RegisterSystem regSys;
    RentalSystem rentSys;
    // Ensure admin user exists
    {
        ifstream check("Customer_info");
        bool exists = false;
        if (check.is_open()) 
        {
            string line;
            while (getline(check, line)) 
            {
                if (line.find("admin,1234") == 0) 
                {
                    exists = true;
                    break;
                }
            }
            check.close();
        }
        if (!exists) 
        {
            ofstream info_file("Customer_info", ios::app);
            if (info_file.is_open()) 
            {
                info_file << "admin,1234" << endl;
                info_file.close();
            }
        }
    }

    int option;

    do 
    {
        cout << "\n________NAVIGATION_________" << endl
             << "1. Register " << endl
             << "2. Log in " << endl
             << "3. Admin " << endl
             << "4. Exit " << endl;
        cout << "Choose an option: ";
        cin >> option;
        
        switch (option) 
        {
        case 1:
            regSys.registerUser();
            break;
        case 2:
            if (regSys.login(regSys.customer)) 
            {
                rentSys.menu();
            }
            break;
        case 3:
            {
                cout << "Admin login:" << endl;
                if (regSys.login(regSys.customer)) 
                {
                    rentSys.adminMenu();
                }
            }
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid option!!!" << endl;
        }
    } while (option != 4);

    return 0;
}
