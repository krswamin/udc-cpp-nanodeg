using namespace std;

void processDataRaw(){
    MyResource* res = new MyResource(); // Acquire
    try {
        res->doWork();
        //What if an exception occurs here ? Leak !
    } catch(....) {
        delete res; // Need to clean up on exception
        throw;
    }
    delete res; // Release (if no exception)
}