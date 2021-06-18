1、C语言和C++有什么区别？

2、C++的访问控制权限  
    
    public: 公有成员，对于类的对象都是可见的   
    protected: 受保护成员，对于类的对象是不可见的；对成员和友元可见，对子类的成员可见
    private: 私有成员，对于类的对象而言是不可见的；对成员和友元可见
    
    例子：
   
    ` 
      class Base {
       public :
	      int age;
       private:
	      int height;
       protected:
	      int weight;
      };

      int main() {
	      Base B; 
	      B.age = 10;
	      b.height = 100; //报错  对象只能访问public成员
	      B.weight = 1000;//报错  对象只能访问public成员

	      return 0;
      }   
   
    `
    继承访问权限：  
    若继承方式是public，基类成员在派生类中的访问权限保持不变，也就是说，基类中的成员访问权限，在派生类中仍然保持原来的访问权限；  
    若继承方式是private，基类所有成员在派生类中的访问权限都会变为私有(private)权限；  
    若继承方式是protected，基类的公有成员和保护成员在派生类中的访问权限都会变为保护(protected)权限，私有成员在派生类中的访问权限仍然是私有(private)权限。
    
    例子：  
    `
    class Derived :public Base {
    public :
	    int a;
	    void run() {
		    age = 10;
		    height = 100; //报错  子类只能访问父类的public和protected
		    weight = 1000;
	    }
    };

    int main() {
	    Derived A;
	    A.age = 10; 
	    A.height = 100;//报错   对象只能访问public成员
	    A.weight = 1000;//报错  对象只能访问public成员
	    return 0;
    }

    `
    对于protected 和 private 继承，由于会将public成员全部改为protected或private，所以A.age=10 也会报错。
    在Derived中的表现是一样的，但是对于Derived的子类，则表现出差异。


3、struct和class有什么区别？
    
    C++中的struct有哪些特性？与class一样，
    1、可以包含成员函数
    2、可以继承
    3、可以实现多态
    4、内存布局一样，成员函数与数据成员是分离的，虚函数在对象或结构体的开始增加虚表指针
    区别在于：
    1、但是struct的默认的继承访问权限是：public ; class 的默认的继承访问权限是：private
    
4、extern "C"的作用？  
    
    extern 链接指示符, for example:  
    extern "C"{  
        int func(int a);  
    }  
    C++编译器会将extern "C"的大括号内部的代码当作C语言代码处理。C++的名称修饰机制(混淆机制)将不会起作用。


5、函数重载(overload)和覆盖(override)有什么区别?
    
    函数重载：是指允许存在多个同名函数，只要这些函数的参数个数或者参数类型不同。如构造方法的重载
    函数覆盖：是指子类的函数继承于父类，但是其实现方式不同，在通过子类创建的实例对象调用这个方法时，将调用子类中定义的方法，这相当于把父类中定义的那个完全相同的方法给覆盖掉了。如果父类的方法是private类型，那么，子类则不存在覆盖的限制，相当于子类中增加了一个全新的方法

6、谈一谈你对多态的理解，运行时多态的实现原理是什么？

    C++ 多态意味着调用成员函数时，会根据调用函数的对象的类型来执行不同的函数，即指向基类的指针在运行时会根据具体指向的派生类调用相应的函数
    例子：
    `
    class Animal {
    public:
	    int age;
	    int weight;
	    virtual void run() {
		    printf(" Animal run ...\n");
	    }
	    void eat() {
		    printf("Animal eat ...\n");
	    }
    };

    class Pig :public Animal {
	public:
        void run() {
	 	    printf("too fat to run ...\n");
	    }
	    void eat() {
		    printf("eat too much \n");
	    }
    };

    int main() {  
        Animal *a = new Pig;
	    a->eat();
	    a->run();
	    return 0;
    }
    `
    输出：
    Animal eat ...
    too fat to run ...
    
    实现原理：虚函数

7、对虚函数机制的理解，单继承、多继承、虚继承条件下虚函数表的结构。


