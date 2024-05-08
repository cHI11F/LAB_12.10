#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_12.10/LAB_12.10.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestWordCount)
        {
            // Prepare test data
            map<string, int> testWordCount;
            testWordCount["apple"] = 2;
            testWordCount["banana"] = 1;
            testWordCount["orange"] = 1;

            // Call the tested function
            map<string, int> resultWordCount = countWords("test_input.txt");

            // Check results
            Assert::AreEqual(static_cast<int>(testWordCount.size()), static_cast<int>(resultWordCount.size()), L"Number of unique words");
            for (const auto& pair : testWordCount) {
                if (resultWordCount.find(pair.first) != resultWordCount.end()) {
                    Assert::AreEqual(pair.second, resultWordCount[pair.first], (L"Occurrences of word " + wstring(pair.first.begin(), pair.first.end())).c_str());
                }
                else {
                    Assert::Fail((wstring(L"Word ") + wstring(pair.first.begin(), pair.first.end()) + L" not found in the results").c_str());
                }
            }
        }

        TEST_METHOD(TestTreeNodeCreation)
        {
            // Prepare test data
            TreeNode* root = new TreeNode("apple", 2);
            TreeNode* child1 = new TreeNode("banana", 1);
            TreeNode* child2 = new TreeNode("orange", 1);

            root->children.push_back(child1);
            root->children.push_back(child2);

            // Check results
            Assert::IsTrue(root->word == "apple");
            Assert::IsTrue(root->count == 2);
            Assert::IsTrue(root->children[0]->word == "banana");
            Assert::IsTrue(root->children[0]->count == 1);
            Assert::IsTrue(root->children[1]->word == "orange");
            Assert::IsTrue(root->children[1]->count == 1);

            // Memory cleanup
            delete root;
            delete child1;
            delete child2;
        }

        TEST_METHOD(TestTreePrinting)
        {
            // Prepare test data
            TreeNode* root = new TreeNode("apple", 2);
            TreeNode* child1 = new TreeNode("banana", 1);
            TreeNode* child2 = new TreeNode("orange", 1);

            root->children.push_back(child1);
            root->children.push_back(child2);

            // Call the tested function
            stringstream outputStream;
            printTree(root, 0, outputStream);
            string expectedOutput = "apple (2)\n  banana (1)\n  orange (1)\n";

            // Check results
            Assert::AreEqual(expectedOutput.c_str(), outputStream.str().c_str());

            // Memory cleanup
            delete root;
            delete child1;
            delete child2;
        }
    };
}
