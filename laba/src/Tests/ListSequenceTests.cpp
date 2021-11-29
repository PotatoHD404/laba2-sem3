//
// Created by korna on 17.04.2021.
//


#include "gtest/gtest.h"
#include "../ListSequence.hpp"

TEST(ListSequence_int, InitDefault) {
    ListSequence<int> arr = ListSequence<int>();
    ASSERT_EQ(0, arr.Count());
    EXPECT_ANY_THROW(arr.First());
    EXPECT_ANY_THROW(arr.Last());
}

TEST(ListSequence_int, InitCount_Set_Clear) {
    EXPECT_ANY_THROW(ListSequence<int>(-1));
    ListSequence<int> arr = ListSequence<int>(2);
    ASSERT_EQ (2, arr.Count());
    arr[0] = 1;
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (0, arr[1]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (0, arr.Last());
    arr = ListSequence<int>(0);
    ASSERT_EQ (0, arr.Count());
    arr = ListSequence<int>(10);
    ASSERT_EQ (10, arr.Count());
    arr.Clear();
    EXPECT_EQ (0, arr.Count());
}


TEST(ListSequence_int, Add) {
    ListSequence<int> arr = ListSequence<int>();
    arr.Add(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr[-1]);
    EXPECT_ANY_THROW(arr[1]);
    EXPECT_EQ (5, arr[0]);

    arr[0] = 4;
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (4, arr.First());
    EXPECT_EQ (4, arr.Last());
    EXPECT_ANY_THROW(arr.Set(-1, 1));
    EXPECT_ANY_THROW(arr.Set(1, 1));

    arr.Add(5);
    ASSERT_EQ (2, arr.Count());
    arr.Set(0, 1);
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (5, arr.Last());

    arr.Add(3);
    ASSERT_EQ (3, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (3, arr.Last());
}

TEST(ListSequence_int, Prepend) {
    ListSequence<int> arr = ListSequence<int>();
    arr.AddFirst(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr[-1]);
    EXPECT_ANY_THROW(arr[1]);
    EXPECT_EQ (5, arr[0]);

    arr[0] = 4;
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (4, arr.First());
    EXPECT_EQ (4, arr.Last());
    EXPECT_ANY_THROW(arr.Set(-1, 1));
    EXPECT_ANY_THROW(arr.Set(1, 1));

    arr.AddFirst(5);
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (4, arr[1]);
    EXPECT_EQ (5, arr.First());
    EXPECT_EQ (4, arr.Last());

    arr.AddFirst(3);
    ASSERT_EQ (3, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (3, arr.First());
    EXPECT_EQ (4, arr.Last());
}

TEST(ListSequence_int, InsertAt) {
    ListSequence<int> arr = ListSequence<int>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.Insert(1, 4);
    ASSERT_EQ (4, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (4, arr[1]);
    EXPECT_EQ (2, arr[2]);
    EXPECT_EQ (3, arr[3]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.Insert(0, 5);
    ASSERT_EQ (5, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (1, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (2, arr[3]);
    EXPECT_EQ (3, arr[4]);
    EXPECT_EQ (5, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.Insert(arr.Count() - 1, 6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (1, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (2, arr[3]);
    EXPECT_EQ (3, arr[4]);
    EXPECT_EQ (6, arr[5]);
    EXPECT_EQ (5, arr.First());
    EXPECT_EQ (6, arr.Last());
}

TEST(ListSequence_int, PopFirst) {
    ListSequence<int> arr = ListSequence<int>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.RemoveFirst();
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (2, arr[0]);
    EXPECT_EQ (3, arr[1]);
    EXPECT_EQ (2, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.RemoveFirst();
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (3, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.RemoveFirst();
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW(arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW (arr.RemoveFirst(););
}

TEST(ListSequence_int, PopLast) {
    ListSequence<int> arr = ListSequence<int>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.RemoveLast();
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (2, arr.Last());

    arr.RemoveLast();
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (1, arr.Last());

    arr.RemoveLast();
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW (arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW(arr.RemoveLast());
}

TEST(ListSequence_int, RemoveAt) {
    ListSequence<int> arr = ListSequence<int>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    ASSERT_ANY_THROW(arr.RemoveAt(-1));
    ASSERT_ANY_THROW(arr.RemoveAt(3));
    arr.RemoveAt(1);
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (3, arr[1]);
    ASSERT_ANY_THROW (arr[2]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.RemoveAt(0);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (3, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW (arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW(arr.RemoveLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));

    arr = ListSequence<int>(2);
    arr[0] = 1;
    arr[1] = 2;

    arr.RemoveAt(1);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (1, arr.Last());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW (arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW(arr.RemoveLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));
}

TEST(ListSequence_int, InitFromArr) {
    int a[] = {1, 2, 3, 4, 5};
    EXPECT_ANY_THROW(ListSequence<int>(a, -1));
    EXPECT_ANY_THROW(ListSequence<int>(nullptr, 1));
    ListSequence<int> arr = ListSequence<int>(a, 5);
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
    arr = ListSequence<int>(a, 0);
    ASSERT_EQ (0, arr.Count());

    arr = ListSequence<int>(a);
    ASSERT_EQ (5, arr.Count());

    arr.Add(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr = ListSequence<int>({1, 2, 3, 4, 5});
    ASSERT_EQ (5, arr.Count());

    arr.Add(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);
}

TEST(ListSequence_int, InitFromListSequence) {
    int a[] = {1, 2, 3, 4, 5, 6};
    ListSequence<int> arr1 = ListSequence<int>(a, 5);
    ASSERT_EQ (5, arr1.Count());
    EXPECT_ANY_THROW(arr1[5]);
    ListSequence<int> arr2 = ListSequence<int>(arr1);
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

    arr1 = ListSequence<int>();
    arr2 = ListSequence<int>(arr1);
    ASSERT_EQ (0, arr2.Count());
}

//TEST(ListSequence_int, Concat) {
//    int a[] = {1, 2, 3, 4, 5};
//    ListSequence<int> arr1 = ListSequence<int>(a, 5);
//    ListSequence<int> arr2 = ListSequence<int>(arr1);
//    std::unique_ptr<ListSequence<int>> arr3 = std::unique_ptr<ListSequence<int>>(arr1.Concat(arr2));
//    ASSERT_EQ (arr1.Count() + arr2.Count(), arr3->Count());
//    EXPECT_EQ (arr1[0], arr3->Get(0));
//    EXPECT_EQ (arr1[1], arr3->Get(1));
//    EXPECT_EQ (arr1[2], arr3->Get(2));
//    EXPECT_EQ (arr1[3], arr3->Get(3));
//    EXPECT_EQ (arr1[4], arr3->Get(4));
//    EXPECT_EQ (arr2[0], arr3->Get(5));
//    EXPECT_EQ (arr2[1], arr3->Get(6));
//    EXPECT_EQ (arr2[2], arr3->Get(7));
//    EXPECT_EQ (arr2[3], arr3->Get(8));
//    EXPECT_EQ (arr2[4], arr3->Get(9));
//
//    ListSequence<int> arr4 = ListSequence<int>();
//    arr3 = std::unique_ptr<ListSequence<int>>(arr1.Concat(arr4));
//    ASSERT_EQ (arr1.Count() + arr4.Count(), arr3->Count());
//    EXPECT_EQ (arr1[0], arr3->Get(0));
//    EXPECT_EQ (arr1[1], arr3->Get(1));
//    EXPECT_EQ (arr1[2], arr3->Get(2));
//    EXPECT_EQ (arr1[3], arr3->Get(3));
//    EXPECT_EQ (arr1[4], arr3->Get(4));
//}
//
//TEST(ListSequence_int, Subsequence) {
//    int a[] = {1, 2, 3, 4, 5};
//    ListSequence<int> arr1 = ListSequence<int>(a, 5);
//    unique_ptr<ListSequence<int>>
//            arr2 = unique_ptr<ListSequence<int>>(arr1.Subsequence(0, 0));
//    ASSERT_EQ(arr2->Count(), 1);
//    EXPECT_EQ (arr1[0], 1);
//    EXPECT_ANY_THROW(arr2->Get(1));
//    EXPECT_ANY_THROW(arr1.Subsequence(-1, 0));
//    EXPECT_ANY_THROW(arr1.Subsequence(1, 0));
//    EXPECT_ANY_THROW(arr1.Subsequence(1, 5));
//    arr2 = unique_ptr<ListSequence<int>>(arr1.Subsequence(0, 4));
//    ASSERT_EQ(arr2->Count(), 5);
//    EXPECT_EQ (arr1[0], arr2->Get(0));
//    EXPECT_EQ (arr1[1], arr2->Get(1));
//    EXPECT_EQ (arr1[2], arr2->Get(2));
//    EXPECT_EQ (arr1[3], arr2->Get(3));
//    EXPECT_EQ (arr1[4], arr2->Get(4));
//    arr2 = unique_ptr<ListSequence<int>>(arr1.Subsequence(2, 3));
//    ASSERT_EQ(arr2->Count(), 2);
//    EXPECT_EQ (arr1[2], arr2->Get(0));
//    EXPECT_EQ (arr1[3], arr2->Get(1));
//}

TEST(ListSequence_float, InitDefault) {
    ListSequence<float> arr = ListSequence<float>();
    ASSERT_EQ(0, arr.Count());
    EXPECT_ANY_THROW(arr.First());
    EXPECT_ANY_THROW(arr.Last());
}

TEST(ListSequence_float, InitCount_Set_Clear) {
    EXPECT_ANY_THROW(ListSequence<float>(-1));
    ListSequence<float> arr = ListSequence<float>(2);
    ASSERT_EQ (2, arr.Count());
    arr[0] = 1;
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (0, arr[1]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (0, arr.Last());
    arr = ListSequence<float>(0);
    ASSERT_EQ (0, arr.Count());
    arr = ListSequence<float>(10);
    ASSERT_EQ (10, arr.Count());
    arr.Clear();
    EXPECT_EQ (0, arr.Count());
}


TEST(ListSequence_float, Add) {
    ListSequence<float> arr = ListSequence<float>();
    arr.Add(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr[-1]);
    EXPECT_ANY_THROW(arr[1]);
    EXPECT_EQ (5, arr[0]);

    arr[0] = 4;
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (4, arr.First());
    EXPECT_EQ (4, arr.Last());
    EXPECT_ANY_THROW(arr.Set(-1, 1));
    EXPECT_ANY_THROW(arr.Set(1, 1));

    arr.Add(5);
    ASSERT_EQ (2, arr.Count());
    arr.Set(0, 1);
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (5, arr.Last());

    arr.Add(3);
    ASSERT_EQ (3, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (3, arr.Last());
}

TEST(ListSequence_float, Prepend) {
    ListSequence<float> arr = ListSequence<float>();
    arr.AddFirst(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr[-1]);
    EXPECT_ANY_THROW(arr[1]);
    EXPECT_EQ (5, arr[0]);

    arr[0] = 4;
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (4, arr.First());
    EXPECT_EQ (4, arr.Last());
    EXPECT_ANY_THROW(arr.Set(-1, 1));
    EXPECT_ANY_THROW(arr.Set(1, 1));

    arr.AddFirst(5);
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (4, arr[1]);
    EXPECT_EQ (5, arr.First());
    EXPECT_EQ (4, arr.Last());

    arr.AddFirst(3);
    ASSERT_EQ (3, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (3, arr.First());
    EXPECT_EQ (4, arr.Last());
}

TEST(ListSequence_float, InsertAt) {
    ListSequence<float> arr = ListSequence<float>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.Insert(1, 4);
    ASSERT_EQ (4, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (4, arr[1]);
    EXPECT_EQ (2, arr[2]);
    EXPECT_EQ (3, arr[3]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.Insert(0, 5);
    ASSERT_EQ (5, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (1, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (2, arr[3]);
    EXPECT_EQ (3, arr[4]);
    EXPECT_EQ (5, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.Insert(arr.Count() - 1, 6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (1, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (2, arr[3]);
    EXPECT_EQ (3, arr[4]);
    EXPECT_EQ (6, arr[5]);
    EXPECT_EQ (5, arr.First());
    EXPECT_EQ (6, arr.Last());
}

TEST(ListSequence_float, PopFirst) {
    ListSequence<float> arr = ListSequence<float>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.RemoveFirst();
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (2, arr[0]);
    EXPECT_EQ (3, arr[1]);
    EXPECT_EQ (2, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.RemoveFirst();
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (3, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.RemoveFirst();
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW(arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW (arr.RemoveFirst(););
}

TEST(ListSequence_float, PopLast) {
    ListSequence<float> arr = ListSequence<float>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.RemoveLast();
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (2, arr.Last());

    arr.RemoveLast();
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (1, arr.Last());

    arr.RemoveLast();
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW (arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW(arr.RemoveLast());
}

TEST(ListSequence_float, RemoveAt) {
    ListSequence<float> arr = ListSequence<float>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    ASSERT_ANY_THROW(arr.RemoveAt(-1));
    ASSERT_ANY_THROW(arr.RemoveAt(3));
    arr.RemoveAt(1);
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (3, arr[1]);
    ASSERT_ANY_THROW (arr[2]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.RemoveAt(0);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (3, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW (arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW(arr.RemoveLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));

    arr = ListSequence<float>(2);
    arr[0] = 1;
    arr[1] = 2;

    arr.RemoveAt(1);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (1, arr.Last());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr[0]);
    EXPECT_ANY_THROW (arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW(arr.RemoveLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));
}

TEST(ListSequence_float, InitFromArr) {
    float a[] = {1, 2, 3, 4, 5};
    EXPECT_ANY_THROW(ListSequence<float>(a, -1));
    EXPECT_ANY_THROW(ListSequence<float>(nullptr, 1));
    ListSequence<float> arr = ListSequence<float>(a, 5);
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
    arr = ListSequence<float>(a, 0);
    ASSERT_EQ (0, arr.Count());

    arr = ListSequence<float>(a);
    ASSERT_EQ (5, arr.Count());

    arr.Add(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr = ListSequence<float>({1, 2, 3, 4, 5});
    ASSERT_EQ (5, arr.Count());

    arr.Add(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr = ListSequence<float>{};
    ASSERT_EQ (0, arr.Count());
    arr.Add(6);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (6, arr[0]);
    EXPECT_ANY_THROW(arr[1]);
}

TEST(ListSequence_float, InitFromListSequence) {
    float a[] = {1, 2, 3, 4, 5, 6};
    ListSequence<float> arr1 = ListSequence<float>(a, 5);
    ASSERT_EQ (5, arr1.Count());
    EXPECT_ANY_THROW(arr1[5]);
    ListSequence<float> arr2 = ListSequence<float>(arr1);
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

    arr1 = ListSequence<float>();
    arr2 = ListSequence<float>(arr1);
    ASSERT_EQ (0, arr2.Count());
}

//TEST(ListSequence_float, Concat) {
//    float a[] = {1, 2, 3, 4, 5};
//    ListSequence<float> arr1 = ListSequence<float>(a, 5);
//    ListSequence<float> arr2 = ListSequence<float>(arr1);
//    std::unique_ptr<ListSequence<float>> arr3 = std::unique_ptr<ListSequence<float>>(arr1.Concat(arr2));
//    ASSERT_EQ (arr1.Count() + arr2.Count(), arr3->Count());
//    EXPECT_EQ (arr1[0], arr3->Get(0));
//    EXPECT_EQ (arr1[1], arr3->Get(1));
//    EXPECT_EQ (arr1[2], arr3->Get(2));
//    EXPECT_EQ (arr1[3], arr3->Get(3));
//    EXPECT_EQ (arr1[4], arr3->Get(4));
//    EXPECT_EQ (arr2[0], arr3->Get(5));
//    EXPECT_EQ (arr2[1], arr3->Get(6));
//    EXPECT_EQ (arr2[2], arr3->Get(7));
//    EXPECT_EQ (arr2[3], arr3->Get(8));
//    EXPECT_EQ (arr2[4], arr3->Get(9));
//
//    ListSequence<float> arr4 = ListSequence<float>();
//    arr3 = std::unique_ptr<ListSequence<float>>(arr1.Concat(arr4));
//    ASSERT_EQ (arr1.Count() + arr4.Count(), arr3->Count());
//    EXPECT_EQ (arr1[0], arr3->Get(0));
//    EXPECT_EQ (arr1[1], arr3->Get(1));
//    EXPECT_EQ (arr1[2], arr3->Get(2));
//    EXPECT_EQ (arr1[3], arr3->Get(3));
//    EXPECT_EQ (arr1[4], arr3->Get(4));
//}
//
//TEST(ListSequence_float, Subsequence) {
//    float a[] = {1, 2, 3, 4, 5};
//    ListSequence<float> arr1 = ListSequence<float>(a, 5);
//    unique_ptr<ListSequence<float>>
//            arr2 = unique_ptr<ListSequence<float>>(arr1.Subsequence(0, 0));
//    ASSERT_EQ(arr2->Count(), 1);
//    EXPECT_EQ (arr1[0], 1);
//    EXPECT_ANY_THROW(arr2->Get(1));
//    EXPECT_ANY_THROW(arr1.Subsequence(-1, 0));
//    EXPECT_ANY_THROW(arr1.Subsequence(1, 0));
//    EXPECT_ANY_THROW(arr1.Subsequence(1, 5));
//    arr2 = unique_ptr<ListSequence<float>>(arr1.Subsequence(0, 4));
//    ASSERT_EQ(arr2->Count(), 5);
//    EXPECT_EQ (arr1[0], arr2->Get(0));
//    EXPECT_EQ (arr1[1], arr2->Get(1));
//    EXPECT_EQ (arr1[2], arr2->Get(2));
//    EXPECT_EQ (arr1[3], arr2->Get(3));
//    EXPECT_EQ (arr1[4], arr2->Get(4));
//    arr2 = unique_ptr<ListSequence<float>>(arr1.Subsequence(2, 3));
//    ASSERT_EQ(arr2->Count(), 2);
//    EXPECT_EQ (arr1[2], arr2->Get(0));
//    EXPECT_EQ (arr1[3], arr2->Get(1));
//}


TEST(ListSequence_int, Equals) {
    ListSequence<int> arr{1, 2, 3};
    ListSequence<int> arr1{1, 2};
    ListSequence<int> arr2{1, 2, 3};
    ListSequence<int> arr3{3, 2};
    EXPECT_TRUE(arr == arr2);
    EXPECT_FALSE(arr == arr1);
    EXPECT_FALSE(arr1 == arr3);
    ListSequence<int> arr4{};
    ListSequence<int> arr5{};
    EXPECT_TRUE(arr4 == arr5);
}