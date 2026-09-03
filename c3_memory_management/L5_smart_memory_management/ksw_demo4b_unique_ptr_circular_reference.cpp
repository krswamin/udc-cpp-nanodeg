
/*
This code demos that unique pointers cannot create circular references.
Atleast so far it seems impossible to me. 
So the following is IMPOSSIBLE WITH UNIQUE POINTERS
 |-----> Object A           
 |       Shared pointer ----> Object B
 |                            Shared Pointer --->--|
 |                                                 |
 |-----------<-------------<------------<----------|
                    
*/

# include<memory>
# include<iostream>
using namespace std;

class Student {
    public:
        string name;
        unique_ptr<Student> buddy;
        Student(string name): name(name), buddy(nullptr){};
        Student(string name, unique_ptr<Student> buddy): name(name), buddy(move(buddy)){};
        void set_name(string name) {this->name = name;};
        void set_buddy(unique_ptr<Student> buddy) {this->buddy = move(buddy);};
        void print_details(){
            cout<<"\n name        :"<< name<<'\n';
            cout<<" self.address  :"<< this<<'\n';
            if (buddy.get()){
                cout<<" buddy address :"<< buddy.get()<<'\n';
            }
        }
};

void print_s1_s2(const unique_ptr<Student>& s1,
                 const unique_ptr<Student>& s2) {

    cout<<"\n s1 details \n";
    if (s1.get()){
        s1->print_details();
    } else {
        cout <<"s1 is null \n";
    }

    cout<<"\n s2 details \n";
    if (s2.get()){
        s2->print_details();
    } else {
        cout <<"s2 is null \n";
    }
}


int main(){
  unique_ptr<Student> s1 = make_unique<Student>("RoadRunner");
  unique_ptr<Student> s2 = make_unique<Student>("Coyote");

  cout<<"\n\n s1 and s2 : start"<<endl;
  print_s1_s2(s1,s2);
  

  // This will execute
  if (s1.get() && s2.get()) {
    s1->set_buddy(move(s2));
    cout<<"\n\n s1 and s2 after move(s2)"<<endl;
    print_s1_s2(s1,s2);
  } else {
    cout<<" s1->set_buddy(move(s2)); did not execute "<<"\n"
  }
  
  // This will NOT EXECUTE, so there is no circular dependency really
  if (s1.get() && s2.get()) {
    s2->set_buddy(move(s1));
    cout<<"\n\n s1 and s2 after move(s1)"<<endl;
    print_s1_s2(s1,s2);
  } else {

  }
}