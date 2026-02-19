# include <iostream>
#include <string>

using namespace std;
class appliace {
    private:
    string name;
    double power;
    double hours;

    public: 
    void input()  {
        cout <<"enter appliance name: ";
        cin >> name;
        do {
            cout <<"enter power rating (watts): ";
            cin >> power;
            if (power <= 0)
            cout <<"power must be greater than 0. \n";
        } while (power <= 0);
        do {
            cout <<"enter daily usage hours (0-24): ";
            cin >> hours;
            if (hours < 0 || hours > 24)
                cout <<"hours must be between 0 and 24. \n";
        } while (hours < 0 || hours > 24);
    }

    void display() const {
        cout <<"name: "<< name <<" | power: " << power << "W" <<"| hours: " <<
        hours << endl;
    }
};

int main () {
    appliace appliaces [100];
    int count = 0;
    int choice;
    do {
        cout << "\n=== electrical load monitoring system ===\n";
        cout <<"1. register appliance\n";
        cout <<"2. view appliances\n";
        cout <<"0. exit\n";
        cout <<"enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                appliaces[count].input();
                count++;
                cout <<"appliance registered successfully!\n";
                break;

            case 2:
                if (count == 0){
                    cout <<"no appliance registered.\n";
                } else {
                    for (int i = 0; i < count; i++) {
                        appliaces[i].display();
                    }
                } 
                break;

            case 0:
                cout << "exiting....\n";
                break;
            default:
                cout << "invalid choice. try again. \n";
        }
    } while (choice != 0);
    
    return 0;
}