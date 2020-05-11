#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

#include "module.h"

Module::Module() {
    /*
    constructor
    - Automatically shows the menu. see void show_menu()
    */
    show_menu();
}

void Module::press_any_key_to_continue() {
    /*
    function
    - Versatile function.
    - Use whenever if unexpected error occured or if user want to quit. I used this a lot.
    - system("read") allow us to enter something. 
    */
    std::cout << "Please enter any key to continue... (redirects to the main menu)\n";
    std::system("read");
    show_menu();
}

void Module::show_menu() {
    /*
    - show menu function show the menu. If you want to edit the main menu, please try to edit this.
    - greeting function allow the computer to read the user file if applicable. If not, It'll make
    user.txt. Code allows the user to enter his or her name/school/major.
    - see void greeting() for more info
    */
    greeting();
    string str_answer;
    int answer = 0;
    std::cout << "-1.Exit program" <<endl;
    std::cout << "1.Show my GPA" << endl;
    std::cout << "2.Show transfer paths" << endl;
    std::cout << "3.Edit my courses" << endl;
    std::cout << "4.See required courses" << endl;
    getline(cin,str_answer);
        answer = atoi(str_answer.c_str());// used atoi on purpose(no error occurs.) unvalid choice will be converted to zero(0).
    if (answer == -1) {
        std::cout << "Thank you for using our program!\n";
        exit(0);
    }  else if (answer == 1) {
        Module::show_gpa_and_coursework(); // We don't need to use Module::func_name but I just used it lol
    } else if (answer == 2) {
        Module::show_transfer_path();
    } else if (answer == 3) {
        edit_courses();
    } else if (answer == 4) {
        show_remained_courses();
    } else { 
        // if user inputs false value, the string will be automatically converted to 0(due to atoi()).
        // if we use stoi, the stoi will throw an error. 
        cout << "Please re-select from the options\n" << endl;
        show_menu();
    }
}

void Module::show_transfer_path() { 
    /* If you want to add school, just add line.
    - may need to follow format school_name.open("filename.txt")!
    ex) else if (answer == 3) {
        school_name.open("harvard_eecs.txt")
    }
    - if you add schools, be sure to edit void show_schools(). 
    - I tried to add them here, but I noticed that showing school's name is used in many 
    other functions so I separated it. 
    - When function finishies showing the requirements, it automatically closes the file and
    call press_any_key_to_continue() <-- 
    */
    show_schools(); // shows schools
    fstream school_name(open_school_file());
    show_school_info(school_name);
    school_name.close();
    press_any_key_to_continue();
}

string Module::open_school_file() {
    /*
    return the name of the file that you want to open.
    You may want to use with fstream stream_name(open_school_file());
    */
    string str_choice;
    int choice = 1;
    getline(cin,str_choice);
    choice = atoi(str_choice.c_str());
    if (choice == 0) {
        cout << "Invalid choice! \n";
        open_school_file();
    } else if (choice == 1) {
        return ("./data/berkeley_cs.txt"); // loading berkeley_cs
    } else if (choice == 2) {
        return ("./data/berkeley_eecs.txt"); // loading ucla_cs
    } else if (choice == 3) {
        return ("./data/davis_ce.txt");
    } else if (choice == 4) {
        return ("./data/davis_cs.txt");
    } else if (choice == 5) {
        return ("./data/davis_csae.txt");
    } else if (choice == 6) {
        return ("./data/irvine_ce.txt");
    } else if (choice == 7) {
        return ("./data/irvine_cgs.txt");
    } else if (choice == 8) {
        return ("./data/irvine_cs.txt");
    } else if (choice == 9) {
        return ("./data/irvine_csae.txt");
    } else if (choice == 10) {
        return ("./data/merced_csae.txt");
    } else if (choice == 11) {
        return ("./data/riverside_ce.txt");
    } else if (choice == 12) {
        return ("./data/riverside_cs.txt");
    } else if (choice == 13) {
        return ("./data/riverside_cswba.txt");
    } else if (choice == 14) {
        return ("./data/sandiego_ce.txt");
    } else if (choice == 15) {
        return ("./data/sandiego_cs.txt");
    } else if (choice == 16) {
        return ("./data/santabarbara_ce.txt");
    } else if (choice == 17) {
        return ("./data/santabarbara_cs.txt");
    } else if (choice == 18) {
        return ("./data/santacruz_ce.txt");
    } else if (choice == 19) {
        return ("./data/santacruz_cs.txt");
    } else if (choice == 20) {
        return ("./data/ucla_cs.txt");
    } else if (choice == 21) {
        return ("./data/ucla_csae.txt");
    }  
}

