#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include <cstring>
#include<conio.h>
#include<cmath>
#include<iomanip>
#include<time.h>
#include<windows.h>
#include <stdlib.h>

using namespace std;

class JG {
    string month;
    char des[100];
    int credit, debit, date;
    static int n;
public:
    void setmonth(string x) {
        month = x;
    }
    string getmonth() {
        return month;
    }
    void setdes(string x) {
        for (int i = 0; i < x.size(); i++) {
            des[i] = x[i];
        }
        des[x.size()] = '\0';
    }
    string getdes() {
        return string(des);
    }
    void setcredit(int x) {
        credit = x;
    }
    int getcredit() {
        return credit;
    }
    void setdebit(int x) {
        debit = x;
    }
    int getdebit() {
        return debit;
    }
    void setdate(int x) {
        date = x;
    }
    int getdate() {
        return date;
    }
    int getn() {
        return n;
    }
    void setn() {
        ifstream xx;
        xx.open("No_of_entries.txt");
        if (xx) {
            int no;
            xx >> no;
            n = no;
            xx.close();
        }
    }
    JG() {
    }
    JG(string x, string y, int z) {
        month.clear();
        month = x;
        date = z;
        memset(des, 0, 100);
        for (int i = 0; i < y.size(); i++) {
            des[i] = y[i];
        }
        des[y.size()] = '\0';
    }
    void cord() {
        int a;
        for (;;) {
            cout << "Is the transaction credit ( press 1) or debit ( press 2)" << endl;
            a = 0;
            cin >> a;
            if (!cin) {
                cout << "INVALID RE-ENTER" << endl;
                continue;
            }
            if (a == 1) {
                cout << "enter amount:" << endl;
                cin >> credit;
                debit = 0;
                break;
            } else if (a == 2) {
                cout << "enter amount:" << endl;
                cin >> debit;
                credit = 0;
                break;
            }
        }
    }

    friend class accountant;
};

int JG::n = 0;

class accountant {
    string password;
public:
    accountant() {
    }
    accountant(string x) : password(x) {
        ofstream aa;
        aa.open("pass.txt");
        aa << password;
        aa.close();
    }
    bool check(string x) {
        string pass;
        ifstream aa;
        aa.open("pass.txt");
        aa >> pass;
        aa.close();

        if (pass == x) {
            return true;
        } else {
            return false;
        }
    }
    void initializefile(JG j) {
        ifstream jg;
        jg.open("general_journal.csv");
        if (jg) {
            jg.close();
            ifstream xx;
            xx.open("No_of_entries.txt");
            if (xx) {
                int no;
                xx >> no;
                j.n = no + 1;
                xx.close();
            } else {
                j.n++;
            }
            ofstream jh;
            jh.open("general_journal.csv", ios::app);
            if (j.getdebit() != 0) {
                jh << j.getn() << "," << j.getmonth() << " " << j.getdate() << "," << j.getdes() << "," << " " << "," << j.getdebit() << "," << " " << "," << " " << endl;
            } else {
                jh << j.getn() << "," << j.getmonth() << " " << j.getdate() << "," << " " << "," << j.getdes() << "," << " " << "," << j.getcredit() << "," << " " << endl;
            }
            jh.close();
            ofstream aa;
            aa.open("No_of_entries.txt");
            aa << j.getn() << endl;;
            aa.close();
            ofstream obj;
            obj.open("gj.txt", ios::app);
            obj.write((char*)&j, sizeof(j));
            obj.close();
            return;
        } else {
            jg.close();
            ifstream xx;
            xx.open("No_of_entries.txt");
            if (xx) {
                int no;
                xx >> no;
                j.n = no + 1;
                xx.close();
            } else {
                j.n++;
            }
            ofstream gg;
            gg.open("general_journal.csv");
            gg << "ENTRY NO" << "," << "DATE" << "," << "DESCRIPTION" << "," << " " << "," << "DR+" << "," << "CR+" << endl;
            if (j.getdebit() != 0) {
                gg << j.getn() << "," << j.getmonth() << " " << j.getdate() << "," << j.getdes() << "," << " " << "," << j.getdebit() << endl;
            } else {
                gg << j.getn() << "," << j.getmonth() << " " << j.getdate() << "," << " " << "," << j.getdes() << "," << " " << "," << j.getcredit() << endl;
            }
            gg.close();
            ofstream aa;
            aa.open("No_of_entries.txt");
            aa << j.getn() << endl;
            aa.close();
            ofstream obj;
            obj.open("gj.txt");
            obj.write((char*)&j, sizeof(j));
            obj.close();
            return;
        }
        return;
    }

