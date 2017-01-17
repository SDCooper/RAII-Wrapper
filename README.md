# RAII

RAII is a simple set of four headers which will wrap up a non-RAII type and give it a meaningful constructor.

RAII stands for Resource Allocation Is Initialision. In this context this refers to the idea that it is better to make proper, meaningful constructors and destructors instead of create and destroy methods.

The motivation for this comes from the engine we use at my present company. It may have been a good idea at the time for whatever reason, the vast majority of classes in this engine use the constructor simply for initialising all the variables to zero. This includes the classes which do no heavy lifting (e.g loading of assets) at all. It has become standard across games and for new classes in the engine to always have a creator and a destroy method and make virtually no meaningful use of the constructor and destructor. This leads to several problems:

* Needing to write boilerplate code for every new class with an Initialised flag and error checking for whether the class has already been initialised, to prevent double initialisation (memory leaks) or double destruction (heap corruption). With RAII, there is little need to do this and no need at all using smart pointers in the standard library.
* Use of C++ smart pointers is rendered a pointless endeavor (excuse the pun) because the constructor and destructor are totally decoupled from the actual lifetime of the assets they control. So unique_ptr offers no additional benefit despite being a hugely useful class.
* More boilerplate of having to call Create() and Destroy() on every object even if the constructor takes no parameters. Having to call Destroy() when the object simply going out of scope would do.
* Lack of exception safety, if an operation throws before Destroy() is called, that memory has leaked.
* Unnecessarily easy to call a method of an object before its Create() has been called. This was sometimes solved by every method checking against an Initialised flag and returning early if it was false. This was unwieldy, inconsistently applied, error prone and would lead to poorly defined behaviour.
* If engine-side classes are not RAII it is difficult to take advantage of RAII game-side, as explicit Create and Destroy calls must still be made in game side classes. A major benefit to RAII is that constructors are mandatorily called for all members which do not have a default constructor, and destructors are automatically called for you.
* While rarely a problem in practice, it is best to destroy in the opposite order to which you create. However, explicitly calling Create and Destroy often lead to them being called in the same order or in some random order, which is not best practice.
* Classes in the engine were inconsistent in the name of the create function. Programmers must remember for each class whether they have to Create, Init, Open, and whether they have to Destroy, Close, or whatever. There were also no clear pairs. Constructors and destructors are uniform.

We had effectively built ourselves into a situation where every object had to be allocated with new and deallocated with delete, except it was less manageable and more error prone, and when I asked around nobody was able to explain why this choice had been made in the first place, let alone why it should continue as standard.

I requested and was granted some extra flexibility to experiment with some Modern C++ (C++11/14) features, as most people at work were not too aware of them. I recognised that move semantics and unique_ptr are a major innovation in the language and needed to show the team how useful these were, but I did not have write access to the engine as this is managed by a separate team. My solution was to create a set of template wrappers which grant RAII-like features to our engine by creating an RAII_Wrapper class which takes three template arguments:

1. The type to be wrapped
2. A struct representing the creation method (e.g whether to call a function called Init, Create or Open, etc.)
3. A struct representing the destruction method (e.g whether to call Destroy or Close, etc.)

The final two structs are defined using a clever use of the preprocessor in raii_creator.h and raii_destructor.h which means that to declare a new type of creation or destruction method, only one line is needed. While a slightly unorthodox approach, it does reduce boilerplate code which I see as one of the (relatively few) legitimate uses of the preprocessor in modern C++. It was then just a case of adding the five or six different words we use for creating, the four or five different words we use for destroying, and making some header files with a using or typedef directive to create new types which forward their constructors' arguments to their creators.

It cannot be stressed how much these simple four headers made development with our engine quick and easy. The only drawback is that it was difficult for Visual Studio's prompt to understand, so you had to navigate to the original header (e.g legacy/Car.h rather than raii/RCar.h) if you were not sure on the exact order or type of parameters required, as the pop up box would only show `RAII_Template(Args&&)`, but this does not happen often once you are experienced with the engine, whereas the problems it tackles (listed above) happen all the time. There is often about half a week of development time dedicated to finding and fixing memory leaks. The game I was working on had none whatsoever, and it's not because I was more careful than my coworkers, but because I used this.

I now recommend to all my coworkers that they make use of the version of these wrappers that was developed at my workplace.

Note also that I came up with this methodology and wrote the header files in my own time, and reimplemented based on the same idea at work. I am not publishing code which does not belong to me.

## About this package

This package comes with an example of the legacy library mentioned above, except obviously with no reference to the actual libraries we use. Two classes are provided - Car and FileStream, with their own creator and destroyer methods. These use the typical style that we have developed at work, with a constructor and destructor that do nothing but set some pointers to null and some integers to zero, and a creator function that does the heavy lifting. Note the unwieldy use of an Initialised flag and that it's checked in FileStream::Write but not in Car::Drive. Please also note that these classes were meant as a demonstration of a typical class in our library, not of the way I would write a class of my own.

It comes with a standard makefile, a simple

~~~~
$ make
$ ./raii_example
~~~~

should run the main function found in tests.cpp. Note the two functions, non_raii() to give an example of how the legacy classes work on their own, and then raii() to do the same thing with constructors and destructors.

Note that your compiler will have to support the C++11 standard. For example I compiled this using G++ 6.3.1 on Arch Linux. The output should be:

````
Non-RAII test: 
Car::Create called.
Driving with my 4 wheeled, Petrol 1.2L car!
Car::Destroy called.
FileStream::OpenStream called.
Written [Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.] to file.
FileStream::Close called.
===============
RAII test: 
Car::Create called.
Driving with my 4 wheeled, Diesel 1.6L car!
FileStream::OpenStream called.
Written [Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.] to file.
FileStream::Close called.
Car::Destroy called.
===============
````