void Module::show_gpa_and_coursework() {
    /*
    Loads user.txt, calculate user's gpa and show them coursework.
    */
    fstream user;
    user.open("./user.txt");
    string name,school,major;

    int total_credits = 0 ;
    int cumulative_points = 0;
    getline(user,name);
    getline(user,school);
    getline(user,major);

    std::cout << "Hello " << name << ". Your dream school is "<< school <<", " << major << endl;
    std::cout << "You have completed:" << endl;
    int index = 1;
    if (user.eof()) {
        cout << "You did not add any courses. Do you want to add now? (Please answer with yes or no)\n";
        string choice;
        getline(cin,choice);
        if (choice == "yes") {
            add_courses();
        } else {
            press_any_key_to_continue();
        }
    } else {
        while(!user.eof()){
        string course_number,course_name,credits,grade;
        int point_one_subject,int_credits;
        getline(user,course_number);
        if (course_number == "") {
            break;
        }
        getline(user,course_name);
        getline(user,credits);
        getline(user,grade);
        std::cout << index << ". " << course_number << " " << course_name << " " << credits << " " << grade << endl; 
        point_one_subject = Module::grade_to_number(grade); // change letter grade to number e.g. A --> 4 B --> 3
        int_credits = stoi(credits.c_str());// string to integer.
        total_credits += int_credits; // add credits to total credits
        cumulative_points += (int_credits * point_one_subject); // credit multiply by the grade. e.g. 4 credits course and got an A,  => 4*4 = 16
        ++index ;// plus index
        }                  
    double gpa ;
    gpa = double(cumulative_points) / total_credits;
    std::cout << "Your GPA is " << setprecision(3) << gpa << endl;
    user.close(); 
    press_any_key_to_continue();
    }
}

int Module::grade_to_number(string letter_grade) {
    // returns integer that corresponds to the given string grade
    /*
    I tried to add P/NP, W, EW, and C/NC, but I noticed that will make our program more complicate.
    If you want to add that, please feel free.
    I guess that'll be very burdensome because you may need to edit other functions as well.
    */
    int number = 0;
    if (letter_grade == "A") {
        number = 4;
    } else if (letter_grade == "B") {
        number = 3;
    } else if (letter_grade == "C") {
        number = 2;    
    } else if (letter_grade == "D") {
        number = 1;
    } else { //F
        number = 0;
    }
    return number;
}

void Module::edit_courses() {
    /*

    */
    string response = "";
    std::cout << "Do you want to add? or delete? (Please answer with add or delete)" << endl;
    getline(cin,response);
    if ( response == "add" ) {
        Module::add_courses();
    } else if ( response == "delete") {
        Module::delete_courses();
    } else {
        std::cout << "It seems that you entered invalid answer. Please select between two\n";
        Module::edit_courses();
    }
}

void Module::add_courses() {
    /*
    - ios:app allows us to write code from the back.

    */
    fstream user;
    user.open("user.txt",ios::app);
    string course_number,course_name,credits,letter_grade,reply;
    std::cout << "What is the course number you want to add? ex) MATH-294\n";
    getline(cin,course_number);
    std::cout << "What is the name of the course? ex)Differential Equations\n";
    getline(cin,course_name);
    std::cout << "How many credits is your course? ex)5\n";
    getline(cin,credits);
    std::cout << "What did you got from the course? ex)A\n";
    getline(cin,letter_grade);

    std::cout << "You are trying to add " << course_number << " " << course_name << ", "
         << credits << " credits" << " and you got " << letter_grade << "\n";
         // expected output: You are trying to add MATH-294 Differential Equations, 5 credits and you got A"
    std::cout << "Is it correct? (You may want to answer with yes or no)\n";
    getline(cin,reply);
    if (reply == "yes") {
        user << "\n" << course_number << "\n" ;
        user << course_name << "\n" ;
        user << credits << "\n" ;
        user << letter_grade ;
        user.close();
        std::cout << "Do you want to add more courses?\n";
        getline(cin,reply);
        if (reply == "yes") {
            add_courses();
        } else {
            press_any_key_to_continue();
        }

    } else if (reply == "no") {
        std::cout << "Okay, do you want to re-enter your data? \n";
        string reply;
        getline(cin,reply);
        if (reply == "yes") {
            std::cout << "Okay. please re-enter the information\n";
            add_courses();
        } else  {
            press_any_key_to_continue();
        }

    } else {
        press_any_key_to_continue();
    }

}

