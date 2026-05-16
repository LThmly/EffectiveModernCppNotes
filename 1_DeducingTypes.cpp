///////////////////////////////////////////////////////
// CHAPTER 1 - Deducing Types                        //
///////////////////////////////////////////////////////

/*
 Type deduction occurs at compile-time and allows the compiler
 to deduce the type of an expressions, variable, or function.
*/

// Rules for template param type - void f(ParamType param)

int x = 27; // int
const int cx = x; // const int
const int& rx = x; // ref to x as const int

template<typename T>
void f(T& param); // Case 1. ParamType is ref || pointer and !univ ref

int main() {
    f(x);  // T is an int, param's type is int&
    f(cx); // T is a const int, param's type is const int&
    f(rx); // T is const int, param's type is const int&
}

/*
 RULE - If the expression's type is a reference, ignore the reference part
 and then pattern-match the expression's type against ParamType to determine T
*/

template<typename T>
void f(T&& param); // Case 2. ParamType is universal ref (ex: rvalue ref)

int main() {
    f(x);  // x is lvalue, T is int&, param's type is int&
    f(cx); // cx is lvalue, T is const int&, param's type is const int&
    f(rx); // rx is lvalue, T is const int&, param's type is const int&
    f(27); // 27 is rvalue, T is int, param's type is int&&

}

template<typename T>
void f(T param); // Case 3. param is just passed by value

int main() {
    f(x);  // T is int, param's type is int
    f(cx); // T is int, param's type is int
    f(rx); // T is int, param's type is int
}

/*
 RULE - Much like for Case 1, drop the ref if the expression's type is a reference,
 but also ignore if it's const or if it's volatile.
*/

/*
 KEY POINTS:
 - reference-ness is ignored during template type deduction
 - lvalue args get "special treatment" with universal ref params
 - const-ness and volatile-ness is ignored for by-value params
 - args that are arrays or function names decay to pointers unless used to initialize refs
*/

