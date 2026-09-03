/*
This code demos that shared pointers could create circular references.

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
        shared_ptr<Student> buddy;
        Student(string name): name(name){};
        Student(string name, shared_ptr<Student> buddy): name(name), buddy(buddy){};
        void set_name(string name) {this->name = name;};
        void set_buddy(shared_ptr<Student> buddy) {this->buddy = buddy;};
};
    

int main(){
  shared_ptr<Student> s1 = make_shared<Student>("RoadRunner");
  shared_ptr<Student> s2 = make_shared<Student>("Coyote");
  s1->set_buddy(s2);
  s2->set_buddy(s1);
  cout<<"s1.use_count() ="<<s1.use_count()<<"\n";
  cout<<"s2.use_count() ="<<s2.use_count()<<"\n";
 
  s1.reset();
  cout<<"After s1 reset"<<"\n";
  cout<<"s1.use_count() ="<<s1.use_count()<<"\n";
  cout<<"s2.use_count() ="<<s2.use_count()<<"\n";

  s2.reset();
  cout<<"After s1 reset"<<"\n";
  cout<<"s1.use_count() ="<<s1.use_count()<<"\n";
  cout<<"s2.use_count() ="<<s2.use_count()<<"\n";
}