# capitege
My first contribution to the clang community
#Plans:

1. scan a file and see what is in there:
	- class declaration
	- constructor
	- destructor
	- copy constructor
	- move constructor
	- simple function

2. get real function calls
	- input: function name
	- output: test containing the call of the function+initialization+asserts
	- mapping the dependencies of the variables used in the function
	- the final dependencies must be generic types(maybe std constructs)
	- instrumentation of the dependencies(saving the assignments into a log)
	- on return we must know what we expect(asserts can be generated in the tests)

3. generate a test app, which tests the classes
	- must be able to read the logs and generate mocks
	- input string contains instructions, which functions to call on which class(for klee)
	- it should be able to generate google tests or any other types of tests(template)

TEST of the Constructor:
1+. if a template function or class is found, we must search for any template specification
2+. if a private constructor is found, we must find, where is it called and call that function to create the instance of the class
3+. if multiple constructors are found, every one must be called
4. for the class A{} the one type of instantiation is: A a;
5. another type of instantiation is: A* a = new A();// after it call: delete a;
6+. another type of instantiation is: instantiation of a subclass(we test also derivation)
7. if explicit constructor is not found, the implicit one must be called
8+. if there are parameters in the constructor function, they must be initialized too.
9+. copy constructor is also a use case
10+. every field of the record must be checked if they are initialized
11+. look at the constructor, which functions are called and test them if they are properly set.

TEST of the member functions:
1. look at the parameters and try to instantiate them
	- in case of basic types and std some predefined initialization can be used
	- if custom types are used, look at the already generated cases.
	- report any condition that the generator cannot handle
2+. some analysis of the code can be used to see the exact cases
3+. a checking phase should be done before generating anything
4+. map the dependencies of the member variables and local variables
5+. try to collect all the cases to achieve maximum coverage
6+. start test generating at the ones which are on the end of the dependency hierarchy(don't test the generic or std types)

GENERATE TEST for a condition:
- a json file will be generated for defining the reactions of the generator for every special case if it finds a condition (for example in for,while, if, switch):
[{
expression: 'vec.size()>0',
true: '//TODO when the expression will be true',
false: '//TODO when the expresssion will be false',
},...]

- or simply build an AST matcher into the json generator, and let the generator generate the special cases:
[{ 
	assert: 'vec.size() > 0',
	true: 'std::vector<int> vec;vec.push_back(1);',
	false: 'std::vector<int> vec;',
},...]

this json file then can be used to generate the tests for each case
+switch can be defined in the json file

PHASE 1:
0. we need to map the hierarchy of types(to begin with the generic ones)
1. for every class A in the directory:
2. generate the instantiation: A a;
3. generate a function call: a.callfunction(parameters)
	- look at the parameters and try to instantiate them
	- if custom types are used, look at the user-generated cases(predefined.json)
4. if explicit constructor is not found, the implicit one must be called
5. if something is missing(we don't know how to instantiate something) then generate a json file with the missing parts.
6. in case of basic types and std some predefined initialization can be used
7. abstract classes should be overridden(abstract functions must be recognizable)