void Module::delete_courses() {
    fstream user;
    user.open("./user.txt");
    string name,school,major;

    getline(user,name);
    getline(user,school);
    getline(user,major);
    vector<string> vec_course_number,vec_course_name,vec_credits,vec_grade;

    int index = 1;
    while(!user.eof()){
        string course_number,course_name,credits,grade;
        getline(user,course_number);
        getline(user,course_name);
        getline(user,credits);
        getline(user,grade);
        if (course_number == "\n" && course_name == "\n" && credits == "\n" &&  grade == "\n") {
            continue; // if the coursework was deleted by the user, it will be changed to newline.
        }
        vec_course_number.push_back(course_number);
        vec_course_name.push_back(course_name);
        vec_credits.push_back(credits);
        vec_grade.push_back(grade);
        std::cout << index << ". " << course_number << " " << course_name << " " << credits << " " << grade << endl;
        ++index;
    }
    string course_to_delete ="";
    int index_course_to_delete = 0;
    cout << "Which course do you want to delete? (Please enter a number)\n";
    getline(cin,course_to_delete);
    index_course_to_delete = atoi(course_to_delete.c_str()) - 1 ;// because index starts from 1 
    if (index_course_to_delete == -1) {
        cout << "Wrong approach!\n";
        // press_any_key_to_continue();
    } else {
        string reply;
        cout << "You chose " << vec_course_number.at(index_course_to_delete) << " to be deleted. Is this correct?";
        getline(cin,reply);
        cout << reply;
            if (reply == "yes") {
                vec_course_number.erase(vec_course_number.begin()+index_course_to_delete);
                vec_course_name.erase(vec_course_name.begin()+index_course_to_delete);
                vec_credits.erase(vec_credits.begin()+index_course_to_delete);
                vec_grade.erase(vec_grade.begin()+index_course_to_delete);
                user.close();
                fstream user;
                user.open("./user.txt",ios::out | ios::trunc); //delete content and re-write it // reset successful

                user << name << "\n";
                user << school << "\n";
                user << major << "\n";


                for (int i = 0; i < vec_course_name.size() ; ++i ) {
                        user << vec_course_number.at(i) << "\n";
                        user << vec_course_name.at(i) << "\n";
                        user << vec_credits.at(i) << "\n";
                        if ( i == vec_course_name.size()-1) { // I don't want newline at the very last element
                            user << vec_grade.at(i);
                        } else {
                            user << vec_grade.at(i) <<"\n";
                        }             
                    }
                cout << "\ndelete successful" << endl;
                user.close();
            } else {
                press_any_key_to_continue();
            }
        }
        press_any_key_to_continue();
    }

void Module::show_remained_courses() {
    vector<vector<string> > schoolinfo(3);
    show_schools();
    fstream school_name(open_school_file());
    schoolinfo = school_info_into_vector(school_name);
    school_name.close();
    show_remained_courses_by_schools(schoolinfo);
}

void Module::show_remained_courses_by_schools(vector<vector<string> > schoolinfo) {
    vector<vector<string> > myinfo(4);
    vector<vector<string> > not_completed_courses(3);
    fstream myinformation("./user.txt");
    myinfo = my_info_into_vector(myinformation);
    myinformation.close();
        for (int i = 0; i < schoolinfo.at(0).size(); ++i) { // see whether user completed this course.
        int founded = 0;
            for (int j = 0 ; j < myinfo.at(0).size(); ++j) {
                if (schoolinfo.at(0).at(i) == myinfo.at(0).at(j)){ // see if my j th course is in the requirement by searching course number
                    founded = 1;
                } 
            }
                if (founded == 0) { // not founded in trascript means I do not completed that course. Therefore I add it in the course.
                    for (int k = 0 ; k < 3 ; ++k) {
                    not_completed_courses.at(k).push_back(schoolinfo.at(k).at(i)); 
                }
            }
        }
        cout << "You should complete those courses to apply the school\n";
        cout << "-------------------------------------------------------------"  << endl;
        for ( int i = 0 ; i < not_completed_courses.at(0).size() ; ++i ) {
            for ( int j = 0 ; j < not_completed_courses.size(); ++j) {
                if ( j != 2) {
                    cout << not_completed_courses.at(j).at(i) << "\n";
                } else {
                    cout << not_completed_courses.at(j).at(i) << " credits" << endl;
                }
            }
            cout << "-------------------------------------------------------------" << endl;
        }
        press_any_key_to_continue();
}

