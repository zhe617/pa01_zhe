#include <iostream>
#include <sstream>
#include <cassert>
#include "card.h"
#include "card_list.h"
using namespace std;

void test(const string &name, bool passed)
{
    cout << (passed ? "PASS" : "FAIL") << name << endl;
}

// Card ordering
void testCardOrdering()
{
    Card ca('c', "a"), ck('c', "k"), d3('d', "3"), s3('s', "3"), h9('h', "9"), hj('h', "j");
    test("c a < c k", ca < ck);
    test("c k < d 3", ck < d3);
    test("d 3 < s 3", d3 < s3);
    test("s 3 < h 9", s3 < h9);
    test("h 9 < h j", h9 < hj);
    test("c a == c a", ca == Card('c', "a"));
    test("h 9 != h j", h9 != hj);
}

// insert
void testInsert()
{
    CardBST bst;
    test("empty: does not contain c a", !bst.contains(Card('c', "a")));
    bst.insert(Card('c', "a"));
    test("contains after single insert", bst.contains(Card('c', "a")));
    bst.insert(Card('h', "k"));
    bst.insert(Card('d', "5"));
    test("contains h k after multi-insert", bst.contains(Card('h', "k")));
    test("contains d 5 after multi-insert", bst.contains(Card('d', "5")));
    bst.insert(Card('c', "a"));
    test("duplicate insert: c a still present (no crash)", bst.contains(Card('c', "a")));
}

// contains
void testContains()
{
    CardBST bst;
    test("empty tree returns false", !bst.contains(Card('s', "10")));
    bst.insert(Card('s', "10"));
    test("contains s 10 after insert", bst.contains(Card('s', "10")));
    test("does not contain h a (not inserted)", !bst.contains(Card('h', "a")));
    bst.insert(Card('h', "a"));
    test("contains h a after second insert", bst.contains(Card('h', "a")));
    test("s 10 still present after second insert", bst.contains(Card('s', "10")));
}

// remove
void testRemove()
{
    CardBST bst;
    bst.insert(Card('c', "a"));
    bst.insert(Card('d', "5"));
    bst.insert(Card('h', "k"));
    bst.remove(Card('d', "5"));
    test("removed d 5: no longer present", !bst.contains(Card('d', "5")));
    test("c a still present after removing d 5", bst.contains(Card('c', "a")));
    test("h k still present after removing d 5", bst.contains(Card('h', "k")));
    bst.remove(Card('s', "9")); // remove non existent: should not crash
    test("remove non-existent: tree intact", bst.contains(Card('h', "k")));
    bst.remove(Card('c', "a")); // remove root
    test("removed root c a: no longer present", !bst.contains(Card('c', "a")));
}

// iterator
void testIterator()
{
    CardBST bst;
    test("empty: begin() == end()", bst.begin() == bst.end());
    test("empty: rbegin() == rend()", bst.rbegin() == bst.rend());

    Card c1('c', "a"), c2('d', "3"), c3('h', "10");
    bst.insert(c3);
    bst.insert(c1);
    bst.insert(c2); // insert out of order

    // Forward: should come out c a, d 3, h 10
    auto it = bst.begin();
    test("forward 1st: c a", *it == c1);
    ++it;
    test("forward 2nd: d 3", *it == c2);
    ++it;
    test("forward 3rd: h 10", *it == c3);
    ++it;
    test("forward: at end", it == bst.end());

    // Reverse: should come out h 10, d 3, c a
    auto rit = bst.rbegin();
    test("reverse 1st: h 10", *rit == c3);
    --rit;
    test("reverse 2nd: d 3", *rit == c2);
    --rit;
    test("reverse 3rd: c a", *rit == c1);
    --rit;
    test("reverse: at rend", rit == bst.rend());
}

// playGame (capture cout output)
string captureGame(CardBST &a, CardBST &b)
{
    ostringstream oss;
    streambuf *old = cout.rdbuf(oss.rdbuf());
    playGame(a, b);
    cout.rdbuf(old);
    return oss.str();
}

void testPlayGame()
{
    // Test 1: common cards exist
    {
        CardBST alice, bob;
        alice.insert(Card('c', "a"));
        alice.insert(Card('d', "5"));
        alice.insert(Card('h', "k"));
        bob.insert(Card('d', "5"));
        bob.insert(Card('h', "k"));
        bob.insert(Card('s', "2"));
        string out = captureGame(alice, bob);
        test("Alice picks first common card d 5",
             out.find("Alice picked matching card d 5") != string::npos);
        test("Bob picks last common card h k",
             out.find("Bob picked matching card h k") != string::npos);
    }
    // Test 2: no common cards
    {
        CardBST alice, bob;
        alice.insert(Card('c', "a"));
        bob.insert(Card('h', "k"));
        string out = captureGame(alice, bob);
        test("no common cards: no pick messages",
             out.find("picked matching") == string::npos);
    }
    // Test 3: both hands empty
    {
        CardBST alice, bob;
        string out = captureGame(alice, bob);
        test("both empty: no crash, prints headers",
             out.find("Alice's cards:") != string::npos);
    }
}

int main()
{
    cout << "Card ordering" << endl;
    testCardOrdering();
    cout << "\ninsert" << endl;
    testInsert();
    cout << "\ncontains" << endl;
    testContains();
    cout << "\nremove" << endl;
    testRemove();
    cout << "\niterator" << endl;
    testIterator();
    cout << "\nplayGame" << endl;
    testPlayGame();
    return 0;
}