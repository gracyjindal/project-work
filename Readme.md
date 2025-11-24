## **📖 Overview**

This project is a **menu-driven Hotel Booking Management System** implemented in the C programming language.
It allows hotel staff to:

* Create new bookings
* Calculate total bills
* Offer meal add-ons
* Apply discounts
* Track check-in and check-out
* Store all booking records in a local file
* Retrieve saved data when the program restarts

The project demonstrates concepts from **file handling, structures, arrays, functions, conditional logic, loops, and modular design**.

---

## **💡 Features**

### ✔️ **Create Booking**

* Customer name
* Room selection (Standard / Deluxe / Suite)
* Check-in & Check-out date
* Auto-calculated stay duration
* Optional meals per day

### ✔️ **Meals Supported**

* Breakfast
* Lunch
* High Tea
* Dinner

### ✔️ **Billing System**

* Room charges × number of days
* Meal charges × number of days
* Automatic discount for long stays (≥ 5 days)
* Displays final payable amount

### ✔️ **Check-In / Check-Out**

* Mark a customer as “Checked In”
* Prevent checkout before check-in
* Prevent repeated checkout

### ✔️ **View All Bookings**

* List all customers
* Show room type, stay period, and total bill

### ✔️ **Delete Booking**

* Remove a booking
* Automatically shift remaining records

### ✔️ **File Handling**

* Saves data to **bookings.dat**
* Loads old data automatically on start

---

## **🧱 Project Structure (as per college guidelines)**

```
/
|-- src/             → All .c files
|-- include/         → Header files
|-- docs/            → ProjectReport.pdf (mandatory)
|-- assets/          → Optional images/screenshots
|-- README.md        → This file
|-- sample_input.txt → (optional)
```

---

## **🛠️ Technologies Used**

* **C Language**
* **GCC Compiler**
* **File Handling (Binary File I/O)**
* **Struct-based Data Model**

---

## **🚀 How to Compile and Run**

### **Step 1: Compile**

```bash
gcc hotel_m.c -o hotel
```

### **Step 2: Run**

```bash
./hotel
```

---

## **📄 Project Report**

Your complete project documentation is located at:

```
/docs/ProjectReport.pdf
```

It includes:

1. Title Page
2. Abstract
3. Problem Definition
4. System Design
5. Implementation Details
6. Testing & Results
7. Conclusion & Future Work
8. References
9. Appendix (optional)

---

## **📌 Author**

**Gracy**

---