void Module::show_schools() { // change show school
    cout << "Which school and program?" << endl;
    cout << "1.UC Berkeley, Computer Science" << endl;
    cout << "2.UC Berkeley, Electrical Engineering and Computer Science" << endl;
    cout << "3.UC Davis, Computer Engineering" << endl;
    cout << "4.UC Davis, Computer Science" << endl;
    cout << "5.UC Davis, Computer Science and Engineering" << endl;
    cout << "6.UC Irvine, Computer Engineering" << endl;
    cout << "7.UC Irvine, Computer Game Science" << endl;
    cout << "8.UC Irvine, Computer Science" << endl;
    cout << "9.UC Irvine, Computer Science and Engineering" << endl;
    cout << "10.UC Merced, Computer Science and Engineering" << endl;
    cout << "11.UC Riverside, Computer Engineering" << endl;
    cout << "12.UC Riverside, Computer Science" << endl;
    cout << "13.UC Riverside, Computer Science With Business Application" << endl;
    cout << "14.UC San Diego, Computer Engineering" << endl;
    cout << "15.UC San Diego, Computer Science" << endl;
    cout << "16.UC Santa Barbara, Computer Engineering" << endl;
    cout << "17.UC Santa Barbara, Computer Science" << endl;
    cout << "18.UC Santa Cruz, Computer Engineering" << endl;
    cout << "19.UC Santa Cruz, Computer Science" << endl;
    cout << "20.UCLA, Computer Science" << endl;
    cout << "21.UCLA, Computer Science and Engineering" << endl;
}

void Module::show_school_info(fstream &schoolinfo) { // used when we want to "show" the requirement of the school
    string name_school,program;
    getline(schoolinfo,name_school);
    getline(schoolinfo,program);
    cout << name_school << ", "<< program << ", requires students to finish :" << endl;
    while(!schoolinfo.eof()) {
        string course_number,course_name,credits;
        getline(schoolinfo,course_number);
        if(course_number.length() == 0) { // if blank line exits, then exit.
            break;
        }
        getline(schoolinfo,course_name);
        getline(schoolinfo,credits);
        cout << "COURSE NAME: " << course_number << " " << course_name << " | " << credits << " credits" << endl;
    }
}

vector<vector<string> > Module::school_info_into_vector(fstream &schoolinfo) {
        string schoolname, major,temp;
        vector<vector<string> >school_course_info(3); // 0 is for course number, 1 is for course name, 2 is for credit info.

        if(!schoolinfo.is_open()) { // If there's no txt file exits by anyhow, the program exits.
            std::cout << "Unexpected Error. Program exits\n";
            exit(0);
        }

        getline(schoolinfo,schoolname);
        getline(schoolinfo,major);
        while(!schoolinfo.eof()) {
            string course_number,course_name,credits;
            getline(schoolinfo,course_number);
            if(course_number.length() == 0) { // if blank line exits, then exit.
                break;
            }
            getline(schoolinfo,course_name);
            getline(schoolinfo,credits);
            school_course_info.at(0).push_back(course_number);
            school_course_info.at(1).push_back(course_name);
            school_course_info.at(2).push_back(credits);
        }

        schoolinfo.close();
        return school_course_info;
}

vector<vector<string> > Module::my_info_into_vector(fstream &myinfo) {
    vector<vector<string> > my_information(4);
    string name,school,major;
    getline(myinfo,name);
    getline(myinfo,school);
    getline(myinfo,major);

    while(!myinfo.eof()) {
            string course_number,course_name,credits,grades;
            getline(myinfo,course_number);
            if(course_number.length() == 0) { // if blank line exits, then exit.
                break;
            }
            getline(myinfo,course_name);
            getline(myinfo,credits);
            getline(myinfo,grades);
            my_information.at(0).push_back(course_number);
            my_information.at(1).push_back(course_name);
            my_information.at(2).push_back(credits);
            my_information.at(3).push_back(grades);
        }
    return my_information;
}

void Module::not_support() { //I used this for something I will do tmr
    cout << "NOT SUPPORTED YET" << endl;
    press_any_key_to_continue();
}

void Module::successful() { //I used this sometims to debug
    cout << "successful" << endl;
}

string Module::new_user() { // When user.txt file DNE
    ofstream user("user.txt");
    string name,school,major;
    cout << "Hello There!\n";
    cout << "Welcome to transfer tool \n";
    cout << "What's your name?\n--->";
    getline(cin,name);
    cout << "\nwhere do you want to transfer?\n--->";
    getline(cin,school);
    cout << "\nWhat do you want to study there?\n--->";
    getline(cin,major);
    user << name <<"\n" << school << "\n" << major ;
    user.close();
    cout << "Setting completed! ";
    return name;
}

void Module::greeting() {
    string name;
    fstream user;
    user.open("./user.txt");
    getline(user,name);
    if (!user.is_open()) { //"first usage.s"
        name = new_user();
    } 
    user.close();
    cout << "Welcome " << name << "!\n" << endl;
}
