/*
Best attempt at replacing raw pointers in ksw_demo2a_raw_ptrs.cpp with unique_ptr
(c3_memory_management/L5_smart_memory_management/ksw_demo2a_raw_ptrs.cpp)

Notice:
- Notice that custom move constructors and custom move-assignment-operators have been replaced with default ones
- The destructor is default as well
- i elminated the custom copy constructor and custom-copy-assignment operator. Which means because of the 
unique_ptr, copying is not possible

 Note: since a lot of defaults have been used, prints are not possible inside those. 
 Test by 
 i) printing the address of the pointers
 ii) use static_assert to see if copying, copy-assignment, moving, move-assignments are possible
     (default copying, default copy-assignment is not possible with unique_ptrs, 
     custom ones for deep copy has to be defined)
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
        
        /*
        * Rule of Zero:
        *
        * No explicitly declared:
        *   - destructor
        *   - copy constructor : Because of the unique_ptr, there will be no default copy constructor either
        *   - copy-assignment operator: : Because of the unique_ptr, there will be no default copy-assignment operator either
        *   - move constructor
        *   - move-assignment operator
        *
        * The compiler generates all five operations.
        */

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
    /* // These two static asserts involving copying cannot be used in this case 
    due to unique_ptr
    static_assert(std::is_copy_constructible_v<Car>);
    static_assert(std::is_copy_assignable_v<Car>);
    */
    static_assert(std::is_move_constructible_v<Car>);
    static_assert(std::is_move_assignable_v<Car>);

    std::cout
        << "\n\n========== c1: Default constructor ==========\n";

    Car c1;
    c1.print_state("c1");


    std::cout
        << "\n\n========== c2, c3, c4: Parameterized constructors ==========\n";

    Car c2("v8");
    Car c3("inline");
    Car c4("v4");

    c2.print_state("c2");
    c3.print_state("c3");
    c4.print_state("c4");


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