8、如果虚函数是有效的，那为什么不把所有函数设为虚函数？
构造函数可以是虚函数吗？析构函数可以是虚函数吗？什么场景需要用到纯虚函数？纯虚函数的作用是什么？
    
    1、构造函数不能是虚函数
         a、虚函数对应一个vtable，是存储在对象的内存空间的。问题来了，如果构造函数是虚的，就需要通过 vtable来调用，可是对象还没有实例化，也就内存空间还没有，怎么找vtable呢？所以构造函数不能是虚函数。
         b、虚函数的作用在于通过父类的指针或者引用来调用它的时候能够变成调用子类的那个成员函数。而构造函数是在创建对象时自动调用的，不可能通过父类的指针或者引用去调用，因此也就规定构造函数不能是虚函数。
    2、析构函数应该为虚函数
        我们往往通过基类的指针来销毁对象。这时候如果析构函数不是虚函数，就不能正确识别对象类型从而不能正确调用析构函数。
    3、inline不能是虚函数
        内联函数是为了在代码中直接展开，减少函数调用花费的代价；虚函数在运行时才能动态绑定函数
    4、C++不支持友元函数为虚函数
        C++不支持友元函数的继承，对于没有继承特性的函数没有虚函数的说法
    5、C++不支持静态成员函数为虚函数
       静态成员函数对于每个类来说只有一份代码，所有的对象都共享这一份代码，他也没有要动态邦定的必要性。

    纯虚函数：在基类中不能对虚函数给出有意义的实现，而把它声明为纯虚函数，它的实现留给派生类去实现

9、了解RAII吗？介绍一下？

    RAII是Resource Acquisition Is Initialization的缩写，意为“资源获取即初始化”。其核心是把资源和对象的生命周期绑定，对象创建获取资源，对象销毁释放资源。
    一般通过使用局部对象管理资源，因为局部对象在代码块结束后自动销毁。

10、类的大小怎么计算？
   
    1、空类的大小为1个字节
    2、与类大小有关的因素：普通成员变量，虚函数，继承（单一继承，多重继承，重复继承，虚拟继承）？？？
      与类大小无关的因素：静态成员变量，静态成员函数及普通成员函数
    
11、内存对齐规则
     1.基本类型的对齐值就是其sizeof值;
     2.class和struct的对齐值是其成员的最大对齐值;
     3.编译器可以设置一个最大对齐值，怎么类型的实际对齐值是该类型的对齐值与默认对齐值取最小值得来。
12、volatile关键字的作用 
     
    volatile 修饰符的主要目的是提示编译器，该对象的值可能在编译器未监测到的情况下被改变，因此编译器不能武断地对引用这些对象的代码作优化处理
13、如何实现一个线程池？

14、了解各种强制类型转换的原理及使用？
    
    一、隐式转换
       `
           short a = 200;
           int b = a;  
       `
       从一些较小的整数类型(如short)转换为int, 或从float转换为double称为提升，并且可以保证在目标类型中产生完全相同的值。 但是算术类型之间的其他转换可能并不总是能够精确地表示相同的值。
       1、如果将负整数值转换为无符号类型，则结果值对应于其2进制补码的按位表示形式。
         如：
         `
          int a = -1;
          int b = -2;
          unsigned int c = a;  //c = 4294967295
          unsigned int d = b;  //b = 4294967294
         ` 
       2、bool类型的转换，false对应于NULL或者0值，True对应于其他值；
       3、float转int，小数部分会被截掉。如果结果超出类型可表示的值的范围，则转换将导致undefined behavior。
       
       对于非基本类型，数组和函数隐式转换为指针，并且指针通常允许进行以下转换：
       1、NULL指针可以转换为任意类型的指针
       2、任意类型的指针可以转换为void指针
       3、指针转换：可以将指向派生类的指针转换为可访问且明确的基类的指针，而无需修改其const或volatile限定条件。
    二、类的隐式转换
       单参数构造函数：允许从特定类型进行隐式转换用于初始化对象。
       赋值运算符：允许从特定类型赋值进行隐式转换。
       类型转换运算符：允许隐式转换为特定类型。
    三、关键字 explicit
       `
       class A {
          int len;
       public:
          A(int len) {}
       };

       int main(void) {
          A a = 10;
          return 0;
       }
       `
       A a = 10； 是允许的，这是因为当构造函数只有一个参数时，A a = 10；相当于 A a(10);
       但是如果构造函数加上 explicit 关键字，这该情况则不允许了。explicit关键字的作用就是防止类构造函数的隐式自动转换.
     四、显示类型转换
     1、dynamic_cast
     2、static_cast
     3、reinterpret_cast
     4、const_cast
    https://blog.csdn.net/qq_29996285/article/details/86508684
     五、typeid
     typeid (expression) 检查表达式的类型
     `
      // typeid, polymorphic class
      #include <iostream>
      #include <typeinfo>
      #include <exception>
      using namespace std;

      class Base { virtual void f(){} };
      class Derived : public Base {};

      int main () {
         try {
             Base* a = new Base;
             Base* b = new Derived;
             cout << "a is: " << typeid(a).name() << '\n';
             cout << "b is: " << typeid(b).name() << '\n';
             cout << "*a is: " << typeid(*a).name() << '\n';
             cout << "*b is: " << typeid(*b).name() << '\n';
         } catch (exception& e) { cout << "Exception: " << e.what() << '\n'; }
         return 0;
       }
      `
      输出：
       a is: class Base *
       b is: class Base *
       *a is: class Base
       *b is: class Derived
       
