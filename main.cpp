#include <pthread.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "vector"
#include "sstream"
#include <semaphore.h>

using namespace std;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t atm_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t cableTV = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t electricity = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t gas = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t telecommunication = PTHREAD_MUTEX_INITIALIZER;

// Declare mutexes for ATM critical sections

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m4 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m5 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m6 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m7 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m8 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m9 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m10 = PTHREAD_MUTEX_INITIALIZER;

// Declare semaphores used for bounded buffer of ATM's

sem_t empty1;
sem_t empty2;
sem_t empty3;
sem_t empty4;
sem_t empty5;
sem_t empty6;
sem_t empty7;
sem_t empty8;
sem_t empty9;
sem_t empty10;

sem_t full1;
sem_t full2;
sem_t full3;
sem_t full4;
sem_t full5;
sem_t full6;
sem_t full7;
sem_t full8;
sem_t full9;
sem_t full10;

struct customer
{
    int sleep_time;
    int atm;
    string type;
    int amount;
    int id;
};

int cableTV_balance = 0;
int electricity_balance = 0;
int gas_balance = 0;
int telecommunication_balance = 0;

vector<customer> atm_buffer(10);


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

void *write_buffer(void *customer_param){
    customer* current_customer = (customer*)customer_param;
    int atm = current_customer->atm;

    cout << "girdim, type: " << atm << endl;
    if(atm == 1){
        sem_wait(&empty1);
        pthread_mutex_lock(&m1);
        // do stuff

        cout << "TEST" << endl;


        //
        pthread_mutex_unlock(&m1);
        sem_post(&full1);

    }
    else if(atm == 2){

    }
    else if(atm == 3){

    }
    else if(atm == 4){

    }
    else if(atm == 5){

    }
    else if(atm == 6){

    }
    else if(atm == 7){

    }
    else if(atm == 8){

    }
    else if(atm == 9){

    }
    else if(atm == 10){

    }

    delete current_customer;
}

void *read_buffer(void *atm_param){

    int atm = *((int *) atm_param);

    cout << "girdim, type: " << atm << endl;
    if(atm == 1){
        while(true) {
            sem_wait(&full1);
            pthread_mutex_lock(&m1);
            // do stuff

            //
            pthread_mutex_unlock(&m1);
            sem_post(&empty1);
        }

    }
    else if(atm == 2){
        while(true) {
            sem_wait(&full2);
            pthread_mutex_lock(&m2);
            // do stuff

            //
            pthread_mutex_unlock(&m2);
            sem_post(&empty2);
        }
    }
    else if(atm == 3){
        while(true) {
            sem_wait(&full3);
            pthread_mutex_lock(&m3);
            // do stuff

            //
            pthread_mutex_unlock(&m3);
            sem_post(&empty3);
        }
    }
    else if(atm == 4){
        while(true) {
            sem_wait(&full4);
            pthread_mutex_lock(&m4);
            // do stuff

            //
            pthread_mutex_unlock(&m4);
            sem_post(&empty4);
        }
    }
    else if(atm == 5){
        while(true) {
            sem_wait(&full5);
            pthread_mutex_lock(&m5);
            // do stuff

            //
            pthread_mutex_unlock(&m5);
            sem_post(&empty5);
        }
    }
    else if(atm == 6){
        while(true) {
            sem_wait(&full6);
            pthread_mutex_lock(&m6);
            // do stuff

            //
            pthread_mutex_unlock(&m6);
            sem_post(&empty6);
        }
    }
    else if(atm == 7){
        while(true) {
            sem_wait(&full7);
            pthread_mutex_lock(&m7);
            // do stuff

            //
            pthread_mutex_unlock(&m7);
            sem_post(&empty7);
        }
    }
    else if(atm == 8){
        while(true) {
            sem_wait(&full8);
            pthread_mutex_lock(&m8);
            // do stuff

            //
            pthread_mutex_unlock(&m8);
            sem_post(&empty8);
        }
    }
    else if(atm == 9){
        while(true) {
            sem_wait(&full9);
            pthread_mutex_lock(&m9);
            // do stuff

            //
            pthread_mutex_unlock(&m9);
            sem_post(&empty9);
        }
    }
    else if(atm == 10){
        while(true) {
            sem_wait(&full10);
            pthread_mutex_lock(&m10);
            // do stuff

            //
            pthread_mutex_unlock(&m10);
            sem_post(&empty10);
        }
    }

}

void * thread_talk(void *param)

{
    //do some operation here
    customer* a = (customer*)param;
    // do stuff
    pthread_mutex_lock(&m);
    cout << "customer number: " << a->amount << endl;
    delete a;
    pthread_mutex_unlock(&m);
    pthread_exit(NULL);         //exit from current thread
}

void * atm(void *param)

{
    //do some operation here
    int id = *((int *) param);
    free(param);
    pthread_mutex_lock(&atm_mutex);
  /*  cout << "atm id: " << id << endl;*/
    pthread_mutex_unlock(&atm_mutex);
    pthread_exit(NULL);         //exit from current thread
}



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
        cout << "atm number: " << stoi(value) << endl;
        getline(linestream, value, ',');
        temp.type = value;
        cout << "atm number: " << endl;
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

    // Initialize semaphores

    sem_init(&empty1, 0, 3);
    sem_init(&empty2, 0, 1);
    sem_init(&empty3, 0, 1);
    sem_init(&empty4, 0, 1);
    sem_init(&empty5, 0, 1);
    sem_init(&empty6, 0, 1);
    sem_init(&empty7, 0, 1);
    sem_init(&empty8, 0, 1);
    sem_init(&empty9, 0, 1);
    sem_init(&empty10, 0, 1);

    sem_init(&full1, 0, 0);
    sem_init(&full2, 0, 0);
    sem_init(&full3, 0, 0);
    sem_init(&full4, 0, 0);
    sem_init(&full5, 0, 0);
    sem_init(&full6, 0, 0);
    sem_init(&full7, 0, 0);
    sem_init(&full8, 0, 0);
    sem_init(&full9, 0, 0);
    sem_init(&full10, 0, 0);

    vector<customer> customers;
    customers = get_input("input_me.txt");

    pthread_t atm_threads[10];
    int temp_arg_atm[10] ;

    /*creating all atm threads*/
    for(int current_t = 1; current_t < 11; current_t++)
    {
        temp_arg_atm[current_t]   = current_t;
        int *arg = (int*)malloc(sizeof(*arg));
        *arg = current_t;
        int result = pthread_create(&atm_threads[current_t], NULL, read_buffer, arg);

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
    for(int current_t = 1; current_t < NUMBER_OF_THREADS+1; current_t++)
    {

        temp_arg[current_t]   = current_t;
        customer current = customers.at(current_t);
        customer* arg = new customer;
        arg->atm = current.atm;
        arg->amount = current.amount;
        arg->type = current.type;
        arg->sleep_time = current.sleep_time;
        arg->id = current_t;
        cout << current_t << endl;
        int result = pthread_create(&thread[current_t], NULL, write_buffer, (void *)arg);
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