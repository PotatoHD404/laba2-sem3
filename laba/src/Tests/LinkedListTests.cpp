//
// Created by korna on 17.04.2021.
//

#include "gtest/gtest.h"
#include "../LinkedList.hpp"

TEST(LinkedList, InitDefault) {
    LinkedList<int> arr = LinkedList<int>();
    ASSERT_EQ(0, arr.Count());
    EXPECT_ANY_THROW(arr.GetFirst());
    EXPECT_ANY_THROW(arr.GetLast());
}

TEST(LinkedList, InitCount_Set) {
    EXPECT_ANY_THROW(LinkedList<int>(-1));
    LinkedList<int> arr = LinkedList<int>(2);
    ASSERT_EQ (2, arr.Count());
    arr[0] = 1;
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (0, arr[1]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (0, arr.GetLast());
    arr = LinkedList<int>(0);
    ASSERT_EQ (0, arr.Count());
}


TEST(LinkedList, Add) {
    LinkedList<int> arr = LinkedList<int>();
    arr.Add(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr[-1]);
    EXPECT_ANY_THROW(arr[1]);
    EXPECT_EQ (5, arr[0]);

    arr[0] = 4;
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (4, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());
    EXPECT_ANY_THROW(arr.Set(-1, 1));
    EXPECT_ANY_THROW(arr.Set(1, 1));

    arr.Add(5);
    ASSERT_EQ (2, arr.Count());
    arr.Set(0, 1);
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (5, arr.GetLast());

    arr.Add(3);
    ASSERT_EQ (3, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());
}

TEST(LinkedList, Prepend) {
    LinkedList<int> arr = LinkedList<int>();
    arr.AddFirst(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr[-1]);
    EXPECT_ANY_THROW(arr[1]);
    EXPECT_EQ (5, arr[0]);

    arr[0] = 4;
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (4, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());
    EXPECT_ANY_THROW(arr.Set(-1, 1));
    EXPECT_ANY_THROW(arr.Set(1, 1));

    arr.AddFirst(5);
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (4, arr[1]);
    EXPECT_EQ (5, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());

    arr.AddFirst(3);
    ASSERT_EQ (3, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (3, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());
}

TEST(LinkedList, InsertAt) {
    LinkedList<int> arr = LinkedList<int>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.Insert(1, 4);
    EXPECT_ANY_THROW(arr.Insert(4, -1));
    EXPECT_ANY_THROW(arr.Insert(4, 4));
    ASSERT_EQ (4, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (4, arr[1]);
    EXPECT_EQ (2, arr[2]);
    EXPECT_EQ (3, arr[3]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.Insert(0, 5);
    ASSERT_EQ (5, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (1, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (2, arr[3]);
    EXPECT_EQ (3, arr[4]);
    EXPECT_EQ (5, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.Insert(arr.Count() - 1, 6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (1, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (2, arr[3]);
    EXPECT_EQ (3, arr[4]);
    EXPECT_EQ (6, arr[5]);
    EXPECT_EQ (5, arr.GetFirst());
    EXPECT_EQ (6, arr.GetLast());
}

TEST(LinkedList, PopFirst) {
    LinkedList<int> arr = LinkedList<int>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.RemoveFirst();
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (2, arr[0]);
    EXPECT_EQ (3, arr[1]);
    EXPECT_EQ (2, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.RemoveFirst();
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (3, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.RemoveFirst();
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW(arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW (arr.RemoveFirst(););
}

TEST(LinkedList, PopLast) {
    LinkedList<int> arr = LinkedList<int>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.RemoveLast();
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (2, arr.GetLast());

    arr.RemoveLast();
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (1, arr.GetLast());

    arr.RemoveLast();
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW (arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW(arr.RemoveLast());
}

TEST(LinkedList, RemoveAt) {
    LinkedList<int> arr = LinkedList<int>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    ASSERT_ANY_THROW(arr.RemoveAt(-1));
    ASSERT_ANY_THROW(arr.RemoveAt(3));
    arr.RemoveAt(1);
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (3, arr[1]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.RemoveAt(0);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (3, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW (arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW(arr.RemoveLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));

    arr = LinkedList<int>(2);
    arr[0] = 1;
    arr[1] = 2;

    arr.RemoveAt(1);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (1, arr.GetLast());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW (arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW(arr.RemoveLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));
}

TEST(LinkedList, InitFromArr) {
    int a[] = {1, 2, 3, 4, 5};
    EXPECT_ANY_THROW(LinkedList<int>(a, -1));
    EXPECT_ANY_THROW(LinkedList<int>(nullptr, 1));
    LinkedList<int> arr = LinkedList<int>(a, 5);
    ASSERT_EQ (5, arr.Count());

    arr.Add(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr.RemoveLast();
    EXPECT_ANY_THROW(arr[5]);
    ASSERT_EQ (5, arr.Count());
    arr.Set(0, 0);
    EXPECT_EQ (1, a[0]);
    EXPECT_EQ (0, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    arr = LinkedList<int>(a, 0);
    ASSERT_EQ (0, arr.Count());
}

TEST(LinkedList, InitFromLinkedList) {
    int a[] = {1, 2, 3, 4, 5, 6};
    LinkedList<int> arr1 = LinkedList<int>(a, 5);
    ASSERT_EQ (5, arr1.Count());
    EXPECT_ANY_THROW(arr1[5]);
    LinkedList<int> arr2 = LinkedList<int>(arr1);
    ASSERT_EQ (5, arr2.Count());
    EXPECT_EQ (arr1[0], arr2[0]);
    EXPECT_EQ (arr1[1], arr2[1]);
    EXPECT_EQ (arr1[2], arr2[2]);
    EXPECT_EQ (arr1[3], arr2[3]);
    EXPECT_EQ (arr1[4], arr2[4]);

    arr1.Set(0, 2);
    EXPECT_EQ (arr1[0], 2);
    EXPECT_EQ (arr2[0], 1);
    arr2.Add(0);
    ASSERT_EQ (5, arr1.Count());
    ASSERT_EQ (6, arr2.Count());

    arr1 = LinkedList<int>();
    arr2 = LinkedList<int>(arr1);
    ASSERT_EQ (0, arr2.Count());
}

TEST(LinkedList, Concat) {
    int a[] = {1, 2, 3, 4, 5};
    LinkedList<int> arr1 = LinkedList<int>(a, 5);
    LinkedList<int> arr2 = LinkedList<int>(arr1);
    LinkedList<int> arr3 = arr1.Concat(arr2);
    ASSERT_EQ (arr1.Count() + arr2.Count(), arr3.Count());
    EXPECT_EQ (arr1[0], arr3[0]);
    EXPECT_EQ (arr1[1], arr3[1]);
    EXPECT_EQ (arr1[2], arr3[2]);
    EXPECT_EQ (arr1[3], arr3[3]);
    EXPECT_EQ (arr1[4], arr3[4]);
    EXPECT_EQ (arr2[0], arr3[5]);
    EXPECT_EQ (arr2[1], arr3[6]);
    EXPECT_EQ (arr2[2], arr3[7]);
    EXPECT_EQ (arr2[3], arr3[8]);
    EXPECT_EQ (arr2[4], arr3[9]);

    LinkedList<int> arr4 = LinkedList<int>();
    arr3 = arr1.Concat(arr4);
    ASSERT_EQ (arr1.Count() + arr4.Count(), arr3.Count());
    EXPECT_EQ (arr1[0], arr3[0]);
    EXPECT_EQ (arr1[1], arr3[1]);
    EXPECT_EQ (arr1[2], arr3[2]);
    EXPECT_EQ (arr1[3], arr3[3]);
    EXPECT_EQ (arr1[4], arr3[4]);
}

TEST(LinkedList, GetSubList) {
    int a[] = {1, 2, 3, 4, 5};
    LinkedList<int> arr1 = LinkedList<int>(a, 5);
    LinkedList<int> arr2 = arr1.GetSubList(0, 0);
    ASSERT_EQ(arr2.Count(), 1);
    EXPECT_EQ (arr1[0], 1);
    EXPECT_ANY_THROW(arr2[1]);
    EXPECT_ANY_THROW(arr1.GetSubList(-1, 0));
    EXPECT_ANY_THROW(arr1.GetSubList(1, 0));
    EXPECT_ANY_THROW(arr1.GetSubList(1, 5));

    arr2 = arr1.GetSubList(0, 4);
    ASSERT_EQ(arr2.Count(), 5);
    EXPECT_EQ (arr1[0], arr2[0]);
    EXPECT_EQ (arr1[1], arr2[1]);
    EXPECT_EQ (arr1[2], arr2[2]);
    EXPECT_EQ (arr1[3], arr2[3]);
    EXPECT_EQ (arr1[4], arr2[4]);

    arr2 = arr1.GetSubList(2, 3);
    ASSERT_EQ(arr2.Count(), 2);
    EXPECT_EQ (arr1[2], arr2[0]);
    EXPECT_EQ (arr1[3], arr2[1]);
}
