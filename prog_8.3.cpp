
#include<iostream>
using namespace std;
class animal {
    public:
    virtual void speak() const = 0;
    virtual ~animal() { cout<<"~animal\n";}
};
class dog : public animal {
    public:
    void speak() const override { cout<<"woof\n";}
    ~dog() { cout<<"~dog\n";}
};
int main()
{
    animal *a = new dog();
    if(dog *d  = dynamic_cast<dog*>(a)) {
        cout<<"downcast ok ->";
        d->speak();

    }
    delete a;
    return 0;
}
