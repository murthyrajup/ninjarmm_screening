// ninjaone.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

// ===== Start of class Job and its derived classes =============

// a. Create a class Job
class Job {
private:
    string name;
    string description;
    uint32_t hours;
protected:
    //disallow copy and assignement
    Job(Job const&) = delete;
    void operator=(Job const&) = delete;
public:
    // constructor
    Job(const string& job_name,
        const string& job_description,
        const uint32_t& job_hours): name(job_name),
                                    description(job_description),
                                    hours(job_hours)
    {
    }

    // accessors
    // d.i. Get the name of the job
    const string& jobName() const { return name; }

    // d.ii. Get the description of the job
    const string& jobDescription() const { return description; }

    // d.iii. Get the number of hours required by the job
    const uint32_t& hoursRequired() const { return hours; }

    // d.iv. A DoWork function that prints out “My work involves ” + the description.  
    void DoWork() {
        cout << "My work involves " + description << endl;
    }

};

// b. Create a subclass Programmer
class Programmer : public Job {
public:
    Programmer(const string& job_name,
               const string& job_description,
               const uint32_t& job_hours):Job(job_name, job_description, job_hours){}
};

// c. Create a subclass Pilot
class Pilot : public Job {
public:
    Pilot(const string& job_name,
          const string& job_description,
          const uint32_t& job_hours) :Job(job_name, job_description, job_hours) {}

};

// ===== End of class Job and its derived classes =============

// ===== Start of finding a range bound =============

// h. Create a template function that will test if the provided values are within a range
// Call the function and print out the inputs and result. The following should execute assuming httpResponse is a uint32_t value:
// IsInBounds<uint32_t>(httpResponseCode, 500, 599);
template <typename T>
void IsInBounds(const T& httpResponseCode, const T& low, const T& high) {
    cout << "httpResponseCode: " << httpResponseCode <<  "  Low Response Code: " << low << "  High Response Code: " << high << endl;
    if (httpResponseCode >= low && httpResponseCode <= high) {
        cout << httpResponseCode << " is between the range " << low << " and " << high << endl;
    }
    else {
        cout << httpResponseCode << " is not between the range " << low << " and " << high << endl;
    }
}

// ===== End of finding a range bound =============

// ===== Start of finding a matching string in a collection of strings =============

struct compare
{
    string key;
    compare(string const& i) : key(i) {}
    bool operator()(string const& i) {
        return (i == key);
    }
};

auto ContainsTheString(const vector<string>& theStrings, compare comp) {
    auto count = count_if(theStrings.begin(), theStrings.end(), comp);
    return count;
}

// ===== End of finding a matching string in a collection of strings =============

// ===== Start of variadic templates =============
template<typename T> // base case
T adder(T v) {
    return v;
}
// general case which recurses - no actual recursion
template <typename T, typename... Args> // template parameter pack
T adder(T first, Args... args) { // function parameter pack
    return first + adder(args...);
}

void test_adder() {
    cout << "=== Testing Variadic template basics - add multiple numbers ===" << endl;
    cout << "single number: " << adder(987) << endl;
    long sum = adder(1, 2, 3, 4, 5);
    cout << "sum of (1, 2, 3, 4, 5) numbers: " << sum << endl;
    sum = adder(987, 789, 657, 623, 444, 999);
    cout << "sum of (987, 789, 657, 623, 444, 999) numbers: " << sum << endl;
    string s1 = "x", s2 = "aa", s3 = "bb", s4 = "yy";
    string ssum = adder(s1, s2, s3, s4);
    cout << "concatenation of s1 = 'x', s2 = 'aa', s3 = 'bb', s4 = 'yy' strings: " << ssum << endl;
    cout << "=== End of Testing Variadic template basics ===" << endl << endl;
}

// pair_comparer accepts any number of arguments and returns true if and only if 
// they are pair-wise equal.The types are not enforced - everything that can be compared goes.
// for even number of args comparison - base case 1
template<typename T>
bool pair_comparer(T a, T b) {
    return a == b;
}

// for odd number of args comparison - base case 2
template<typename T>
bool pair_comparer(T a) {
    return false;
}

// compares the same types
template<typename T, typename... Args> // recursive case - no actual recursion
bool pair_comparer(T a, T b, Args... args) {
    return a == b && pair_comparer(args...);
}
// compares different types
template<typename T1, typename T2, typename... Args>
bool pair_comparer(T1 a, T2 b, Args... args) {
    return a == b && pair_comparer(args...);
}
void test_pair_comparer() {
    cout << "=== Testing Variadic template basics - compare pairs of numbers ===" << endl;
    bool same = pair_comparer(4, 5);
    cout << "compare (4,5): " << boolalpha << same << endl;

    same = pair_comparer(90, 90);
    cout << "compare (90,90): " << boolalpha << same << endl;

    same = pair_comparer(1.5, 1.5, 2, 2, 6, 6);
    cout << "compare (1.5,1.5,2,2,6,6): " << boolalpha << same << endl;

    same = pair_comparer(1.5, 1.5, 2, 2, 7, 6);
    cout << "compare (1.5, 1.5, 2, 2, 7, 6): " << boolalpha << same << endl;

    // this won't compile since a double and int are not the same type.
    //same = pair_comparer(1, 1.5, 2, 2, 7, 6);

    //Does not compile; the compiler complains that the base case expects 2 arguments but only 1 is provided. 
    //same = pair_comparer(1.5, 1.5, 2, 2, 6, 6, 7); // odd number od args - works for even number only

    // this one works because of the base case 2
    same = pair_comparer(1.5, 1.5, 2, 2, 6, 6, 7);
    cout << "compare (1.5, 1.5, 2, 2, 6, 6, 7): " << boolalpha << same << endl;

    same = pair_comparer(1, 1.5, 2, 2, 7, 6);
    cout << "compare (1, 1.5, 2, 2, 7, 6): " << boolalpha << same << endl;
    cout << "=== End of Testing Variadic template basics ===" << endl << endl;
}

