#include <pthread.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "vector"
#include "sstream"
#include <semaphore.h>
#include <atomic>
#include <chrono>
#include <thread>

using namespace std;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t atm_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t cableTV = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t electricity = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t gas = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t telecommunication = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t water = PTHREAD_MUTEX_INITIALIZER;

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

// Declare exit flags for ATMs
/*
array<atomic<bool>, 10> exit_flags;*/

/*array<atomic<bool>, 10> exit_flags = {0,0,0,0,0,0,0,0,0,0};*/

atomic<bool> exit_atm1(false);
atomic<bool> exit_atm2(false);
atomic<bool> exit_atm3(false);
atomic<bool> exit_atm4(false);
atomic<bool> exit_atm5(false);
atomic<bool> exit_atm6(false);
atomic<bool> exit_atm7(false);
atomic<bool> exit_atm8(false);
atomic<bool> exit_atm9(false);
atomic<bool> exit_atm10(false);

struct customer
{
    int sleep_time;
    int atm;
    int type;
    int amount;
    int id;
};

int cableTV_balance = 0;
int electricity_balance = 0;
int gas_balance = 0;
int telecommunication_balance = 0;
int water_balance = 0;

vector<customer> atm_buffer(10);
vector<customer> log_data;


void pay_bill(int type, int amount)
{

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
    else if(type == 5){
        pthread_mutex_lock(&water);
        water_balance += amount;
        pthread_mutex_unlock(&water);
    }

}

void *write_buffer(void *customer_param){
    customer* current_customer = (customer*)customer_param;
    int atm = current_customer->atm;
    std::this_thread::sleep_for(std::chrono::milliseconds(current_customer->sleep_time));

    if(atm == 1){
        sem_wait(&empty1);
        pthread_mutex_lock(&m1);
        // do stuff
        atm_buffer[0].amount = current_customer->amount;
        atm_buffer[0].type = current_customer->type;
        atm_buffer[0].atm = current_customer->atm;
        atm_buffer[0].id = current_customer->id;
        pthread_mutex_unlock(&m1);
        sem_post(&full1);

    }
    else if(atm == 2){
        sem_wait(&empty2);
        pthread_mutex_lock(&m2);
        // do stuff
        atm_buffer[1].amount = current_customer->amount;
        atm_buffer[1].type = current_customer->type;
        atm_buffer[1].atm = current_customer->atm;
        atm_buffer[1].id = current_customer->id;
        pthread_mutex_unlock(&m2);
        sem_post(&full2);

    }
    else if(atm == 3){
        sem_wait(&empty3);
        pthread_mutex_lock(&m3);
        // do stuff
        atm_buffer[2].amount = current_customer->amount;
        atm_buffer[2].type = current_customer->type;
        atm_buffer[2].atm = current_customer->atm;
        atm_buffer[2].id = current_customer->id;
        pthread_mutex_unlock(&m3);
        sem_post(&full3);

    }
    else if(atm == 4){
        sem_wait(&empty4);
        pthread_mutex_lock(&m4);
        // do stuff
        atm_buffer[3].amount = current_customer->amount;
        atm_buffer[3].type = current_customer->type;
        atm_buffer[3].atm = current_customer->atm;
        atm_buffer[3].id = current_customer->id;
        pthread_mutex_unlock(&m4);
        sem_post(&full4);
    }
    else if(atm == 5){
        sem_wait(&empty5);
        pthread_mutex_lock(&m5);
        // do stuff
        atm_buffer[4].amount = current_customer->amount;
        atm_buffer[4].type = current_customer->type;
        atm_buffer[4].atm = current_customer->atm;
        atm_buffer[4].id = current_customer->id;
        pthread_mutex_unlock(&m5);
        sem_post(&full5);
    }
    else if(atm == 6){
        sem_wait(&empty6);
        pthread_mutex_lock(&m6);
        // do stuff
        atm_buffer[5].amount = current_customer->amount;
        atm_buffer[5].type = current_customer->type;
        atm_buffer[5].atm = current_customer->atm;
        atm_buffer[5].id = current_customer->id;
        pthread_mutex_unlock(&m6);
        sem_post(&full6);
    }
    else if(atm == 7){
        sem_wait(&empty7);
        pthread_mutex_lock(&m7);
        // do stuff
        atm_buffer[6].amount = current_customer->amount;
        atm_buffer[6].type = current_customer->type;
        atm_buffer[6].atm = current_customer->atm;
        atm_buffer[6].id = current_customer->id;
        pthread_mutex_unlock(&m7);
        sem_post(&full7);

    }
    else if(atm == 8){
        sem_wait(&empty8);
        pthread_mutex_lock(&m8);
        // do stuff
        atm_buffer[7].amount = current_customer->amount;
        atm_buffer[7].type = current_customer->type;
        atm_buffer[7].atm = current_customer->atm;
        atm_buffer[7].id = current_customer->id;
        pthread_mutex_unlock(&m8);
        sem_post(&full8);

    }
    else if(atm == 9){
        sem_wait(&empty9);
        pthread_mutex_lock(&m9);
        // do stuff
        atm_buffer[8].amount = current_customer->amount;
        atm_buffer[8].type = current_customer->type;
        atm_buffer[8].atm = current_customer->atm;
        atm_buffer[8].id = current_customer->id;
        pthread_mutex_unlock(&m9);
        sem_post(&full9);

    }
    else if(atm == 10){
        sem_wait(&empty10);
        pthread_mutex_lock(&m10);
        // do stuff
        atm_buffer[9].amount = current_customer->amount;
        atm_buffer[9].type = current_customer->type;
        atm_buffer[9].atm = current_customer->atm;
        atm_buffer[9].id = current_customer->id;
        pthread_mutex_unlock(&m10);
        sem_post(&full10);

    }

    delete current_customer;
}

