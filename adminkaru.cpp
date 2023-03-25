#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include<windows.h>
using namespace std;

// Define a User class to represent a student, parent, or teacher
class User {
    private:
        string name;
        string id;
        string password;
        string role;

    public:
        // Constructor to initialize a User object
        User(string name, string id, string password, string role) {
            this->name = name;
            this->id = id;
            this->password = password;
            this->role = role;
        }

        // Getter functions to retrieve the user's information
        string getName() {
            return name;
        }

        string getId() {
            return id;
        }

        string getPassword() {
            return password;
        }

        string getRole() {
            return role;
        }
};
void createNews() {
    cout << "Enter the news (type 'done' on a new line to finish):\n";
    string line;
    getline(cin, line); // consume newline character left by previous input
    ofstream newsFile("news.txt", ios::app);
    while (getline(cin, line) && line != "done") {
        newsFile << line << endl;
    }
    cout << "News created successfully!\n";
};
void communication() {
    cout << "\nSelect an option:\n"
         << "1. Send message to admin\n"
         << "2. Send message to students\n"
         << "3. Send message to parents\n"
         << "4. Exit\n";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1: {
            string message;
            cout << "Enter message to send to admin: ";
            cin.ignore();
            getline(cin, message);
            ofstream adminCommFile("admincommunication.txt", ios::app);
            adminCommFile << message << endl;
            adminCommFile.close();
            cout << "Message sent to admin successfully!" << endl;
            break;
        }
        case 2: {
            string message;
            cout << "Enter message to send to students: ";
            cin.ignore();
            getline(cin, message);
            ofstream studentCommFile("studentcommunication.txt", ios::app);
            studentCommFile << message << endl;
            studentCommFile.close();
            cout << "Message sent to students successfully!" << endl;
            break;
        }
        case 3: {
            string message;
            cout << "Enter message to send to parents: ";
            cin.ignore();
            getline(cin, message);
            ofstream parentCommFile("parentcommunication.txt", ios::app);
            parentCommFile << message << endl;
            parentCommFile.close();
            cout << "Message sent to parents successfully!" << endl;
            break;
        }
        case 4:
            exit(0);
        default:
            cout << "Invalid choice. Please select a valid option." << endl;
    }
}