// variadic template data structure
// 
// helper declaration - to access the data members of the data structure
template<size_t idx, typename T>
struct GetHelper;

// data structure base case - an empty case
template<typename ... T>
struct DataStructure
{
};

// data structure recursive case - rest of the parameters 
template<typename T, typename ... Rest>
struct DataStructure<T, Rest ...>
{
    DataStructure(const T& first, const Rest& ... rest)
        : first(first)
        , rest(rest...)
    {}

    T first;
    DataStructure<Rest ... > rest;

    template<size_t idx>
    auto get()
    {
        return GetHelper<idx, DataStructure<T, Rest...>>::get(*this);
    }
};

// helper function - helps access the data memers of the data structure - base case
template<typename T, typename ... Rest>
struct GetHelper<0, DataStructure<T, Rest ... >>
{
    static T get(DataStructure<T, Rest...>& data)
    {
        return data.first;
    }
};

// helper function - recursive case
template<size_t idx, typename T, typename ... Rest>
struct GetHelper<idx, DataStructure<T, Rest ... >>
{
    static auto get(DataStructure<T, Rest...>& data)
    {
        return GetHelper<idx - 1, DataStructure<Rest ...>>::get(data.rest);
    }
};

// test variadic template data structure
void test_variadic_data_structure() {
    cout << "=== Testing Variadic template data structure - pass in and access multiple parameters of a data structure ===" << endl;
    DataStructure<int, float, string> data(1, 2.1, "Hello");
    cout << "parameter 1: " << data.get<0>() << endl;
    cout << "parameter 2: " << data.get<1>() << endl;
    cout << "parameter 3: " << data.get<2>() << endl;
    cout << "=== End of Testing Variadic template data structure ===" << endl << endl;
}

// ===== End of variadic templates =============

int main()
{
    cout << endl << "=== Testing of Job and its derived classes ===" << endl << endl;

    // e. dynamically allocate each type of job
    auto pProgrammer = make_unique<Programmer>("Programmer", "designing and developing application software.", 40);
    pProgrammer->DoWork();

    // e. dynamically allocate each type of job   
    auto pPilot = make_unique<Pilot>("Pilot", "operating and controling aircraft along planned routes and during takeoffs and landings.", 24);
    pPilot->DoWork();


    // f. Store each instance in a collection

    // jobs collection
    vector<unique_ptr<Job>> jobs;
    jobs.push_back(move(pProgrammer));
    jobs.push_back(move(pPilot));

    // g. Iterate the collection and call each of the available interface functions
    for (auto const& pJob : jobs) {
        cout << endl;
        cout << "Job Name: " << pJob->jobName() << endl;
        cout << "Job Description: " << pJob->jobDescription() << endl;
        cout << "Hours Required: " << pJob->hoursRequired() << endl;
        cout << endl;
    }

    cout << endl << "=== End of Testing of Job and its derived classes ===" << endl << endl;

    // test IsInBounds
    cout << endl << "=== Testing of a value for a range bound ===" << endl << endl;
    IsInBounds<uint32_t>(500, 500, 599);
    IsInBounds<uint32_t>(599, 500, 599);
    IsInBounds<uint32_t>(503, 500, 599);
    IsInBounds<uint32_t>(960, 500, 599);
    IsInBounds<uint32_t>(-100, 500, 599);
    cout << endl << "=== End of Testing of a value for a range bound ===" << endl << endl;

    
    cout << endl << "=== Testing of matching strings in a collection ===" << endl << endl;
    vector<string> theStrings{ "one", "two", "two", "test", "test", "test" };
    cout << "theStrings  {'one', 'two', 'two', 'test', 'test', 'test'}" <<  endl;
    compare comp1("one");
    auto count = ContainsTheString(theStrings, comp1);
    cout << "count of 'one': " << count << endl;
    compare comp2("two");
    count = ContainsTheString(theStrings, comp2);
    cout << "count of 'two': " << count << endl;
    compare comp3("test");
    count = ContainsTheString(theStrings, comp3);
    cout << "count of 'test': " << count << endl;
    cout << endl << "=== End of Testing of matching strings in a collection ===" << endl << endl;

    // testing of variadic templates
    test_adder();
    test_pair_comparer();
    test_variadic_data_structure();

    return 0;
}