void *read_buffer(void *atm_param){

    int atm = *((int *) atm_param);
    if(atm == 1){
        while(!exit_atm1) {
            sem_wait(&full1);
            pthread_mutex_lock(&m1);
            // do stuff
            pay_bill(atm_buffer.at(0).type, atm_buffer.at(0).amount);
            log_data.push_back(atm_buffer.at(0));
            pthread_mutex_unlock(&m1);
            sem_post(&empty1);
        }

    }
    else if(atm == 2){
        while(!exit_atm2) {
            sem_wait(&full2);
            pthread_mutex_lock(&m2);
            // do stuff
            pay_bill(atm_buffer.at(1).type, atm_buffer.at(1).amount);
            log_data.push_back(atm_buffer.at(1));
            pthread_mutex_unlock(&m2);
            sem_post(&empty2);
        }
    }
    else if(atm == 3){
        while(!exit_atm3) {
            sem_wait(&full3);
            pthread_mutex_lock(&m3);
            // do stuff
            pay_bill(atm_buffer.at(2).type, atm_buffer.at(2).amount);
            log_data.push_back(atm_buffer.at(2));
            pthread_mutex_unlock(&m3);
            sem_post(&empty3);
        }
    }
    else if(atm == 4){
        while(!exit_atm4) {
            sem_wait(&full4);
            pthread_mutex_lock(&m4);
            // do stuff
            pay_bill(atm_buffer.at(3).type, atm_buffer.at(3).amount);
            log_data.push_back(atm_buffer.at(3));
            pthread_mutex_unlock(&m4);
            sem_post(&empty4);
        }
    }
    else if(atm == 5){
        while(!exit_atm5) {
            sem_wait(&full5);
            pthread_mutex_lock(&m5);
            // do stuff
            pay_bill(atm_buffer.at(4).type, atm_buffer.at(4).amount);
            log_data.push_back(atm_buffer.at(4));
            pthread_mutex_unlock(&m5);
            sem_post(&empty5);
        }
    }
    else if(atm == 6){
        while(!exit_atm6) {
            sem_wait(&full6);
            pthread_mutex_lock(&m6);
            // do stuff
            pay_bill(atm_buffer.at(5).type, atm_buffer.at(5).amount);
            log_data.push_back(atm_buffer.at(5));
            pthread_mutex_unlock(&m6);
            sem_post(&empty6);
        }
    }
    else if(atm == 7){
        while(!exit_atm7) {
            sem_wait(&full7);
            pthread_mutex_lock(&m7);
            // do stuff
            pay_bill(atm_buffer.at(6).type, atm_buffer.at(6).amount);
            log_data.push_back(atm_buffer.at(6));
            pthread_mutex_unlock(&m7);
            sem_post(&empty7);
        }
    }
    else if(atm == 8){
        while(!exit_atm8) {
            sem_wait(&full8);
            pthread_mutex_lock(&m8);
            // do stuff
            pay_bill(atm_buffer.at(7).type, atm_buffer.at(7).amount);
            log_data.push_back(atm_buffer.at(7));
            pthread_mutex_unlock(&m8);
            sem_post(&empty8);
        }
    }
    else if(atm == 9){
        while(!exit_atm9) {
            sem_wait(&full9);
            pthread_mutex_lock(&m9);
            // do stuff
            pay_bill(atm_buffer.at(8).type, atm_buffer.at(8).amount);
            log_data.push_back(atm_buffer.at(8));
            pthread_mutex_unlock(&m9);
            sem_post(&empty9);
        }
    }
    else if(atm == 10){
        while(!exit_atm10) {
            sem_wait(&full10);
            pthread_mutex_lock(&m10);
            // do stuff
            pay_bill(atm_buffer.at(9).type, atm_buffer.at(9).amount);
            log_data.push_back(atm_buffer.at(9));
            pthread_mutex_unlock(&m10);
            sem_post(&empty10);
        }
    }

    return 0;

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
    customer temp;
    getline(in_file, line);
    temp.amount = stoi(line);
    id_count++;
    customers.push_back(temp);
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
        string a = value;
        if(value == "cableTV"){
            temp.type = 1;
        }
        else if(value == "electricity"){
            temp.type = 2;
        }
        else if(value == "gas"){
            temp.type = 3;
        }
        else if(value == "telecommunication"){
            temp.type = 4;
        }
        else if(value == "water"){
            temp.type = 5;
        }
        getline(linestream, value, ',');
        temp.amount = stoi(value);
        temp.id = id_count;
        id_count++;

        customers.push_back(temp);

    }

    in_file.close();
    return customers;
}