void submitTest() {
    string id, answers;
    cout << "Enter your user ID: ";
    cin >> id;

    // Check if user exists in users.txt
    ifstream userFileIn("users.txt");
    string line, name, file_id, password, role;
    bool found = false;
    while (getline(userFileIn, line)) {
        istringstream iss(line);
        iss >> name >> file_id >> password >> role;
        if (file_id == id) {
            found = true;
            break;
        }
    }
    userFileIn.close();
    if (!found) {
        cout << "User ID not found!" << endl;
        return;
    }

    // Get result from user
    cout << "Enter your result: ";
    getline(cin,answers);

    // Store result in results.txt
    ofstream resultFileOut("results.txt", ios::app);
    resultFileOut << id << " " << answers << endl;
    resultFileOut.close();

    cout << "Result submitted successfully!" << endl;
}
void viewGrade() {
    string id;
    cout << "Enter user ID: ";
    cin >> id;
    ifstream gradeFileIn("grades.txt");
    string line;
    bool found = false;
    while (getline(gradeFileIn, line)) {
        string file_id, grade;
        istringstream iss(line);
        iss >> file_id >> grade;
        if (file_id == id) {
            cout << "Grade for user " << id << ": " << grade << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "User ID not found." << endl;
    }
}
void giveGrade() {
    string id, grade;
    cout << "Enter student ID: ";
    cin >> id;
    cout << "Enter grade: ";
    cin >> grade;

    // Open users file to check if ID exists
    ifstream userFileIn("users.txt");
    string line;
    bool found = false;
    while (getline(userFileIn, line)) {
        string file_id;
        istringstream iss(line);
        iss >> file_id;
        if (file_id == id) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Error: ID not found\n";
        return;
    }

    // Open grade file to update or create record
    ifstream gradeFileIn("grade.txt");
    ofstream gradeFileOut("temp.txt");
    bool gradeFound = false;
    while (getline(gradeFileIn, line)) {
        string file_id;
        istringstream iss(line);
        iss >> file_id;
        if (file_id == id) {
            gradeFound = true;
            gradeFileOut << id << " " << grade << "\n";
        } else {
            gradeFileOut << line << "\n";
        }
    }

    if (!gradeFound) {
        gradeFileOut << id << " " << grade << "\n";
    }

    // Replace original grade file with temp file
    remove("grade.txt");
    rename("temp.txt", "grade.txt");

    cout << "Grade updated for student with ID " << id << "\n";
}
void teacherStudent() {
    ifstream studentCommFile("studentcommunication.txt");
    if (!studentCommFile) {
        cout << "No communication found from students." << endl;
    } else {
        cout << "Student Communication:\n";
        string line;
        while (getline(studentCommFile, line)) {
            cout << line << endl;
        }
    }
}

void teacherAdmin() {
    ifstream adminCommFile("admincommunication.txt");
    if (!adminCommFile) {
        cout << "No communication found from admins." << endl;
    } else {
        cout << "Admin Communication:\n";
        string line;
        while (getline(adminCommFile, line)) {
            cout << line << endl;
        }
    }
}

void parentCommunication() {
    ifstream parentCommFile("parentcommunication.txt");
    if (!parentCommFile) {
        cout << "No communication found from parents." << endl;
    } else {
        cout << "Parent Communication:\n";
        string line;
        while (getline(parentCommFile, line)) {
            cout << line << endl;
        }
    }
}
void writeToTestFile() {
    // Open the file in append mode
    ofstream testFile("test.txt", ios::app);

    if (!testFile) {
        cerr << "Error: Failed to open file." << endl;
        return;
    }

    // Get user input
    string input;
    cout << "Enter text to write to test file (type 'exit' to stop):" << endl;
    getline(cin, input);

    while (input != "exit") {
        // Write the input to the file
        testFile << input << endl;

        // Get the next input from the user
        getline(cin, input);
    }

    // Close the file
    testFile.close();
    cout << "Text has been written to test file." << endl;
}
void mark() {
    string id;
    cout << "Enter user ID to view results: ";
    cin >> id;

    ifstream userFileIn("users.txt");
    string name, file_id, password, role;
    bool found = false;
    while (userFileIn >> name >> file_id >> password >> role) {
        if (file_id == id && role == "student") {
            found = true;
            break;
        }
    }
    userFileIn.close();

    if (!found) {
        cout << "User with ID " << id << " not found or not a student." << endl;
        return;
    }

    ifstream resultsFileIn("results.txt");
    string line;
    while (getline(resultsFileIn, line)) {
        istringstream iss(line);
        string file_id, marks;
        iss >> file_id >> marks;
        if (file_id == id) {
            cout << "User ID: " << id << ", Marks: " << marks << endl;
            break;
        }
    }
    resultsFileIn.close();
}

void viewNews() {
    ifstream newsFile("news.txt");
    if (!newsFile.is_open()) {
        cout << "Error: news file not found." << endl;
        return;
    }
    string line;
    while (getline(newsFile, line)) {
        cout << line << endl;
    }
    newsFile.close();
}

void parentTeacherComm() {
    string id;
    cout << "Enter student ID: ";
    cin >> id;
    
    ifstream inFile("parentteacher.txt");
    ofstream outFile("temp.txt");
    string line;
    bool found = false;
    
    while (getline(inFile, line)) {
        string file_id;
        istringstream iss(line);
        iss >> file_id;
        if (file_id == id) {
            found = true;
            cout << "Previous communication:\n" << line.substr(id.length() + 1) << endl;
            cout << "Enter new communication:\n";
            string new_communication;
            getline(cin, new_communication);
            outFile << id << " " << new_communication << endl;
        } else {
            outFile << line << endl;
        }
    }
    
    if (!found) {
        cout << "No communication found for student ID " << id << endl;
        cout << "Enter new communication:\n";
        string new_communication;
        getline(cin, new_communication);
        outFile << id << " " << new_communication << endl;
    }
    
    inFile.close();
    outFile.close();
    remove("parentteacher.txt");
    rename("temp.txt", "parentteacher.txt");
}
void viewAssignment() {
    ifstream infile("test.txt");
    if (!infile) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        cout << line << endl;
    }

    infile.close();
}

