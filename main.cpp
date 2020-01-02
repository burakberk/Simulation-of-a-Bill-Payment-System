#include <pthread.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "vector"
#include "sstream"

using namespace std;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cableTV = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t electricity = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t gas = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t telecommunication = PTHREAD_MUTEX_INITIALIZER;

int cableTV_balance = 0;
int electricity_balance = 0;
int gas_balance = 0;
int telecommunication_balance = 0;

/*const int NUMBER_OF_THREADS = 5;*/

void *pay_bill(void *type_param, void *amount_param)
{
    int amount = *((int *) amount_param);
    int type = *((int *) type_param);
    if(type == 1){
        pthread_mutex_lock(&cableTV);
        cableTV_balance += amount;
        pthread_mutex_unlock(&cableTV);
    }
    else if(type == 2){
        pthread_mutex_lock(&electricity);
        electricity_balance += amount;
        pthread_mutex_unlock(&electricity);
    }
    else if(type == 3){
        pthread_mutex_lock(&gas);
        gas_balance += amount;
        pthread_mutex_unlock(&gas);
    }
    else if(type == 4){
        pthread_mutex_lock(&telecommunication);
        telecommunication_balance += amount;
        pthread_mutex_unlock(&telecommunication);
    }

}

void * thread_talk(void *param)

{
    //do some operation here
    int a = *((int *) param);
    free(param);
    pthread_mutex_lock(&m);
    /*cout << "thread number: " << a << endl;*/
    pthread_mutex_unlock(&m);
    pthread_exit(NULL);         //exit from current thread
}

void * atm(void *param)

{
    //do some operation here
    int id = *((int *) param);
    free(param);
    pthread_mutex_lock(&m);
    cout << "atm id: " << id << endl;
    pthread_mutex_unlock(&m);
    pthread_exit(NULL);         //exit from current thread
}

struct customer
{
    int sleep_time;
    int atm;
    string type;
    int amount;
    int id;
};


vector<customer> get_input(string file_name){ // Read the input from the text file
    vector<customer> customers;
    ifstream in_file;
    in_file.open(file_name);
    if (!in_file) {
        cerr << "Unable to open the input file";
        exit(1);
    }

    int id_count = -1;
    string line;
    while(getline(in_file,line))
    {
        customer temp;
        stringstream linestream(line);
        string value;

        getline(linestream, value, ',');
        temp.sleep_time = stoi(value);
        getline(linestream, value, ',');
        temp.atm = stoi(value);
        getline(linestream, value, ',');
        temp.type = value;
        getline(linestream, value, ',');
        temp.amount = stoi(value);
        temp.id = id_count;
        id_count++;

        customers.push_back(temp);

        /*while(getline(linestream,value,','))
        {
            std::cout << "Value(" << value << ") - ";
        }
        std::cout << "Line Finished" << std::endl;*/

    }

    in_file.close();
    return customers;
}

void print_file(){
    vector<customer> file_result;
    file_result = get_input("input_cmpe.txt");
    for(int i= 0; i<file_result.size(); i++){
        cout << file_result[i].sleep_time << " " << file_result[i].atm << " " << file_result[i].type << " " << file_result[i].amount <<endl;
    }
}

int main()

{

    vector<customer> customers;
    customers = get_input("input_cmpe.txt");

    pthread_t atm_threads[10];
    int temp_arg_atm[10] ;

    /*creating all atm threads*/
    for(int current_t = 1; current_t < 11; current_t++)
    {
        cout << current_t << endl;
        temp_arg_atm[current_t]   = current_t;
        int *arg = (int*)malloc(sizeof(*arg));
        *arg = current_t;
        int result = pthread_create(&atm_threads[current_t], NULL, atm, arg);

        if (result !=0)
        {
            cout << "Error creating thread " << current_t << ". Return code:" << result <<  endl;
        }

    }

    int NUMBER_OF_THREADS = customers[0].amount; //  First customers actually just presents how many customers there is.

    pthread_t thread[NUMBER_OF_THREADS];

    cout << "Starting all threads..." << endl;

    int temp_arg[NUMBER_OF_THREADS] ;

    /*creating all customer threads*/
    for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++)
    {

        temp_arg[current_t]   = current_t;
        int *arg = (int*)malloc(sizeof(*arg));
        *arg = current_t;
        int result = pthread_create(&thread[current_t], NULL, thread_talk, arg);

        if (result !=0)
        {
            cout << "Error creating thread " << current_t << ". Return code:" << result <<  endl;
        }

    }

    /*creating all threads*/

/*Joining all threads*/
    for(int current_t = 1; current_t < 11; current_t++)
    {
        pthread_join(atm_threads[current_t], NULL);
    }

    for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++)
    {
        pthread_join(thread[current_t], NULL);
    }

/*Joining all threads*/
    cout << "All threads completed." << endl;



    return 0;
}