15、指针和引用有什么区别？什么情况下用指针，什么情况下用引用？
    引用主要被用作函数的形参
    1、引用必须被初始化
    2、在汇编层面，引用和指针是一样的。引用所具有的特性是编译器在编译时的规范，而编译后指针和引用完全没有区别


    指针是一个真正的存在的对象，它和 int、double、char……没有区别，都是储存一个值的对象，指针储存着它所指向的对象的内存地址；
    而引用则是语法上的概念，作用是一个对象的别名，用于绑定到一个对象上，对引用的操作等于对它所绑定的对象的操作。 
    在内存上储存对象的内存地址，是编译器实现引用的一种常用的方式，但是，编译器并不一定总是会为引用分配内存空间——就像上面所说的，
    对指针的解引用、对数组元素的引用、甚至是对对象本身的引用，都是对引用在操作。这时候的引用是不会有单独的内存空间为它储存地址的。

    作者：Timothy Liu
    链接：https://www.zhihu.com/question/37608201/answer/1893663654

16、new和malloc有什么区别？malloc的内存可以用delete释放吗？malloc出来20字节内存，为什么free不需要传入20呢，不会产生内存泄漏吗？
new[]和delete[]一定要配对使用吗？
    
    new的功能是在堆区新建一个对象，并返回该对象的指针。所谓的【新建对象】的意思就是，将调用该类的构造函数，因为如果不构造的话，就不能称之为一个对象。
    而malloc只是机械的分配一块内存，如果用mallco在堆区创建一个对象的话，是不会调用构造函数的。严格说来用malloc不能算是新建了一个对象，只能说是分配了一块与该类对象匹配的内存而已，然后强行把它解释为【这是一个对象】，按这个逻辑来，也不存在构造函数什么事。
    同样的，用delete去释放一个堆区的对象，会调用该对象的析构函数。用free去释放一个堆区的对象，不会调用该对象的析构函数。

    理论上malloc的内存可以用delete释放。但是new的内存不能用free释放，因为free不会调用对象的析构函数。
 
    malloc会记住内存的大小。
    当调用malloc(size)时，实际分配的内存大小大于size字节，这是因为在分配的内存区域头部有类似于
    struct control_block {
        unsigned size;
        int used;
    };
    这样的一个结构，如果malloc函数内部得到的内存区域的首地址为void *p,那么它返回给你的就是p + sizeof(control_block)，
    而调用free(q)的时候，该函数把p减去sizeof(control_block)，然后就可以根据((control_blcok*)q)->size得到要释放的内存区域的大小。
    这也就是为什么free只能用来释放malloc分配的内存，如果用于释放其他的内存，会发生未知的错误。

realloc?


17、了解auto和decltype吗？
    
    decltype并不会实际计算表达式的值，编译器分析表达式并得到它的类型。
    函数调用也算一种表达式，因此不必担心在使用decltype时真正的执行了函数

18、谈一谈你对左值和右值的了解，了解左值引用和右值引用吗？ 
了解移动语义和完美转发吗？

19、了解列表初始化吗？

平时会用到function、bind、lambda吗，都什么场景下会用到？

对C++11的mutex和RAII lock有过了解吗？

对C++11的智能指针了解多少，可以自己实现一个智能指针吗？

enum 和 enum class有什么区别？

一般什么情况下会出现内存泄漏？

怎么用C++在编码层面尽量避免内存泄漏。

unique_ptr如何转换所有权？

谈一谈你对面向对象的理解什么场景下使用继承方式，什么场景下使用组合？

STL系列C++直接使用数组好还是使用std::array好？std::array是怎么实现的？

std::vector最大的特点是什么？它的内部是怎么实现的？resize和reserve的区别是什么？clear是怎么实现的？

deque的底层数据结构是什么？它的内部是怎么实现的？

map和unordered_map有什么区别？分别在什么场景下使用？

list的使用场景？std::find可以传入list对应的迭代器吗？

string的常用函数


const的作用有哪些，谈一谈你对const的理解？

描述char*、const char*、char* const、const char* const的区别？

指针常量和常量指针有什么区别？

static的作用是什么，什么情况下用到static？

全局变量与局部变量的区别？宏定义的作用是什么？

内存对齐的概念？为什么会有内存对齐？

inline 内联函数的特点有哪些？它的优缺点是什么？

如何用C 实现 C++ 的面向对象特性（封装、继承、多态）

memcpy怎么实现让它效率更高？

typedef和define有什么区别？

extern有什么作用，extern C有什么作用？

如何避免野指针？

如何计算结构体长度？

sizeof和strlen有什么区别？

知道条件变量吗？条件变量为什么要和锁配合使用？



   
        