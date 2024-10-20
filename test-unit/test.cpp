/*
#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#define private public
#include "../src/AVLTree.h"


TEST_CASE("Incorrect Commands", "[flag]")
{
    AVLTree tree;
    // Valid insert for testing
    tree.insert("John Doe", "88888888");

    ostringstream oss;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    // Numbers in name
    tree.insert("12345", "45679999");
    // Ufid not 8 digits
    tree.insert("One", "2");
    // Letters in ufid
    tree.insert("Two", "1234woop");
    // Empty string
    tree.insert("", "12345678");
    // Deleting using name
    tree.remove("John Doe");

    cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "unsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\n");
}

TEST_CASE("Edge Cases", "[flag]")
{
    AVLTree tree;
    tree.insert("Ten", "00000010");
    tree.insert("Twins", "00000007");
    tree.insert("Twins", "00000012");
    tree.insert("Twins", "00000013");

    ostringstream oss;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    // Checking for unique ID
    tree.insert("Ten Again", "00000010");
    // Removing node that does not exist
    tree.remove("00000006");
    // Removing Nth node that does not exist
    tree.removeInorder("20");
    // Printing all IDs for same name
    tree.searchName("Twins");

    cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "unsuccessful\nunsuccessful\nunsuccessful\n00000007\n00000012\n00000013\n");
}

TEST_CASE("Rotations", "[flag]")
{
    AVLTree tree;
    // Right right case: left rotation
    tree.insert("Ten", "00000010");
    tree.insert("Eleven", "00000011");
    tree.insert("Fourteen", "00000014");
    // Left left case: right rotation
    tree.insert("Eight", "00000008");
    tree.insert("Seven", "00000007");
    // Left right case: left right rotation
    tree.insert("Twelve", "00000012");
    tree.insert("Thirteen", "00000013");
    // Right left case: right left rotation
    tree.insert("Sixteen", "00000016");
    tree.insert("Fifteen", "00000015");

    ostringstream oss;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    tree.preorder();

    cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "Eleven, Eight, Seven, Ten, Thirteen, Twelve, Fifteen, Fourteen, Sixteen\n");
}

TEST_CASE("Deletion", "[flag]")
{
    AVLTree tree;
    tree.insert("Ten", "00000010");
    tree.insert("Eleven", "00000011");
    tree.insert("Fourteen", "00000014");
    tree.insert("Eight", "00000008");
    tree.insert("Seven", "00000007");
    tree.insert("Twelve", "00000012");
    tree.insert("Thirteen", "00000013");
    tree.insert("Sixteen", "00000016");
    tree.insert("Fifteen", "00000015");
    // No child
    tree.remove("00000014");
    // One child
    tree.remove("00000015");
    // Two children
    tree.remove("00000011");

    ostringstream oss;
    streambuf* p_cout_streambuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    tree.preorder();

    cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "Twelve, Eight, Seven, Ten, Thirteen, Sixteen\n");
}

TEST_CASE("Large Insert", "[flag]")
{
    AVLTree tree;
    vector<string> expectedOutput, actualOutput;
    // Insert 100 random nodes
    for (int i = 0; i < 100; i++)
    {
        // Generate random ufid, convert to string, and add '0's in front
        int randomInput = rand();
        string num = to_string(randomInput);
        string zeros(8 - num.size(), '0');
        string ufid = zeros + num;

        expectedOutput.push_back(ufid);
        tree.insert("Large Insert", ufid);
    }
    // Sort vector (for inorder)
    sort(expectedOutput.begin(), expectedOutput.end());
    // Delete 10 random nodes
    // Random number capped at 99 (cap - 1)
    int cap = 100;
    for (int j = 0; j < 10; j++)
    {
        int randomIndex = rand() % cap;
        int currIndex = 0;
        for (auto it = expectedOutput.begin(); it != expectedOutput.end(); it++)
        {
            if (currIndex == randomIndex)
            {
                // Erase node from vector
                expectedOutput.erase(it, it + 1);
                string n = to_string(randomIndex);
                tree.removeInorder(n);
            }
            currIndex++;
        }
        // When node deleted decrement cap
        cap--;
    }

    tree.helperUpdateInorderVector(actualOutput);
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(expectedOutput == actualOutput);
}*/
