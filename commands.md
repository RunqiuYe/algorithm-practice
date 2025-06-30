Compile C++ code:
```sh
g++ -std=c++11 -O2 -Wall a.cpp -o a
```
Take a line of input:
```cpp
string s;
getline(cin, s);
```
Reading input:
```cpp
int a, b;
scanf("%d %d", &a, &b);
```
Make input and output more efficient:
```cpp
ios::sync_with_stdio(0);
cin.tie(0);
```