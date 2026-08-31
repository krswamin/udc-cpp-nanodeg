/*
Best attempt at replacing raw pointers in ksw_demo2a_raw_ptrs.cpp with unique_ptr 
(c3_memory_management/L5_smart_memory_management/ksw_demo2a_raw_ptrs.cpp)

Notice:
- Notice that custom move constructors and custom move-assignment-operators have been replaced with default ones
- The destructor is default as well
- If you need a deep copy, a custom constructor, custom copy-assignment operator is needed,
 since by default unique_ptrs are not copyable.

 Note: since a lot of defaults have been used, prints are not possible inside those. 
 Test by 
 i) printing the address of the pointers
 ii) use static_assert to see if copying, copy-assignment, moving, move-assignments are possible
 iii) cannot use reference count: since that is only for shared_ptrs.
 reference_count does not exist for unique_ptrs
*/

# include<iostream>
# include<memory> //unique_ptr, make_unique
# include<string>
# include<utility> // st
using namespace std;

class Engine {
    private: 
        string name;
    public:
        Engine(){
            cout<<"\n Engine-Default Constructor : "<< endl;
        }
        Engine(string name): name(name){ 
            cout<<"\n Engine-Parameterized Constructor : "<< endl;
        }
        ~Engine(){}
        void start(){
            cout<<"\n Engine-Starting : name:"<<name<<endl;
        }
        string getname(){ return name;}
};

class Car {
    private:
        unique_ptr<Engine> engine_ptr1; 
        unique_ptr<Engine> engine_ptr2; 
    
    public:
        // Default Constructor
        Car() : engine_ptr1(make_unique<Engine>()) , 
                engine_ptr2(make_unique<Engine>()){
            cout<<"\n Car-Default Constructor "<< endl;
        }

        // Parameterized Constructor1 
        Car(string engine1_name) : engine_ptr1(make_unique<Engine>(engine1_name)) , 
                                   engine_ptr2(make_unique<Engine>()){
            cout<<"\n Car-Parameterized Constructor1 "<< endl;
        }

        // Parameterized Constructor2
        Car(string engine1_name, string engine2_name) : engine_ptr1(make_unique<Engine>(engine1_name)) , 
                                                        engine_ptr2(make_unique<Engine>(engine2_name)){
            cout<<"\n Car-Parameterized Constructor2 "<< endl;
        }
        
        // Default Destructor
        ~Car() = default;

        // Custom Copy Constructor (deep copy)
        /* C++ cannot automatically decide whether copying a Car should:
        - Copy the pointers
        - Share the engines
        - Create new independent engines
        - Transfer ownership
        - Be prohibited entirely
        In your original program, copying meant creating a deep copy, so you must implement that policy explicitly:
        */
        Car(const Car& other) {
             this->engine_ptr1 = nullptr; 
             if(other.engine_ptr1) {
                this->engine_ptr1 = make_unique<Engine>(*other.engine_ptr1) ;
             }

             this->engine_ptr2 = nullptr; 
             if(other.engine_ptr2) {
                this->engine_ptr2 = make_unique<Engine>(*other.engine_ptr2) ;
             }

            cout<<"\n Car-Copy Constructor : car with 2 engines "<< endl;
            if(engine_ptr1)
                cout<<"Engine 1 name: "<<engine_ptr1->getname() ;
            if(engine_ptr2)
                cout<<", Engine 2 name: "<<engine_ptr2->getname()<<endl;
        }

        // Custom Copy Assignment 
        /* copy-assignment operator deletes the destination’s current engines before finishing the new allocations. 
        If an allocation throws, the destination object is left partially modified.
        The copy-and-swap approach provides stronger exception safety:
        */
        Car& operator=(const Car& other){
            if(this == &other){
                return *this;
            }
            
            this->engine_ptr1 = nullptr;
            if(other.engine_ptr1) {
                this->engine_ptr1 = make_unique<Engine>(*other.engine_ptr1) ;
             }

            this->engine_ptr2 = nullptr;
            if(other.engine_ptr2) {
                this->engine_ptr2 = make_unique<Engine>(*other.engine_ptr2) ;
            }

            cout<<"\n Car-Copy Assignment Operator : car with 2 engines "<< endl;
            if(engine_ptr1)
                cout<<"Engine 1 name: "<<engine_ptr1->getname() ;
            if(engine_ptr2)
                cout<<", Engine 2 name: "<<engine_ptr2->getname()<<endl;

            return *this;

        }

