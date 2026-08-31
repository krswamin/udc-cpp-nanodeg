# include<iostream>
using namespace std;

class Engine {
    private: 
        string name;
    public:
        Engine(){
            name = "unknown";
            cout<<"\n Engine-Constructor : name:"<<name<<endl;
        }
        Engine(string name): name(name){
            cout<<"\n Engine-Parameterized Constructor : name:"<<name<<endl;
        }
        ~Engine(){
            cout<<"\n Engine-Destructor : name:"<<name<<endl;
        }
        void start(){
            cout<<"\n Engine-Starting : name:"<<name<<endl;
        }
        string getname(){ return name;}
};

class Car {
    private:
        Engine *engine_ptr1; 
        Engine *engine_ptr2; 
    
    public:
        // Default Constructor
        Car() : engine_ptr1(new Engine()) , 
                engine_ptr2(new Engine()){
            cout<<"\n Car-Default Constructor : car with 2 engines "<< endl;
            cout<<"Engine 1 name: "<<engine_ptr1->getname();
            cout<<", Engine 2 name: "<<engine_ptr2->getname()<<endl;
        }

        // Parameterized Constructor1 
        Car(string engine1_name) : engine_ptr1(new Engine(engine1_name)) , 
                                   engine_ptr2(new Engine()){
            cout<<"\n Car-Parameterized Constructor1 : car with 2 engines "<< endl;
            cout<<"Engine 1 name: "<<engine_ptr1->getname();
            cout<<", Engine 2 name: "<<engine_ptr2->getname()<<endl;
        }

        // Parameterized Constructor2
        Car(string engine1_name, string engine2_name) : engine_ptr1(new Engine(engine1_name)) , 
                                                        engine_ptr2(new Engine(engine2_name)){
            cout<<"\n Car-Parameterized Constructor2 : car with 2 engines "<< endl;
            cout<<"Engine 1 name: "<<engine_ptr1->getname();
            cout<<", Engine 2 name: "<<engine_ptr2->getname()<<endl;
        }
        
        // Custom Destructor
        ~Car() {
            cout<<"\n Car-Destructor : car with 2 engines "<< endl;
            if (engine_ptr1)
                cout << "Engine 1 name: " << engine_ptr1->getname() << endl;
            else
                cout << "Engine 1: nullptr" << endl;

            if (engine_ptr2)
                cout << "Engine 2 name: " << engine_ptr2->getname() << endl;
            else
                cout << "Engine 2: nullptr" << endl;

            delete engine_ptr1;    
            delete engine_ptr2;
            // no need to set engine_ptr1 and engine_ptr2 to nullptr. 
            //because the object is getting destroyed anyway
        }

        // Custom Copy Constructor (deep copy)
        Car(const Car& other) {
             this->engine_ptr1 = nullptr; 
             if(other.engine_ptr1) {
                this->engine_ptr1 = new Engine(*other.engine_ptr1) ;
             }

             this->engine_ptr2 = nullptr; 
             if(other.engine_ptr2) {
                this->engine_ptr2 = new Engine(*other.engine_ptr2) ;
             }

            cout<<"\n Car-Copy Constructor : car with 2 engines "<< endl;
            if(engine_ptr1)
                cout<<"Engine 1 name: "<<engine_ptr1->getname() ;
            if(engine_ptr2)
                cout<<", Engine 2 name: "<<engine_ptr2->getname()<<endl;
        }

        // Custom Copy Assignment Operator
        Car& operator=(const Car& other){
            if(this == &other){
                return *this;
            }
            
            delete this->engine_ptr1 ;
            this->engine_ptr1 = nullptr;
            if(other.engine_ptr1) {
                this->engine_ptr1 = new Engine(*other.engine_ptr1) ;
             }

            delete this->engine_ptr2 ;
            this->engine_ptr2 = nullptr;
            if(other.engine_ptr2) {
                this->engine_ptr2 = new Engine(*other.engine_ptr2) ;
            }

            cout<<"\n Car-Copy Assignment Operator : car with 2 engines "<< endl;
            if(engine_ptr1)
                cout<<"Engine 1 name: "<<engine_ptr1->getname() ;
            if(engine_ptr2)
                cout<<", Engine 2 name: "<<engine_ptr2->getname()<<endl;

            return *this;

        }

        // Custom Move Constructor 
        Car(Car&& other) noexcept {
            
            this->engine_ptr1 = other.engine_ptr1 ;
            other.engine_ptr1 = nullptr;

            this->engine_ptr2 = other.engine_ptr2 ;
            other.engine_ptr2 = nullptr;

            cout<<"\n Car-Move Constructor : car with 2 engines "<< endl;
            if(engine_ptr1)
                cout<<"Engine 1 name: "<<engine_ptr1->getname() ;
            if(engine_ptr2)
                cout<<", Engine 2 name: "<<engine_ptr2->getname()<<endl;
        }

        // Custom Move Assignment Operator
        Car& operator=(Car&& other) noexcept{
            if(this == &other){
                return *this;
            }
            
            delete this->engine_ptr1 ;
            this->engine_ptr1 = other.engine_ptr1 ;
            other.engine_ptr1 = nullptr;

            delete this->engine_ptr2 ;
            this->engine_ptr2 = other.engine_ptr2 ;
            other.engine_ptr2 = nullptr;

            cout<<"\n Car-Move Assignment Operator : car with 2 engines "<< endl;
            if(engine_ptr1)
                cout<<"Engine 1 name: "<<engine_ptr1->getname() ;
            if(engine_ptr2)
                cout<<", Engine 2 name: "<<engine_ptr2->getname()<<endl;


            return *this;
        }

        // Start both car engines
        void start(){
            cout<<"\n Starting: Car"<<endl;
            if(engine_ptr1)
                engine_ptr1->start();
            if(engine_ptr2)
                engine_ptr2->start();
        }

};


int main(){
    cout<<"\n\n ------ c1: car: default-constructor--------"<<endl;
    Car c1;  
    
    cout<<"\n\n ------ c2, c3: car: parameterized-constructor--------"<<endl;
    Car c2("v8");  
    Car c3("inline");

    cout<<"\n\n ------ c4: car: copy-constructor (copy c1 to c4) --------"<<endl;
    Car c4(c1);

    cout<<"\n\n ------ c5: car: copy-assignment operator (copy c1 to c5)--------"<<endl;
    Car c5;
    c5 = c1;

    cout<<"\n\n ------ c6: car: move-constructor (std::move c2 to c6)--------"<<endl;
    //Note:   Car c5{Car()}; will not work . Since C++17, the compiler performs guaranteed copy elision
    Car c6{std::move(c2)};

    cout<<"\n\n ------ c4: car: move-assignment operator, (std::move c3 to c4)--------"<<endl;
    c4 = std::move(c3);
    

    cout<<"\n\n ------ c4: car: move-assignment operator --------"<<endl;
    c4 = Car("v8", "inline");
    
    cout<<"\n\n ----------- THE END -----------------------"<<endl;
    
}