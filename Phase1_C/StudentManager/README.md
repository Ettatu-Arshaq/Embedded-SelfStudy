# 📚 Student Record Manager (C + File Handling)

## 📌 Project Overview
A menu-driven C program to **add, view, search, and delete student records** stored in a binary file.  
This is my **Phase 1 mini project** from my Embedded Systems self-study roadmap.

---

## 🛠 Features
- Add new student records
- View all stored student records
- Search student by roll number
- Delete a student record with confirmation
- Data persistence using binary file handling

---

## 📂 Data Structure
```c
typedef struct {
    int roll;
    char name[50];
    float marks;
} std;
```

---

## 💻 Technologies Used
- **Language:** C
- **Concepts:** Structures, File Handling, Loops, Modular Functions
- **File Type:** Binary (`studentdata.bin`)

---

## ▶ How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/Ettatu-Arshaq/StudentManager.git
   ```
2. Navigate to the folder:
   ```bash
   cd StudentManager
   ```
3. Compile the program:
   ```bash
   gcc main.c -o student_manager
   ```
4. Run the program:
   ```bash
   ./student_manager
   ```

---

## 📸 Sample Output
```
=========== STUDENT RECORD MANAGER ===========
1. Add New Student
2. View All Students
3. Search Student by Roll Number
4. Delete Student Record
5. Exit
==============================================
Enter your choice: 1

Enter No of Entries : 2
Enter Entry No 1
RollNo: 101
Name: Arshaq
Marks : 88.5
✅ Successfully Saved Entries
```

---

## 📌 Future Improvements
- Support names with spaces
- Show total number of records
- Improved delete confirmation
- User interface improvements

---

## 🏆 Author
**Muhammad Arshaq**  
📅 **Completed:** July 2025  
Part of **Phase 1 – C Programming** in my Embedded Systems self-study roadmap.