        // Default Move Constructor 
        Car(Car&&) noexcept = default;

        // Default Move Assignment Operator
        Car& operator=(Car&&) noexcept = default;

        // Start both car engines
        void start(){
            cout<<"\n Starting: Car"<<endl;
            if(engine_ptr1)
                engine_ptr1->start();
            if(engine_ptr2)
                engine_ptr2->start();
        }


        void print_state(const std::string& car_name) const
        {
            std::cout << "\nState of " << car_name << '\n';

            print_engine_state("engine_ptr1", engine_ptr1);
            print_engine_state("engine_ptr2", engine_ptr2);
        }


    private:
        static void print_engine_state(
        const std::string& pointer_name,
        const std::unique_ptr<Engine>& engine_ptr)
    {
        std::cout << "  " << pointer_name << '\n'
                  << "    address   : " << engine_ptr.get() << '\n';

        if (engine_ptr) {
            std::cout << "    name     : "
                      << engine_ptr->getname() << '\n';
        } else {
            std::cout << "    name     : <empty>\n";
        }
    }

};


int main()
{
    static_assert(std::is_copy_constructible_v<Car>);
    static_assert(std::is_copy_assignable_v<Car>);
    static_assert(std::is_move_constructible_v<Car>);
    static_assert(std::is_move_assignable_v<Car>);

    std::cout
        << "\n\n========== c1: Default constructor ==========\n";

    Car c1;
    c1.print_state("c1");


    std::cout
        << "\n\n========== c2 and c3: Parameterized constructors ==========\n";

    Car c2("v8");
    Car c3("inline");

    c2.print_state("c2");
    c3.print_state("c3");


    std::cout
        << "\n\n========== c4: Copy constructor ==========\n";

    std::cout << "\nBefore copy construction:\n";
    c1.print_state("c1");

    Car c4(c1);

    std::cout << "\nAfter copy construction:\n";
    c1.print_state("c1");
    c4.print_state("c4");

    /*
     * Expected:
     *
     * c1 and c4 have engines with the same names,
     * but their addresses are different.
     *
     * This proves that a deep copy occurred.
     */


    std::cout
        << "\n\n========== c5: Copy assignment ==========\n";

    Car c5;

    std::cout << "\nBefore copy assignment:\n";
    c1.print_state("c1");
    c5.print_state("c5");

    c5 = c1;

    std::cout << "\nAfter copy assignment:\n";
    c1.print_state("c1");
    c5.print_state("c5");

    /*
     * Expected:
     *
     * c1 and c5 have engines with the same names,
     * but their addresses are different.
     *
     * This proves that a deep-copy assignment occurred.
     */


    std::cout
        << "\n\n========== c6: Move constructor ==========\n";

    std::cout << "\nBefore move construction:\n";
    c2.print_state("c2");

    Car c6(std::move(c2));

    std::cout << "\nAfter move construction:\n";
    c2.print_state("c2 - moved from");
    c6.print_state("c6");

    /*
     * Expected:
     *
     * c6 receives c2's original Engine addresses.
     * c2's addresses become zero/null.
     *
     * This proves that ownership was moved.
     */


    std::cout
        << "\n\n========== c4: Move assignment ==========\n";

    std::cout << "\nBefore move assignment:\n";
    c3.print_state("c3");
    c4.print_state("c4");

    c4 = std::move(c3);

    std::cout << "\nAfter move assignment:\n";
    c3.print_state("c3 - moved from");
    c4.print_state("c4");

    /*
     * Expected:
     *
     * c4 receives c3's original Engine addresses.
     * c3's addresses become zero/null.
     *
     * c4's previously owned Engines are destroyed.
     */


    std::cout
        << "\n\n========== c4: Move assignment from temporary ==========\n";

    c4.print_state("c4 before assignment");

    c4 = Car("v8", "inline");

    c4.print_state("c4 after assignment");

    std::cout
        << "\n\n================ THE END ================\n";
}