// Define a function to display a user's profile
void seeUserProfile(string id) {
    cout << "Enter user ID to view profile: ";
    cin >> id;
    ifstream userFile("users.txt");
    string line;
    bool found = false;
    while (getline(userFile, line)) {
        string name, file_id, password, role;
        istringstream iss(line);
        iss >> name >> file_id >> password >> role;
        if (file_id == id) {
            found = true;
            cout << "Name: " << name << endl;
            cout << "ID: " << file_id << endl;
            cout << "Password: " << password << endl;
            cout << "Role: " << role << endl;
            break;
        }
    }
    if (!found) {
        cout << "User ID not found." << endl;
    }
}
void deleteNews() {
    string lineToDelete;
    cout << "Enter the line number to delete: ";
    getline(cin, lineToDelete);

    ifstream newsFileIn("news.txt");
    ofstream tempFileOut("temp.txt");

    int lineNumber = 0;
    string line;
    bool found = false;
    while (getline(newsFileIn, line)) {
        lineNumber++;
        if (lineNumber == stoi(lineToDelete)) {
            found = true;
            continue;
        }
        tempFileOut << line << endl;
    }
    newsFileIn.close();
    tempFileOut.close();

    if (found) {
        remove("news.txt");
        rename("temp.txt", "news.txt");
        cout << "Line " << lineToDelete << " deleted successfully" << endl;
    } else {
        remove("temp.txt");
        cout << "Line not found" << endl;
    }
}

// Define a function to create a new user
void createNewUser() {
    string name, id, password, role;
    cout << "Enter user name: ";
    cin >> name;
    cout << "Enter user ID: ";
    cin >> id;
    cout << "Enter user password: ";
    cin >> password;
    cout << "Enter user role (student/teacher/parent): ";
    cin >> role;

    // Create a new User object
    User newUser(name, id, password, role);

    // Open the user data file in append mode and store the new user's information
    ofstream userFile("users.txt", ios::app);
    userFile << newUser.getName() << " " << newUser.getId() << " " << newUser.getPassword() << " " << newUser.getRole() << endl;
    userFile.close();

    cout << "New user created successfully!" << endl;
}


// Define a function to check if the login credentials are valid
bool checkLogin(string id, string password, string role) {
    ifstream userFile("users.txt");
    string line;
    while (getline(userFile, line)) {
        string name, file_id, file_password, file_role;
        istringstream iss(line);
        iss >> name >> file_id >> file_password >> file_role;
        if (file_id == id && file_password == password && file_role == role) {
            return true;
        }
    }
    return false;
}