void print_file(string file_name, int number_of_customers){
    ofstream out_file;
    out_file.open(file_name);

    for(int i=0; i< number_of_customers; i++){

        customer temp = log_data.at(i);
        string type;
        if(temp.type == 1){
            type = "cableTV";
        }
        else if(temp.type == 2){
            type = "electricity";
        }
        else if(temp.type == 3){
            type = "gas";
        }
        else if(temp.type == 4){
            type = "telecommunication";
        }
        else if(temp.type == 5){
            type = "water";
        }
        out_file << "Customer" << temp.id + 1 << "," << temp.amount << "," << type << endl;

    }

    out_file << "All payments are completed." << endl;
    out_file << "CableTV: " << cableTV_balance << endl;
    out_file << "Electricity: " << electricity_balance << endl;
    out_file << "Gas: " << gas_balance << endl;
    out_file << "Telecommunication: " << telecommunication_balance << endl;
    out_file << "Water: " << water_balance << endl;
    out_file.close();
}

int main(int argc, char** argv)

{
    if(argc != 2){
        cout << "Number of parameters should be 1." <<endl;
        return 1;
    }

    // Initialize semaphores

    sem_init(&empty1, 0, 1);
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
    customers = get_input(argv[1]);

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

    // Creating customer threads
    int NUMBER_OF_THREADS = customers[0].amount; //  First customers actually just presents how many customers there is.
    pthread_t thread[NUMBER_OF_THREADS];
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
        arg->id = current.id;
        int result = pthread_create(&thread[current_t], NULL, write_buffer, (void *)arg);
        if (result !=0)
        {
            cout << "Error creating thread " << current_t << ". Return code:" << result <<  endl;
        }

    }

    for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++)
    {
        pthread_join(thread[current_t], NULL);
    }

    cout << "All payments are completed." << endl;

    exit_atm1 = true;
    exit_atm2 = true;
    exit_atm3 = true;
    exit_atm4 = true;
    exit_atm5 = true;
    exit_atm6 = true;
    exit_atm7 = true;
    exit_atm8 = true;
    exit_atm9 = true;
    exit_atm10 = true;


    cout << "cableTv: " << cableTV_balance << endl;
    cout << "electricity: " << electricity_balance << endl;
    cout << "gas: " << gas_balance << endl;
    cout << "telecommunication: " << telecommunication_balance << endl;
    cout << "water: " << water_balance << endl;

    string in_file = argv[1];
    string sub_str = in_file.substr(0, in_file.size()-4);
    string out_file = sub_str + "_log.txt";
    print_file(out_file, NUMBER_OF_THREADS);

    return 0;
}