    void updatefile(int x, JG j) {
        int num;
        ifstream xx;
        xx.open("No_of_entries.txt");
        if (xx) {
            int no;
            xx >> no;
            num = no;
            xx.close();
        }

        JG g[num];

        ifstream obj;
        obj.open("gj.txt");
        obj.read((char*)&g, sizeof(g));
        obj.close();

        g[x - 1].setmonth(j.getmonth());
        g[x - 1].setdes(j.getdes());
        g[x - 1].setcredit(j.getcredit());
        g[x - 1].setdebit(j.getdebit());
        g[x - 1].setdate(j.getdate());

        ofstream gg;
        gg.open("general_journal.csv");
        gg << "ENTRY NO" << "," << "DATE" << "," << "DESCRIPTION" << "," << " " << "," << "DR+" << "," << "CR+" << endl;
        for (int i = 0; i < num; i++) {
            if (g[i].getdebit() != 0) {
                gg << i + 1 << "," << g[i].getmonth() << " " << g[i].getdate() << "," << g[i].getdes() << "," << " " << "," << g[i].getdebit() << endl;
            } else {
                gg << i + 1 << "," << g[i].getmonth() << " " << g[i].getdate() << "," << " " << "," << g[i].getdes() << "," << " " << "," << g[i].getcredit() << endl;
            }
        }
        gg.close();
        ofstream obj1;
        obj1.open("gj.txt");
        obj1.write((char*)&g, sizeof(g));
        obj1.close();
    }

    void display() {
        int num;
        ifstream xx;
        xx.open("No_of_entries.txt");
        if (xx) {
            int no;
            xx >> no;
            num = no;
            xx.close();
        }

        JG g[num];

        ifstream obj;
        obj.open("gj.txt");
        obj.read((char*)&g, sizeof(g));
        obj.close();

        cout << "ENTRY NO" << "," << "DATE" << "," << "DESCRIPTION" << "," << " " << "," << "DR+" << "," << "CR+" << endl;
        for (int i = 0; i < num; i++) {
            if (g[i].getdebit() != 0) {
                cout << i + 1 << "," << g[i].getmonth() << " " << g[i].getdate() << "," << g[i].getdes() << "," << " " << "," << g[i].getdebit() << endl;
            } else {
                cout << i + 1 << "," << g[i].getmonth() << " " << g[i].getdate() << "," << " " << "," << g[i].getdes() << "," << " " << "," << g[i].getcredit() << endl;
            }
        }
    }
};

class Taccount : public JG {
public:
    Taccount() {
    }
    void create() {
        JG g[getn()];
        int deb[getn()], cre[getn()], sum = 0, z = 0, no2 = 0, x = 1;
        int idk[getn()];
        for (int j = 0; j < getn(); j++) {
            idk[j] = -1;
            deb[j] = 0;
            cre[j] = 0;
        }

        ifstream obj;
        obj.open("gj.txt");
        obj.read((char*)&g, sizeof(g));
        obj.close();

        ofstream oj;
        oj.open("Taccounts.csv");
    jump:
        for (int i = no2; i < getn() - 1; i++) {
            for (int j = 0; j < getn(); j++) {
                if (i == idk[j]) {
                    no2 = i + 1;
                    goto jump;
                }
            }
            for (int j = i + 1; j < getn(); j++) {
                if (g[i].getdes() == g[j].getdes()) {
                    idk[z] = j;
                    z++;
                }
            }
            oj << "," << g[i].getdes() << endl;
            oj << "Dr+" << "," << "," << "Cr+" << endl;
            oj << g[i].getdebit() << "," << "," << g[i].getcredit() << endl;
            deb[0] = g[i].getdebit();
            cre[0] = g[i].getcredit();

            for (int j = i + 1; j < getn(); j++) {
                if (g[i].getdes() == g[j].getdes()) {
                    oj << g[j].getdebit() << "," << "," << g[j].getcredit() << endl;
                    deb[x] = g[j].getdebit();
                    cre[x] = g[j].getcredit();
                    x++;
                } else {
                    deb[x] = 0;
                    cre[x] = 0;
                    x++;
                }
            }
            for (int j = 0; j < getn(); j++) {
                sum += deb[j];
                sum -= cre[j];
            }
            if (sum > 0) {
                oj << sum << endl;
            } else {
                oj << "," << "," << sum - sum - sum << endl;
            }
            oj << endl;
            sum = 0;
            x = 1;
            for (int j = 0; j < getn(); j++) {
                deb[j] = 0;
                cre[j] = 0;
            }
        }
        oj.close();
    }
};

