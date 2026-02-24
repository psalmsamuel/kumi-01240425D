# include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

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

    double calculateEnergy() const {
        return (power * hours) / 1000.0;
    }

    void display() const {
        cout <<"name: "<< name <<" | power: " << power << "W" <<"| hours: " <<
        hours <<  " | energy: " << calculateEnergy() << "KWh\n" << endl;
        
         
    }

    string getName() const {
        return name;
    }
    double getPower() const {
        return power;
    }
    double getHours() const {
        return hours;
    }

    void setData(string n, double p, double h) {
        name = n;
        power = p;
        hours = h;
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
        cout <<"3. calculate total energy consumption\n";
        cout <<"4. calculate bill\n";
        cout <<"5. save to file\n";
        cout <<"6. load from file\n";
        cout <<"0. exit\n";
        cout <<"enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (count >= 100) {
                    cout <<"maximum appliance limit reached. cannot register more.\n";
                    break;
                }
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

            case 3: {
                if (count == 0){
                    cout <<"no appliance registered.\n";
                } else {
                    double
                    totalenergy = 0;
                    for (int i = 0; i < count; i++) { 
                    totalenergy += appliaces[i].calculateEnergy();
                    }
                    cout << fixed << setprecision(2);
                                                      cout <<"total daily energy consumption: "
                                                      << 
                                                      totalenergy << "KWh\n";
                }
                break;

                case 4: {
                    if (count == 0) {
                        cout <<"no appliance registered.\n";
                        break;
                    }
                    double tariff;
                    do {
                        cout <<"enter tariff rate (per KWh): ";
                        cin >> tariff;
                        if (tariff <= 0)
                            cout <<"tariff must be greater than 0. \n";
                    } while (tariff <= 0);
                    double totalenergy = 0;
                    for (int i = 0; i < count; i++) {
                        totalenergy += appliaces[i].calculateEnergy();

                    }
                    double bill = totalenergy * tariff;
                    cout << fixed << setprecision(2);
                    cout <<"\n===== bill summary =====\n";
                    cout <<"total energy consumption: " << totalenergy << " KWh\n";
                    cout <<"tariff rate: KShs. " << tariff << " per KWh\n";
                    cout <<"total bill: KShs. " << bill << endl;
                    break;
                }

                case 5: {
                    ofstream
                    file("appliances.txt");
                    for(int i = 0; i < count; i++) {
                        file << appliaces[i].getName() << " "
                             << appliaces[i].getPower() << " "
                             << appliaces[i].getHours() << endl;
                    }
                    file.close();
                    cout <<"appliances saved to appliances.txt\n";
                    break;
                }

            case 6: {
                ifstream file("appliances.txt");

                string name;
                double power, hours;
                count = 0;
                while (file >> name >> power >> hours) {
                    appliaces[count].setData(name, power, hours);
                    count++;
                }
                file.close();
                cout <<"data loaded successfully!\n";
                break;
            }
            case 0:
                cout << "exiting....\n";
                break;
            default:
                cout << "invalid choice. try again. \n";
        }
    } while (choice != 0);
    
    return 0;
}