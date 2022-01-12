# CppND-System-Monitor
This project implement a basic system monitor (like [htop](https://github.com/hishamhm/htop) does, but simpler).
## Build and Run
The instructions is written in the original starter code [repository](https://github.com/udacity/CppND-System-Monitor-Project-Updated). 
## Reviewer recommended reference material
### Awesome Resources on Web
Here are some awesome resources I like to go through as additional material for C++ OOP:

1. You can check out from chapter 8-12 and even later chapters to do some more practice in OOP -- [learncpp](https://www.learncpp.com/)
2. [Basic Concepts of Object Oriented Programming using C++](https://www.geeksforgeeks.org/basic-concepts-of-object-oriented-programming-using-c/)
3. A short and quick but wonderful tutorial on OOP -- [Object Oriented Programming](https://www.youtube.com/watch?v=ZOKLjJF54Xc)
4. [4 Advantages of Object-Oriented Programming](https://www.roberthalf.com/blog/salaries-and-skills/4-advantages-of-object-oriented-programming)
5. [Differences between Procedural and Object Oriented Programming](https://www.geeksforgeeks.org/differences-between-procedural-and-object-oriented-programming/)
6. [Modern C++ Object-Oriented Programming](https://ms.sapientia.ro/~manyi/teaching/c++/CPP_v1.1.pdf)
7. Great series on basic C++ with some important OOP concepts throughout the series -- [C++ Beginner Game Programming](https://www.youtube.com/playlist?list=PLqCJpWy5FohcehaXlCIt8sVBHBFFRVWsx)
8. A good overview of OOP though it's covered in Python you will find a lot of concepts well explained -- [Object Oriented Programming](https://www.youtube.com/watch?v=-DP1i2ZU9gk)
9. A good amount of OOP concepts are used while making this role-playing game. I am posting only the first part of the series but there are 4 parts for this series so do complete them. You will have a fun time doing it -- [Code-It-Yourself! Role Playing Game](https://www.youtube.com/watch?v=xXXt3htgDok&list=PLrOv9FMX8xJE8NgepZR1etrsU63fDDGxO&index=18)
10. Another good resource on Polymorphism -- [Polymorphism](https://www.youtube.com/watch?v=kxKKHKSMGIg&t=651s)
11. A great video on Pointers -- [What Are Pointers? C++](https://www.youtube.com/watch?v=iChalAKXffs)

Here are a few additional resources you can look at it for more information on Object Oriented Programming:

1. [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
2. [CppCon 2019 – Back to Basics Object Oriented Programming](https://youtu.be/32tDTD9UJCE) - This back to basics series is so much awesome. I would recommend you to go through all of the back to basics CppCon
3. [SOLID](https://www.youtube.com/watch?v=rtmFCcjEgEw)
4. [Design Patterns](http://www.uml.org.cn/c++/pdf/DesignPatterns.pdf)

You may also find the following reading material helpful:

1. [Code Complete, Steve McConnell](http://aroma.vn/web/wp-content/uploads/2016/11/code-complete-2nd-edition-v413hav.pdf)
2. [Clean Code, Robert C Martin](https://enos.itcollege.ee/~jpoial/oop/naited/Clean%20Code.pdf)
3. [The Pragmatic Programmer, Andrew Hunt and Dave Thomas.](https://www.cin.ufpe.br/~cavmj/104The%20Pragmatic%20Programmer,%20From%20Journeyman%20To%20Master%20-%20Andrew%20Hunt,%20David%20Thomas%20-%20Addison%20Wesley%20-%201999.pdf)
4. [Design Patterns: Elements of Reusable Object Oriented Software, Emich Gamma et all.](http://www.uml.org.cn/c++/pdf/DesignPatterns.pdf)
### Add to Knowledge
#### CMake and Make
* Overview of [CMake](https://cmake.org/overview/) and how it manages cross-platform build processes.
* Introduction to CMake by [examples](https://review.udacity.com/Introduction%20to%20CMake%20by%20Example) that apply single file project, and multiple directory projects.
* Introduction to [Make](https://www.gnu.org/software/make/) and how it uses the Makefile generated by CMake to build the system.
* How to [write Makefiles](https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html). This is just for your information. It is already automated through CMake.
#### Makefile
1. [GNU MakeFile Documentation](https://www.gnu.org/software/make/manual/html_node/Standard-Targets.html#Standard-Targets)
2. [A Simple Makefile Tutorial](http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)
3. [Variable Name Convention](https://makefiletutorial.com/)

#### Adjust Compiler Warning Level
1. [Link 1: Configuring your compiler: Warning and error levels](https://www.learncpp.com/cpp-tutorial/configuring-your-compiler-warning-and-error-levels/)
2. [Link 2: Suppressing the warning](https://www.viva64.com/en/k/0048/)
3. [Link 3: Guidelines on warning](https://github.com/boostorg/boost/wiki/Guidelines:-Warnings)
4. [Intel® C++ Compiler 19.0 Developer Guide and Reference](https://software.intel.com/en-us/cpp-compiler-developer-guide-and-reference-remarks-warnings-and-errors)
#### ncurses
[Writing Programs with NCURSES](https://invisible-island.net/ncurses/ncurses-intro.html)
#### Process
[Process Meaning](https://en.wikipedia.org/wiki/Process_(computing)) and process [in Linux](https://www.tecmint.com/linux-process-management/)
#### Overload
Note : Following Operators cannot be overloaded:
1. `.` (Member Access or Dot operator)
2. `?:` (Ternary or Conditional Operator )
3. `::` (Scope Resolution Operator)
4. `.*` (Pointer-to-member Operator )
5. `sizeof` (Object size Operator)
6. `typeid` (Object type Operator)
#### chrono
[CppCon 2016: Howard Hinnant “A ＜chrono＞ Tutorial"](https://www.youtube.com/watch?v=P32hvk8b13M)
