#include <iostream>
#include <fstream>  // файловые потоки
#include <iomanip>  // манипуляторы
#include <string>
#include <algorithm> // алгоритмические ф-ции STL
#include <time.h>
using namespace std;
#define RAND(Min,Max)  (rand()%((Max)-(Min)+1)+(Min))
struct LC { LC() { system("chcp 1251 > nul"); srand(time(0)); }~LC() { cin.get(); cin.get(); } } _;


// Используя механизм множественного наследования разработайте класс "Автомобиль".
// Должны быть базовые классы "Колеса", "Двигатель", "Двери" и т.д., от которых порождается класс "Автомобиль".
class Wheels // класс "Колеса"
{
private:
    float Radius;
    string Manufacturer;    // производитель
public:
    Wheels() : Radius(), Manufacturer("unknown") {}
    Wheels(float radius, string manuf) : Radius(radius), Manufacturer(manuf) {}

    float GetRadius()        const { return Radius; }
    string GetManufacturer() const { return Manufacturer; }

    void SetRadius(float val) { Radius = val; }
    void SetManufacturer(string val) { Manufacturer = val; }

    friend ostream& operator<< (ostream& os, const Wheels& obj)
    {
        os << typeid(obj).name() << endl;
        os << "Radius: " << obj.GetRadius() << endl;
        os << "Manufacturer: " << obj.GetManufacturer() << endl;
        return os;
    }

    friend istream& operator>> (istream& is, Wheels& obj)
    {
        cout << typeid(obj).name() << ":" << endl;
        float tmp; string tmp2;

        cout << "Enter radius: ";
        (is >> tmp).ignore();
        obj.SetRadius(tmp);

        cout << "Enter manufacturer: ";
        getline(is, tmp2);
        obj.SetManufacturer(tmp2);
        cout << "--------------------------------------------------\n";

        return is;
    }
};

class Engine // класс "Двигатель"
{
private:
    float Volume;
    string Fuel;
public:
    Engine() : Volume(), Fuel("unknown") {}
    Engine(float volume, string fuel) : Volume(volume), Fuel(fuel) {}

    float  GetVolume() const { return Volume; }
    string GetFuel()   const { return Fuel; }

    void SetVolume(float val) { Volume = val; }
    void SetFuel(string val) { Fuel = val; }

    friend ostream& operator<< (ostream& os, const Engine& obj)
    {
        os << typeid(obj).name() << endl;
        os << "Volume: " << obj.GetVolume() << endl;
        os << "Fuel: " << obj.GetFuel() << endl;
        return os;
    }

    friend istream& operator>> (istream& is, Engine& obj)
    {
        cout << typeid(obj).name() << ":" << endl;
        float tmp; string tmp2;

        cout << "Enter volume: ";
        (is >> tmp).ignore();
        obj.SetVolume(tmp);

        cout << "Enter fuel: ";
        getline(is, tmp2);
        obj.SetFuel(tmp2);
        cout << "--------------------------------------------------\n";

        return is;
    }
};

class Doors // класс "Дверь"
{
private:
    int Count;
    string Color;
public:
    Doors() : Count(), Color("unknown") {}
    Doors(int count, string color) : Count(count), Color(color) {}

    int    GetCount() const { return Count; }
    string GetColor() const { return Color; }

    void SetCount(int val) { Count = val; }
    void SetColor(string val) { Color = val; }

    friend ostream& operator<< (ostream& os, const Doors& obj)
    {
        os << typeid(obj).name() << endl;
        cout << "Count: " << obj.GetCount() << endl;
        cout << "Color: " << obj.GetColor() << endl;
        return os;
    }

    friend istream& operator>> (istream& is, Doors& obj)
    {
        cout << typeid(obj).name() << ":" << endl;
        int tmp; string tmp2;

        cout << "Enter count: ";
        (is >> tmp).ignore();
        obj.SetCount(tmp);

        cout << "Enter color: ";
        getline(is, tmp2);
        obj.SetColor(tmp2);
        cout << "--------------------------------------------------\n";
        return is;
    }
};


class Automobile : virtual public Wheels, virtual public Engine, virtual public Doors
{
private:
    string Name;
public:
    Automobile() : Name("unknown"), Wheels(), Engine(), Doors() {}
    Automobile(Wheels wheels, Engine engine, Doors doors) : Wheels(wheels), Engine(engine), Doors(doors)
    {
        // класс "Колеса"
        SetRadius(wheels.GetRadius());
        SetManufacturer(wheels.GetManufacturer());

        // класс "Двигатель"
        SetVolume(engine.GetVolume());
        SetFuel(engine.GetFuel());

        // класс "Двери"
        SetCount(doors.GetCount());
        SetColor(doors.GetColor());
    }

    string GetName()   const { return Name; }
    void SetName(string val) { Name = val; }

    friend ostream& operator<< (ostream& os, const Automobile& obj)
    {
        os << typeid(obj).name() << endl;
        os << "Name: " << obj.GetName() << "\n\n";
        os << (Wheels&)obj << endl;
        os << (Engine&)obj << endl;
        os << (Doors&)obj << endl;
        return os;
    }

    friend istream& operator>> (istream& is, Automobile& obj)
    {
        cout << "Enter info for " << typeid(obj).name() << ":" << endl;

        string tmp;
        cout << "Enter name: ";
        getline(is, tmp);
        obj.SetName(tmp);
        cout << "--------------------------------------------------\n";

        is >> (Wheels&)obj >> (Engine&)obj >> (Doors&)obj;
        return is;
    }
};

int main()
{
    Automobile automobile;
    cin >> automobile;
    cout << automobile;
}