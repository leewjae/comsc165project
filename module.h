#ifndef MODULE_H
#define MODULE_H

#include <string>

using namespace std;

class Module {
    public:
        Module();
        void show_menu(); // show main menu
        void show_gpa_and_coursework(); // showing unofficial "transcript"
        void show_transfer_path(); // pick school, and see the transfer pathwork
        void edit_courses(); // edit tools, can add or delete courses.
        void add_courses(); // add course
        void delete_courses(); // delete course
        void show_remained_courses();//show remained course.
        int grade_to_number(string); // tools to change grade to number
        void press_any_key_to_continue();
        void show_schools();
        void not_support();
        void successful();
        void greeting();
        void show_school_info(fstream &a);
        void show_remained_courses_by_schools(vector<vector<string> >);
        string new_user();
        vector<vector<string> > school_info_into_vector(fstream &a);
        vector<vector<string> > my_info_into_vector(fstream &a);
    private:
        void show_my_coursework_only();
};
    
#endif