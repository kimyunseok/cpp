/*
* OOP - 얕은 복사와 깊은 복사
*/
#include <iostream>
using namespace std;

class MyObject {
public:
    string* name;
    int age;

    //기본 생성자
    MyObject(int age, string name) {
        this->name = new string(name);
        this->age = age;
    }

    //기본 복사 생성자와 같음. 레퍼런스로 만들지 않으면 복사생
    //MyObject(const MyObject &myObj) {
    //    cout << "얕은복사 생성자 호출" << "\n";
    //    this->name = myObj.name;
    //    this->age = myObj.age;
    //}

    //깊은 복사 생성자.
    MyObject(const MyObject &myObj) {
        cout << "깊은복사 생성자 호출" << "\n";
        this->name = new string(*myObj.name);
        this->age = myObj.age;
    }

    //소멸자
    ~MyObject() {
        cout << *name << "의 소멸자 호출" << "\n";
        delete name;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    MyObject obj1(42, "Mike");
    MyObject obj2(obj1);
    //MyObject obj2 = obj1;

    *obj2.name = "John";
    obj2.age = 36;

    cout << "obj1's name's addr:" << &(*obj1.name) << "\n";
    cout << "obj2's name's addr:" << &(*obj2.name) << "\n";

    cout << "obj1's name:" << *obj1.name << "\n";
    cout << "obj2's name:" << *obj2.name << "\n";

    cout << "obj1's age:" << obj1.age << "\n";
    cout << "obj2's age:" << obj2.age << "\n";

    return 0;
}