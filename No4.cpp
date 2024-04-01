//在类外访问类的成员函数时  type Class::Get();即要在函数类型之后声明该成员函数所在的类名
//对象指针访问类成员：对象名->成员名;
//对象引用访问类的成员：已知一个Student类，a为该类型的一个对象，则访问a的Get()函数 a.Get();访问a的数据成员score：a.score(一般不能通过直接访问来访问私有有权限的成员)



//对象的赋值：
//1.前提是必须是同类对象才可以相互赋值
//2.在类中动态分配的内存，默认的赋值运算符不会赋值，因为默认赋值函数只是浅拷贝，如果要实现深拷贝就要重载赋值运算符；
//3.若重载了赋值运算符，最好逐一赋值所有的数据成员；

//对象的复制：通过复制构造函数来实现（或称为拷贝构造函数）分为默认拷贝构造函数与自己提供的拷贝构造函数；
//【默认拷贝构造函数不能对动态分配的数据复制，是浅拷贝】
//复制构造函数的声明已知一个类Date，则
           Date(int year,int month,int day);//构造函数；
           Date(const Date& rhs);//拷贝构造函数；
//拷贝构造函数的定义：
      Date::Date(const Date& rhs)
      {
        m_year=rhs.m_year;
        m_month=rhs.m_month;
        m_day=rhs.m_day;
      }
//在main函数中调用拷贝构造函数：
int main()
{
    Date d1(2003,12,18);
    Date d2(d1);
    return 0;
}



//const对象和const成员函数
//const对象 任何想要修改const对象的行为都将编译出错；对象不可修改指的是不可修改类中的任何数据成员，无法调用const对象的任何成员函数（即使成员函数没有对对象作出修改也无法调用）
//const成员函数，为了让const对象可以获得数据成员，允许const对象调用const成员函数。
//const成员函数的声明与定义是在函数首部最后添加const关键字；
          class Date
          {
                private:
                        int m_year,m_month,int day;
                public:
                    Date(int year,int month,int day)//构造函数
                    void Show();
                    int getyear();//获取成员函数；
                    int getyear() const;//const 成员函数；
                    int getmonth();
          };
          int Date::getyear()
          {
            return m_year;
          }
          int Date::getyear() const
          {
            return m_year;
          }
          int Date::getmonth()
          {
            return m_month;
          }
          int main()
          {
            Date d1(2003,12,18);
            const Date d2(2004,10,02);
            cout<<d1.getyear()<<endl;
            cout<<d2.getyear()<<endl;//函数重载，const对象只调用const函数；
            cout<<d2.getmonth()<<endl;//错误，const对象不能调用非const函数
          }




//类作为函数参数
//和基本函数类型也一样，有三种传递方式：
//（1）类对象（按值传递）（2）类对象指针（按地址传递）（3）类对象引用（按引用传递）；
//同时，由于const可以修饰对象，所以类对象作为函数参数一共6种可能的结果：
//（1）void func(T t);(2)void func(const T t);这两种情况使用类对象作为参数，实际传递进入函数的是实参的副本，所以无法修改实参，且（2）对副本也无法修改；{函数值传递实参无法被修改，只有通过引用传递，实参才可以被修改}；
//(3)void func(T&t);(4)void func(const T&t);//使用类对象作为参数，可以实现对实参修改    （4）对实参的修改是禁止的，与（1）等效，通常使用（4），效率高。
//(5)void func(T*p);(6)void func(const T*p);//传入的是实参的地址，所以可以对实参进行修改。（6）对实参修改进行了禁止，所以（6）与（1）等效，通常使用（1）；




//动态创建删除对象
//与动态创建、删除一般数据类型一样，唯一的不同是动态创建对象两个运算：首先分配内存，再调用构造函数初始化对象。
//动态删除对象也两个运算：首先调用析构函数释放对象用到的资源，然后释放对象所占的内存；


//static类成员（作为公共的部分，供该类的所有对象进行读写的成员）可以说static成员是作用在该类域上的全局变量；
//分为static数据成员和static成员函数
//类的public的static数据成员，在类外也可以访问（可以用对象访问，也可以用类名：：（static成员）进行访问）
//类的private的static成员在类外也没有访问权限，可以通过成员函数进行访问
//？？当未创建类的对象时，无法调用一般的成员函数，如何访问类的private的static成员？？：使用static成员函数
//static成员函数只能对static数据成员进行操作；
class Car
{
    private:
          static int startYear;
          static int carCount;
          static int currentYear;
    public:
        Car();
        static void setCurrentYear(int year)
        {
            currentYear=year;
        }
        static int getCount()
        {
            return count;
        }
        static float average();
}
int Car::carCount=0;
int Car::startYear=2003;
int Car::currentYear=2023;
float Car::average()
{
    float aver=(float)carCount/(currentYear-startYear+1);
    return aver;
}
int main()
{
    Car a;
    a.startYear=12;(在私有属性内，目前无法去修改。)
}









//友元函数和友元类
//关键字：friend 
//（1）在类声明中，函数原型前加关键字friend，该函数就声明为该类的友元函数，该函数可以访问该类的私有公有数据成员，该函数可以是全局函数或者其他类的成员函数；
//（2）在类声明中，在其他类前加上friend关键字，就声明为该类的友元类，可以访问该类的私有成员公有成员。
注意：（1）友元不受访问限制，友元的声明可以在类的任何部分；
    （2）友元函数不是该类自己的成员函数；
    （3）友元是授予其他函数或者类访问权限，其具有不对称性；
    （4）友元类不可传递。





//组合：将一个类作为其他类的成员的组合方式（比如在自定义类内使用string类）
//主类对象与子对象构造函数创建时间顺序问题：（1）其它类成员先于宿主对象调用构造函数（2）若包含多个其它类对象，则按先后顺序调用构造函数。
//（3）其他类对象的构造函数只能在参数初始化列表中调用（4）如果其他类有默认构造函数，可以不用显式调用。
class Date{
    private:
        int myear;
        int mmonth;
        int day;
    public:
        Date(int nyear,int nmonth,int nday);
};
class Time
{
    private:
            int mhour;
            int mmin;
    public:
          Time(int nhour,int nmin);
};
class Memo
{
    private:
            string mstrmemo;
            Date mdate;
            Time mtime;
    public:
         Memo(const string strmemo,int year,int montj,int day,int hour,int min);
         {
             mstrmemo(strmemo);
             Date(year,mon,day);
             Time(hour,min);
         }
};