// Define a function for the Admin to login to the system
void adminLogin() {
    string username, password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;
    if (username == "admin" && password == "123") {
        // Admin is authenticated, allow access to the system
        bool exit = false;
        while (!exit) {
            // Display options for the Admin to choose from
            cout << "\nSelect an option:\n"
                 << "1. Create new user\n"
                 << "2. Delete user record\n"
                 << "3. View user records\n"
                  <<"4. Create News\n"
                <<"5. view Karu News\n"
                "6. delete Karu News\n"
                <<"7.communication from teacher\n"
                 << "8. Exit\n";
            int choice;
            cin >> choice;
            switch (choice) {
                case 1:
                    createNewUser();
                    break;
                
                	case 2: {
                		string name,role;
    string id;
    cout << "Enter user ID to delete: ";
    cin >> id;
    ifstream userFileIn("users.txt");
    ofstream userFileOut("temp.txt");
    string line;
    bool found = false;
    while (getline(userFileIn, line)) {
        string file_id;
        istringstream iss(line);
        iss >> name >> file_id >> password >> role;
        if (file_id != id) {
            userFileOut << line << endl;
        } else {
            found = true;
        }
    }
    userFileIn.close();
    userFileOut.close();
    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        cout << "User record deleted successfully!" << endl;
    } else {
        remove("temp.txt");
        cout << "User not found." << endl;
    }
    break;
}
 
 case 3: {
    string id;
    cout << "Enter user ID to view profile: ";
    cin >> id;
    seeUserProfile(id);
    break;
}
case 4:
	createNews();
	break;
	case 5:
		viewNews() ;
		break;
		case 6:
			deleteNews();
			break;
case 7:
	 teacherAdmin();
	 break;
                default:
                    cout << "Invalid option selected. Please try again." << endl;
                    break;
            }
        }
    } else {
        cout << "Invalid username or password. Access denied." << endl;
    }
}
 
 
void studentLogin() {
    string id, password;
    cout << "Enter your ID: ";
    cin >> id;
    cout << "Enter your password: ";
    cin >> password;

    ifstream userFileIn("users.txt");
    string line,name;
    bool found = false;
    while (getline(userFileIn, line)) {
        string file_id, file_password, role;
        istringstream iss(line);
        iss >> name >> file_id >> file_password >> role;
        if (file_id == id && file_password == password && role == "student") {
            found = true;
            break;
        }
    }
    if (found) {
    	int option;
        cout << "Login successful!" << endl;
        // Continue with student actions
         cout << "\nSelect an option:\n"
                 << "1. view assignment\n"
                 << "2.  view your record\n"
                 << "3. submit assignment\n"
                  <<"4. view grade\n"
                <<"5. view Karu News\n"
     <<"6. communications from teachers\n";
                 cin>>option;
                 switch(option){
                 	case 1:
                 	viewAssignment();
                 	break;
                 	case 2:
                 		  seeUserProfile(id);
                 		break;
                 		case 3:
                 			submitTest() ;
                 			break;
                 			case 4:
                 				viewGrade();
                 				break;
                 				case 5:
                 						viewNews();
                 						break;
                 						case 6:
                 						teacherStudent() ;
                 						break;
                default:
                    cout << "Invalid option selected. Please try again." << endl;
                    break;
                 							
                 					
                 		
                 	
				 }
    } else {
        cout << "Invalid ID or password!" << endl;
    }
}
void teacherLogin() {
    string id, password;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter password: ";
    cin >> password;

    ifstream usersFile("users.txt");
    string line;
    bool found = false;
    while (getline(usersFile, line)) {
        istringstream iss(line);
        string file_username, file_password, role;
        iss >> file_username >> file_password >> role;
        if (id== id && password == file_password) {
            cout << "Login successful as a teacher!" << endl;
            found = true;
            cout<<"WELCOME TEACHER\nchoose an option from below:\n";
            cout<<"1.communicate\n2.give test\n3.mark assignment\n4.give grade\n5.view niews\n6.exit";
            int option;
            cin>>option;
            switch(option){
            	case 1:
            		communication();
            		break;
            		case 2:
            		 writeToTestFile();
            			break;
            			case 3:
            				mark();
            				break;
            				case 4:
            					giveGrade() ;
            					break;
            					case 5:
            							viewNews() ;
            							break;
            							case 6:
            								exit(1);
            								break;
            						
			}
        }
    }
    if (!found) {
        cout << "Invalid login credentials or user not authorized." << endl;
    }
}
void parent() {
    string id, password, name, role;
    bool found = false;

    cout << "Enter student ID: ";
    cin >> id;

    ifstream userFileIn("users.txt");
    while (userFileIn >> name >> password >> role) {
        if (name == id && role == "student") {
            found = true;
            break;
        }
    }
    userFileIn.close();

    if (found) {
        cout << "Login successful. Welcome parent of student " << id << "!" << endl;
        cout<<"what ids your agend for today pick an option\n"<<endl;
        cout<<"1.view student grade\n2.communicate with the teacher\n3.get teacher communications\n";
        int option;
        cin>>option;
        switch(option){
        	case 1:
        			viewGrade();
        			break;
        			case 2:
        				parentTeacherComm();
        				break;
        				case 3:
        					parentCommunication();
        					break;
        					
        	
		}
    } else {
        cout << "Invalid student ID. Please try again." << endl;
        // Handle error or allow user to try again
    }
}
		    		int main(){
	SetConsoleTitle("KARU MANAGEMENT SYSTEM||BY ENGINEER EDU");
	system("color 1f");
		cout<<"WELCOME TO KARU MANAGEMENT SYSTEM\n PICK YOUR CATEGORY\n";
	cout<<"1.Admin\n2.Teacher\n3.Student\n4.Parent\n";
int category;
cin>>category;
switch(category){
	case 1:
		adminLogin() ;
		break;
		case 2:
			teacherLogin();
			break;
		case 3:
		studentLogin();	
		break;	
		case 4:
			parent();
			break;
			case 5:
				exit(1);
				default:
					cout<<"invalid choice";
	
}

    return 0;
}
