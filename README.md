# 🚗 Car Rental System in C++

A basic yet functional **Car Rental System** built in C++ that allows users to register, log in, rent and return cars. The application includes an admin panel with the ability to manage the fleet.

---

## ✨ Features

### 👤 User Functionality
- **User Registration**: Sign up with name and numeric password.
- **User Login**: Secure login with masked password entry.
- **View Available Cars**: Browse the list of cars and their details.
- **Rent a Car**: Select a car by its ID and mark it as rented.
- **Return a Car**: Return a rented car and view the total bill.
- **Billing System**: Calculates rental cost based on daily rate and number of days rented.

### 🔐 Admin Functionality
- **Login** with preset credentials (`admin`, `1234`).
- **Add New Cars**: Include new vehicles in the system.
- **Remove Cars**: Delete cars using their unique IDs.
- **View Car List**: Display all cars with their availability status.

---

## 🛠️ Technologies Used

- **C++** Standard Library
- **File Handling** (`fstream`) for persistent data storage
- **Password Masking** using `_getch()` from `conio.h`

---

## 📁 Project Structure

| File/Folder       | Description                                      |
|-------------------|--------------------------------------------------|
| `CarRental++.cpp` | Main source file containing the entire program. |
| `Customer_info`   | Auto-generated file storing customer credentials.|
| `car_list`        | Auto-generated file maintaining car inventory.   |

---
