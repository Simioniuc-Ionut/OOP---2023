#include <iostream>
#include <string>
using namespace std;

enum Type { prieten, cunoscut, coleg };

class exceptie : public exception {
  public:
    const char* what() const noexcept override {
        return "Nu s-a gasit niciun contact cu acel nume";
    }
};

class Contact {
  public:
    virtual ~Contact() {
    }
    virtual string Nume() = 0;
    virtual Type GetType() const = 0;
};

class Prieten : public Contact {
  private:
    string nume;
    struct data {
        int an;
        int luna;
        int zi;
    };
    data data;
    string NrTelefon;
    string Adresa;

  public:
    Type GetType() const override {
        return Type::prieten;
    }

    Prieten(const Prieten& other) {
        nume = other.nume;
        NrTelefon = other.NrTelefon;
        data = other.data;
        Adresa = other.Adresa;
    }

    Prieten() {
        data.an = 0;
        data.zi = 0;
        data.luna = 0;
        NrTelefon = "";
        nume = "";
        Adresa = "";
    }

    string Nume() {
        return nume;
    }

    void SetNume(string nume) {
        this->nume = nume;
    }

    void SetNrTelefon(string nr) {
        NrTelefon = nr;
    }

    void SetData(int an, int luna, int zi) {
        data.an = an;
        data.zi = zi;
        data.luna = luna;
    }

    void SetAdresa(string adresa) {
        Adresa = adresa;
    }
};

class Cunoscut : public Contact {
  private:
    string nume;
    string NrTelefon;

  public:
    Type GetType() const override {
        return Type::cunoscut;
    }

    Cunoscut() : nume(""), NrTelefon("") {
    }

    string Nume() {
        return nume;
    }

    void SetNume(string nume) {
        this->nume = nume;
    }

    void SetNrTelefon(string nr) {
        NrTelefon = nr;
    }
};

class Coleg : public Contact {
  private:
    string nume;
    string NrTelefon;
    string firma;
    string Adresa;

  public:
    Type GetType() const override {
        return Type::coleg;
    }

    Coleg() : nume(""), NrTelefon(""), firma(""), Adresa("") {
    }

    string Nume() {
        return nume;
    }

    void SetNume(string nume) {
        this->nume = nume;
    }

    void SetNrTelefon(string nr) {
        NrTelefon = nr;
    }

    void SetFirma(string firma) {
        this->firma = firma;
    }

    void SetAdresa(string adresa) {
        Adresa = adresa;
    }
};

class Agenda {
  private:
    Contact** contacte;
    int index;
    int NrPrieteni;
  public:
    Agenda() {
        index = 0;
        NrPrieteni = 0;
        contacte = new Contact*[100];
    }

    ~Agenda() {
        delete[] contacte;
    }

    Contact& CautaNume(string nume) {
        for (int i = 0; i < index; i++) {
            if (contacte[i]->Nume() == nume)
                return *contacte[i];
        }
        throw exceptie();
    }
    int GetNrPrieteni() {
        return NrPrieteni;
    }
    void StergeNume(string nume) {
        for (int i = 0; i < index; i++) {
            if (contacte[i]->Nume() == nume) {
                while (i < index - 1) {
                    contacte[i] = contacte[i + 1];
                    i++;
                }
                index--;
                break;
            }
        }
    }

    void adaugaContact(Contact* contact) {
        contacte[index] = contact;
        index++;
    }

    Contact** GetPrieteni() {
        Contact** prieteni = new Contact*[100];
        for (int i = 0; i < index; i++) {
            if (contacte[i]->GetType() == Type::prieten) {
                prieteni[NrPrieteni] = contacte[i];
                NrPrieteni++;
            }
        }
        return prieteni;
    }

    void print() {
        for (int i = 0; i < index; i++)
            cout << "Contact: " << contacte[i]->GetType() << " Numele: " << contacte[i]->Nume() << endl;
    }
};

int main() {
    Agenda agenda;

    // Adăugare contacte
    Prieten prieten1;
    prieten1.SetNume("John");
    prieten1.SetData(1990, 8, 15);
    prieten1.SetNrTelefon("1234567890");
    prieten1.SetAdresa("Strada X, Nr. 10");

    Cunoscut cunoscut1;
    cunoscut1.SetNume("Alice");
    cunoscut1.SetNrTelefon("9876543210");

    Coleg coleg1;
    coleg1.SetNume("Bob");
    coleg1.SetNrTelefon("5555555555");
    coleg1.SetFirma("ABC Company");
    coleg1.SetAdresa("Strada Y, Nr. 20");

    agenda.adaugaContact(&prieten1);
    agenda.adaugaContact(&cunoscut1);
    agenda.adaugaContact(&coleg1);
    agenda.print();
    cout << endl;
    // Căutare după nume
    string numeCautat = "Alice";
    try {
        Contact& contactCautat = agenda.CautaNume(numeCautat);
        cout << "Contactul cautat: " << contactCautat.Nume() << endl;
    } catch (exceptie& e) {
        cout << "Exceptie: " << e.what() << endl;
    }

    // Stergere contact
    string numeSters = "Bob";
    agenda.StergeNume(numeSters);

     agenda.print();
    // Obținere lista de prieteni
    Contact** prieteni = agenda.GetPrieteni();
    cout << "Lista de prieteni:" << endl;
    for (int i = 0; i < agenda.GetNrPrieteni(); i++) {
        cout << prieteni[i]->Nume() << endl;
    }

    
    // Eliberare memorie
     delete[] prieteni;

    return 0;
}