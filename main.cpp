#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

class Appliance {
private:
    string name;
    double power{0};
    double hours{0};

public:
    void input() {
        cout << "enter appliance name: ";
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, name);

        do {
            cout << "enter power rating (watts): ";
            cin >> power;
            if (power <= 0) cout << "power must be greater than 0.\n";
        } while (power <= 0);

        do {
            cout << "enter daily usage hours (0-24): ";
            cin >> hours;
            if (hours < 0 || hours > 24) cout << "hours must be between 0 and 24.\n";
        } while (hours < 0 || hours > 24);
        if (cin.peek() == '\n') cin.ignore();
    }

    double calculateEnergy() const { return (power * hours) / 1000.0; }

    void display() const {
        cout << fixed << setprecision(2);
        cout << "name: " << name << " | power: " << power << " W | hours: " << hours
             << " | energy: " << calculateEnergy() << " KWh\n";
    }

    const string &getName() const { return name; }
    double getPower() const { return power; }
    double getHours() const { return hours; }

    void setData(const string &n, double p, double h) {
        name = n;
        power = p;
        hours = h;
    }
};

int main() {
    vector<Appliance> appliances;
    int choice{ -1 };

    do {
        cout << "\n=== electrical load monitoring system ===\n";
        cout << "1. register appliance\n";
        cout << "2. view appliances\n";
        cout << "3. calculate total energy consumption\n";
        cout << "4. calculate bill\n";
        cout << "5. save to file\n";
        cout << "6. load from file\n";
        cout << "0. exit\n";
        cout << "enter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "invalid input. please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            Appliance a;
            if (cin.peek() == '\n') cin.ignore();
            a.input();
            appliances.push_back(a);
            cout << "appliance registered successfully!\n";
            break;
        }

        case 2: {
            if (appliances.empty()) {
                cout << "no appliance registered.\n";
            } else {
                for (const auto &a : appliances) a.display();
            }
            break;
        }

        case 3: {
            if (appliances.empty()) {
                cout << "no appliance registered.\n";
            } else {
                double totalenergy = 0;
                for (const auto &a : appliances) totalenergy += a.calculateEnergy();
                cout << fixed << setprecision(2);
                cout << "total daily energy consumption: " << totalenergy << " KWh\n";
            }
            break;
        }

        case 4: {
            if (appliances.empty()) {
                cout << "no appliance registered.\n";
                break;
            }
            double tariff;
            do {
                cout << "enter tariff rate (per KWh): ";
                cin >> tariff;
                if (tariff <= 0) cout << "tariff must be greater than 0.\n";
            } while (tariff <= 0);

            double totalenergy = 0;
            for (const auto &a : appliances) totalenergy += a.calculateEnergy();
            double bill = totalenergy * tariff;
            cout << fixed << setprecision(2);
            cout << "\n===== bill summary =====\n";
            cout << "total energy consumption: " << totalenergy << " KWh\n";
            cout << "tariff rate: KShs. " << tariff << " per KWh\n";
            cout << "total bill: KShs. " << bill << "\n";
            break;
        }

        case 5: {
            ofstream file("appliances.txt");
            if (!file) {
                cout << "failed to open appliances.txt for writing.\n";
                break;
            }
            for (const auto &a : appliances) {
                file << a.getName() << '\n' << a.getPower() << ' ' << a.getHours() << '\n';
            }
            file.close();
            cout << "appliances saved to appliances.txt\n";
            break;
        }

        case 6: {
            ifstream file("appliances.txt");
            if (!file) {
                cout << "failed to open appliances.txt for reading.\n";
                break;
            }
            appliances.clear();
            string name;
            double power{0}, hours{0};
            while (getline(file, name)) {
                if (!(file >> power >> hours)) break;
                file.ignore(numeric_limits<streamsize>::max(), '\n');
                Appliance a;
                a.setData(name, power, hours);
                appliances.push_back(a);
            }
            file.close();
            cout << "data loaded successfully!\n";
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