/*
Best attempt at replacing raw pointers in ksw_demo2a_raw_ptrs.cpp with shared_ptr
(c3_memory_management/L5_smart_memory_management/ksw_demo2a_raw_ptrs.cpp)

Notice:
- Notice that custom destructor, custom copy constructor, custom copy assignement oeprator, 
custom move constructors and custom move-assignment-operators have all been replaced with default ones
This is perhaps truly a RULE OF ZERO ???
- because of the shared_ptr, the default copy and copy assignment are not deep copies
    Because of the shared pointer, this creates a shallow, shared-ownership copy:
                c1.engine_ptr1 ──┐
                                ├──> same Engine
                c2.engine_ptr1 ──┘
        

 Note: since a lot of defaults have been used, prints are not possible inside those. 
 So we test by 
 i) print the address of the pointers/objects 
 ii) check the reference count
 iii) use static_assert
        static_assert verifies a condition during compilation:
        static_assert(condition);
        - If the condition is true, compilation continues.
        - If it is false, compilation fails.
        - It does not execute at runtime or print anything.

        You can add explanatory messages:-
        static_assert(
            std::is_copy_constructible_v<Car>,
            "Car must be copy constructible"
        );

| Expression                  | `Car` operation  | Effect on each `shared_ptr`                |
| --------------------------- | ---------------- | ------------------------------------------ |
| `Car c4(c1);`               | Copy constructor | Shares engines; reference counts increase  |
| `c5 = c1;`                  | Copy assignment  | Shares engines; reference counts increase  |
| `Car c6(std::move(c2));`    | Move constructor | Ownership handles move; `c2` becomes empty |
| `c4 = std::move(c3);`       | Move assignment  | Handles move; `c3` becomes empty           |
| `c4 = Car("v8", "inline");` | Move assignment  | Handles move from the temporary            |


*/

# include<iostream>
# include<memory> //shared_ptr, make_shared
# include<string>
# include<utility> 
using namespace std;

class Engine {
    private: 
        string name;
    public:
        Engine(){}
        Engine(string name): name(name){ }
        ~Engine(){ }
        void start(){
            cout<<"\n Engine-Starting : name:"<<name<<endl;
        }
        string getname(){ return name;}
};

class Car {
    private:
        shared_ptr<Engine> engine_ptr1; 
        shared_ptr<Engine> engine_ptr2; 
    
    public:
        // Default Constructor
        Car() : engine_ptr1(make_shared<Engine>()) , 
                engine_ptr2(make_shared<Engine>()){
            cout<<"\n Car-Default Constructor : car with 2 engines "<< endl;
            cout<<"Engine 1 name: "<<engine_ptr1->getname();
            cout<<", Engine 2 name: "<<engine_ptr2->getname()<<endl;
        }

        // Parameterized Constructor1 
        Car(string engine1_name) : engine_ptr1(make_shared<Engine>(engine1_name)) , 
                                   engine_ptr2(make_shared<Engine>()){
            cout<<"\n Car-Parameterized Constructor1 : car with 2 engines "<< endl;
            cout<<"Engine 1 name: "<<engine_ptr1->getname();
            cout<<", Engine 2 name: "<<engine_ptr2->getname()<<endl;
        }

        // Parameterized Constructor2
        Car(string engine1_name, string engine2_name) : engine_ptr1(make_shared<Engine>(engine1_name)) , 
                                                        engine_ptr2(make_shared<Engine>(engine2_name)){
            cout<<"\n Car-Parameterized Constructor2 : car with 2 engines "<< endl;
            cout<<"Engine 1 name: "<<engine_ptr1->getname();
            cout<<", Engine 2 name: "<<engine_ptr2->getname()<<endl;
        }
        
