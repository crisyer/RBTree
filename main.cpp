// Driver Program for Red Black Tree

#include <bits/stdc++.h>
#include "RBTree.h"
using namespace std;

int main() {
    int data;
    RBTree rbTree1;
    auto beforeTime = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000000; i++)
    {
        rbTree1.insert(data);
    }

    // rbTree1.inorder();

    // cin >> data;
    // while (data != 0)
    // {
    //     rbTree1.deleteValue(data);
    //     rbTree1.inorder();
    //     cin >> data;
    // }

    for (int i = 100000000; i > 0; i--)
    {
        rbTree1.deleteValue(data);
    }
    auto afterTime = std::chrono::steady_clock::now();
    double duration_second = std::chrono::duration<double>(afterTime - beforeTime).count();
	std::cout << duration_second << "秒" << std::endl;

    return 0;
}