class trailbal : public JG {
public:
    trailbal() {
    }
    void create() {
        JG g[getn()];
        int deb[getn()], cre[getn()], sum = 0, z = 0, no2 = 0, x = 1;
        int idk[getn()];
        int totaldeb=0, totalcred=0;
        for (int j = 0; j < getn(); j++) {
            idk[j] = -1;
            deb[j] = 0;
            cre[j] = 0;
        }

        ifstream obj;
        obj.open("gj.txt");
        obj.read((char*)&g, sizeof(g));
        obj.close();

        ofstream oj;
        oj.open("Trial-Balance.csv");
        oj << "," << "Trial" << "," << "Balance" << endl;
        oj << "Des" << "," << "Dr+" << "," << "Cr+" << endl;

    jump:
        for (int i = no2; i < getn(); i++) {
            for (int j = 0; j < getn(); j++) {
                if (i == idk[j]) {
                    no2 = i + 1;
                    goto jump;
                }
            }
            for (int j = i + 1; j < getn(); j++) {
                if (g[i].getdes() == g[j].getdes()) {
                    idk[z] = j;
                    z++;
                }
            }
            deb[0] = g[i].getdebit();
            totaldeb += deb[0];
            cre[0] = g[i].getcredit();
            totalcred += cre[0];
            for (int j = i + 1; j < getn(); j++) {
                if (g[i].getdes() == g[j].getdes()) {
                    deb[x] = g[j].getdebit();
                    totaldeb += deb[x];
                    cre[x] = g[j].getcredit();
                    totalcred += cre[x];
                    x++;
                }
            }
            for (int j = 0; j < getn(); j++) {
                sum += deb[j];
                sum -= cre[j];
            }
            if (sum > 0) {
                oj << g[i].getdes() << "," << sum << endl;
            } else {
                oj << g[i].getdes() << "," << "," << sum - sum - sum << endl;
            }
            sum = 0;
            x = 1;
            for (int j = 0; j < getn(); j++) {
                deb[j] = 0;
                cre[j] = 0;
            }
        }
        oj << "Total" << "," << totaldeb << "," << totalcred << endl;
        oj.close();
    }
};

int main() {
    system("color F1");
    system("mode 650");

    int i = 1;
    string pass;
    accountant f;

    JG g;
    Taccount T;
    trailbal tb;
    g.setn();
    int d, mon, dat;
    string mon1, des1, h;

    cout << "\t\t\t\t\t\t     FINANCIAL ACCOUNTING" << endl << endl;

    for (;;) {
        cout << "1)To create a new account press 1" << endl;
        cout << "2)To log into an existing account press 2" << endl;
        cout << "3)To exit press 3" << endl;
        cin >> i;
        if (!cin) {
            cout << "INVALID RE-ENTER" << endl;
            continue;
        }
        if (i == 1) {
            system("cls");
            cout << "Enter the new password:";
            cin >> pass;
            f = accountant(pass);
            cout << "\nACCOUNT CREATED\n";
            system("cls");
        }
        if (i == 2) {
            cout << "Enter the password:";
            cin >> pass;
            if (f.check(pass) == true) {
                system("cls");
                break;
            } else {
                cout << "\nPASSWORD IS INCORRECT TRY AGAIN\n";
                continue;
            }
        }
        if (i == 3) {
            exit(0);
        }
    }

    for (;;) {
        cout << "\n1)TO make an entry in the journal press 1" << endl;
        cout << "2)To update an entry press 2" << endl;
        cout << "3)To create T-accounts press 3" << endl;
        cout << "4)To create trial balance press 4" << endl;
        cout << "5)To display the general journal press 5" << endl;
        cout << "6)To exit press 6" << endl;
        cin >> i;

        if (!cin) {
            cout << "INVALID RE-ENTER" << endl;
            continue;
        }

        if (i == 1) {
            cout << "enter month:" << endl;
            cin >> mon1;
            g.setmonth(mon1);
            cout << "enter description:" << endl;
            cin >> des1;
            g.setdes(des1);
            cout << "enter date:" << endl;
            cin >> dat;
            g.setdate(dat);
            g.cord();
            f.initializefile(g);
            system("cls");
        }

        if (i == 2) {
            cout << "enter the entry no you want to edit:" << endl;
            cin >> d;
            cout << "enter month:" << endl;
            cin >> mon1;
            g.setmonth(mon1);
            cout << "enter description:" << endl;
            cin >> des1;
            g.setdes(des1);
            cout << "enter date:" << endl;
            cin >> dat;
            g.setdate(dat);
            g.cord();
            f.updatefile(d, g);
            system("cls");
        }

        if (i == 3) {
            T.create();
            cout << "\nTACCOUNTS CREATED\n";
            system("cls");
        }

        if (i == 4) {
            tb.create();
            cout << "\nTRIAL BALANCE CREATED\n";
            system("cls");
        }

        if (i == 5) {
            f.display();
        }

        if (i == 6) {
            exit(0);
        }
    }

    return 0;
}