        /*
        * Rule of Zero:
        *
        * No explicitly declared:
        *   - destructor
        *   - copy constructor
        *   - copy-assignment operator
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
        const std::shared_ptr<Engine>& engine_ptr)
    {
        std::cout << "  " << pointer_name << '\n'
                  << "    address   : " << engine_ptr.get() << '\n'
                  << "    use_count: " << engine_ptr.use_count() << '\n';

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
    // Verify at compile time that all four operations exist.
    /* These are compile-time checks that ask the compiler whether Car supports copying and moving:
    */
    static_assert(std::is_copy_constructible_v<Car>);
    static_assert(std::is_copy_assignable_v<Car>);
    static_assert(std::is_move_constructible_v<Car>);
    static_assert(std::is_move_assignable_v<Car>);

    static_assert(std::is_nothrow_move_constructible_v<Car>);
    static_assert(std::is_nothrow_move_assignable_v<Car>);

    std::cout
        << "\n\n========== 1. Default construction ==========\n";

    Car c1;
    c1.print_state("c1");


    std::cout
        << "\n\n========== 2. Parameterized construction ==========\n";

    Car c2("v8");
    Car c3("inline");


    std::cout
        << "\n\n========== 3. Copy construction ==========\n";

    std::cout << "\nBefore: Car c4(c1)\n";
    c1.print_state("c1");

    Car c4(c1);  // Implicit copy constructor

    std::cout << "\nAfter: Car c4(c1)\n";
    c1.print_state("c1");
    c4.print_state("c4");

    /*
     * Expected:
     * - c1 and c4 have the same Engine addresses.
     * - Their use_count values are 2.
     */


    std::cout
        << "\n\n========== 4. Copy assignment ==========\n";

    Car c5;

    std::cout << "\nBefore: c5 = c1\n";
    c1.print_state("c1");
    c5.print_state("c5");

    c5 = c1;  // Implicit copy-assignment operator

    std::cout << "\nAfter: c5 = c1\n";
    c1.print_state("c1");
    c4.print_state("c4");
    c5.print_state("c5");

    /*
     * Expected:
     * - c1, c4 and c5 have the same Engine addresses.
     * - Their use_count values are 3.
     * - c5's original engines are destroyed during assignment.
     */


    std::cout
        << "\n\n========== 5. Move construction ==========\n";

    std::cout << "\nBefore: Car c6(std::move(c2))\n";
    c2.print_state("c2");

    Car c6(std::move(c2));  // Implicit move constructor

    std::cout << "\nAfter: Car c6(std::move(c2))\n";
    c2.print_state("c2 - moved from");
    c6.print_state("c6");

    /*
     * Expected:
     * - c6 receives c2's original Engine addresses.
     * - c2's shared_ptr members become empty.
     * - The use_count remains 1 because ownership was transferred,
     *   not copied.
     */


    std::cout
        << "\n\n========== 6. Move assignment ==========\n";

    std::cout << "\nBefore: c4 = std::move(c3)\n";
    c1.print_state("c1");
    c3.print_state("c3");
    c4.print_state("c4");

    c4 = std::move(c3);  // Implicit move-assignment operator

    std::cout << "\nAfter: c4 = std::move(c3)\n";
    c1.print_state("c1");
    c3.print_state("c3 - moved from");
    c4.print_state("c4");

    /*
     * Expected:
     * - c4 releases its shared ownership of c1's engines.
     * - c1 and c5 use_count values decrease from 3 to 2.
     * - c4 receives c3's original Engine addresses.
     * - c3 becomes empty.
     */


    std::cout
        << "\n\n========== 7. Move assignment from temporary ==========\n";

    std::cout << "\nBefore: c4 = Car(\"v8\", \"inline\")\n";
    c4.print_state("c4");

    c4 = Car("v8", "inline");

    std::cout << "\nAfter: c4 = Car(\"v8\", \"inline\")\n";
    c4.print_state("c4");

    /*
     * A temporary Car is constructed and move-assigned into c4.
     * The temporary is then destroyed.
     */


    std::cout
        << "\n\n========== 8. Moved-from objects are valid ==========\n";

    c2.start();
    c3.start();

    /*
     * c2 and c3 are valid but empty.
     * Their start() methods do nothing because of the null checks.
     */


    std::cout
        << "\n\n================ THE END ================\n";
}