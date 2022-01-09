//
// Created by korna on 17.04.2021.
//

#include "gtest/gtest.h"
#include "../ArraySequence.hpp"

TEST(ArraySequence_int, InitDefault) {
    ArraySequence<int> arr = ArraySequence<int>();
    ASSERT_EQ(0, arr.Count());
    EXPECT_ANY_THROW(arr.First());
    EXPECT_ANY_THROW(arr.Last());
}

TEST(ArraySequence_int, InitCount_Set_Clear) {
    EXPECT_ANY_THROW(ArraySequence<int>(-1));
    ArraySequence<int> arr = ArraySequence<int>(2);
    ASSERT_EQ (2, arr.Count());
    arr[0] = 1;
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (0, arr[1]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (0, arr.Last());
    arr = ArraySequence<int>(0);
    ASSERT_EQ (0, arr.Count());
    arr = ArraySequence<int>(10);
    ASSERT_EQ (10, arr.Count());
    arr.Clear();
    EXPECT_EQ (0, arr.Count());
}


TEST(ArraySequence_int, Add) {
    ArraySequence<int> arr = ArraySequence<int>();
    arr.Add(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr.Get(-1));
    EXPECT_ANY_THROW(arr.Get(1));
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

TEST(ArraySequence_int, Prepend) {
    ArraySequence<int> arr = ArraySequence<int>();
    arr.AddFirst(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr.Get(-1));
    EXPECT_ANY_THROW(arr.Get(1));
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

//TEST(ArraySequence_int, InsertAt) {
//    ArraySequence<int> arr = ArraySequence<int>(3);
//    arr[0] = 1;
//    arr[1] = 2;
//    arr[2] = 3;
//    arr.Insert(1, 4);
//    ASSERT_EQ (4, arr.Count());
//    EXPECT_EQ (1, arr[0]);
//    EXPECT_EQ (4, arr[1]);
//    EXPECT_EQ (2, arr[2]);
//    EXPECT_EQ (3, arr[3]);
//    EXPECT_EQ (1, arr.First());
//    EXPECT_EQ (3, arr.Last());
//
//    arr.Insert(0, 5);
//    ASSERT_EQ (5, arr.Count());
//    EXPECT_EQ (5, arr[0]);
//    EXPECT_EQ (1, arr[1]);
//    EXPECT_EQ (4, arr[2]);
//    EXPECT_EQ (2, arr[3]);
//    EXPECT_EQ (3, arr[4]);
//    EXPECT_EQ (5, arr.First());
//    EXPECT_EQ (3, arr.Last());
//
//    arr.Insert(arr.Count() - 1, 6);
//    ASSERT_EQ (6, arr.Count());
//    EXPECT_EQ (5, arr[0]);
//    EXPECT_EQ (1, arr[1]);
//    EXPECT_EQ (4, arr[2]);
//    EXPECT_EQ (2, arr[3]);
//    EXPECT_EQ (3, arr[4]);
//    EXPECT_EQ (6, arr[5]);
//    EXPECT_EQ (5, arr.First());
//    EXPECT_EQ (6, arr.Last());
//}

TEST(ArraySequence_int, PopFirst) {
    ArraySequence<int> arr = ArraySequence<int>(3);
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
    EXPECT_ANY_THROW (arr.Get(0));
    EXPECT_ANY_THROW(arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW (arr.RemoveFirst(););
}

TEST(ArraySequence_int, PopLast) {
    ArraySequence<int> arr = ArraySequence<int>(3);
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
    EXPECT_ANY_THROW (arr.Get(0));
    EXPECT_ANY_THROW (arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW(arr.RemoveLast());
}

TEST(ArraySequence_int, RemoveAt) {
    ArraySequence<int> arr = ArraySequence<int>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    ASSERT_ANY_THROW(arr.RemoveAt(-1));
    ASSERT_ANY_THROW(arr.RemoveAt(3));
    arr.RemoveAt(1);
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (3, arr[1]);
    ASSERT_ANY_THROW (arr.Get(2));
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.RemoveAt(0);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (3, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr.Get(0));
    EXPECT_ANY_THROW (arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW(arr.RemoveLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));

    arr = ArraySequence<int>(2);
    arr[0] = 1;
    arr[1] = 2;

    arr.RemoveAt(1);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (1, arr.Last());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr.Get(0));
    EXPECT_ANY_THROW (arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW(arr.RemoveLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));
}

TEST(ArraySequence_int, InitFromArr) {
    int a[] = {1, 2, 3, 4, 5};
    EXPECT_ANY_THROW(ArraySequence<int>(a, -1));
    EXPECT_ANY_THROW(ArraySequence<int>(nullptr, 1));
    ArraySequence<int> arr = ArraySequence<int>(a, 5);
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
    EXPECT_ANY_THROW(arr.Get(5));
    ASSERT_EQ (5, arr.Count());
    arr.Set(0, 0);
    EXPECT_EQ (1, a[0]);
    EXPECT_EQ (0, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    arr = ArraySequence<int>(a, 0);
    ASSERT_EQ (0, arr.Count());

    arr = ArraySequence<int>(a);
    ASSERT_EQ (5, arr.Count());

    arr.Add(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr = ArraySequence<int>({1, 2, 3, 4, 5});
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

TEST(ArraySequence_int, InitFromArraySequence) {
    int a[] = {1, 2, 3, 4, 5, 6};
    ArraySequence<int> arr1 = ArraySequence<int>(a, 5);
    ASSERT_EQ (5, arr1.Count());
    EXPECT_ANY_THROW(arr1.Get(5));
    ArraySequence<int> arr2 = ArraySequence<int>(arr1);
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

    arr1 = ArraySequence<int>();
    arr2 = ArraySequence<int>(arr1);
    ASSERT_EQ (0, arr2.Count());
}

//TEST(ArraySequence_int, Concat) {
//    int a[] = {1, 2, 3, 4, 5};
//    ArraySequence<int> arr1 = ArraySequence<int>(a, 5);
//    ArraySequence<int> arr2 = ArraySequence<int>(arr1);
//    std::unique_ptr<ArraySequence<int>> arr3 = std::unique_ptr<ArraySequence<int>>(arr1.Concat(arr2));
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
//    ArraySequence<int> arr4 = ArraySequence<int>();
//    arr3 = std::unique_ptr<ArraySequence<int>>(arr1.Concat(arr4));
//    ASSERT_EQ (arr1.Count() + arr4.Count(), arr3->Count());
//    EXPECT_EQ (arr1[0], arr3->Get(0));
//    EXPECT_EQ (arr1[1], arr3->Get(1));
//    EXPECT_EQ (arr1[2], arr3->Get(2));
//    EXPECT_EQ (arr1[3], arr3->Get(3));
//    EXPECT_EQ (arr1[4], arr3->Get(4));
//}

TEST(ArraySequence_int, GetSubsequence) {
    int a[] = {1, 2, 3, 4, 5};
    ArraySequence<int> arr1 = ArraySequence<int>(a, 5);
    unique_ptr<ArraySequence<int>>
            arr2 = unique_ptr<ArraySequence<int>>(arr1.GetSubsequence(0, 0));
    ASSERT_EQ(arr2->Count(), 1);
    EXPECT_EQ (arr1[0], 1);
    EXPECT_ANY_THROW(arr2->Get(1));
    EXPECT_ANY_THROW(arr1.GetSubsequence(-1, 0));
    EXPECT_ANY_THROW(arr1.GetSubsequence(1, 0));
    EXPECT_ANY_THROW(arr1.GetSubsequence(1, 5));
    arr2 = unique_ptr<ArraySequence<int>>(arr1.GetSubsequence(0, 4));
    ASSERT_EQ(arr2->Count(), 5);
    EXPECT_EQ (arr1[0], arr2->Get(0));
    EXPECT_EQ (arr1[1], arr2->Get(1));
    EXPECT_EQ (arr1[2], arr2->Get(2));
    EXPECT_EQ (arr1[3], arr2->Get(3));
    EXPECT_EQ (arr1[4], arr2->Get(4));
    arr2 = unique_ptr<ArraySequence<int>>(arr1.GetSubsequence(2, 3));
    ASSERT_EQ(arr2->Count(), 2);
    EXPECT_EQ (arr1[2], arr2->Get(0));
    EXPECT_EQ (arr1[3], arr2->Get(1));
}

TEST(ArraySequence_float, InitDefault) {
    ArraySequence<float> arr = ArraySequence<float>();
    ASSERT_EQ(0, arr.Count());
    EXPECT_ANY_THROW(arr.First());
    EXPECT_ANY_THROW(arr.Last());
}

TEST(ArraySequence_float, InitCount_Set_Clear) {
    EXPECT_ANY_THROW(ArraySequence<float>(-1));
    ArraySequence<float> arr = ArraySequence<float>(2);
    ASSERT_EQ (2, arr.Count());
    arr[0] = 1;
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (0, arr[1]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (0, arr.Last());
    arr = ArraySequence<float>(0);
    ASSERT_EQ (0, arr.Count());
    arr = ArraySequence<float>(10);
    ASSERT_EQ (10, arr.Count());
    arr.Clear();
    EXPECT_EQ (0, arr.Count());
}


TEST(ArraySequence_float, Add) {
    ArraySequence<float> arr = ArraySequence<float>();
    arr.Add(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr.Get(-1));
    EXPECT_ANY_THROW(arr.Get(1));
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

TEST(ArraySequence_float, Prepend) {
    ArraySequence<float> arr = ArraySequence<float>();
    arr.AddFirst(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr.Get(-1));
    EXPECT_ANY_THROW(arr.Get(1));
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

//TEST(ArraySequence_float, InsertAt) {
//    ArraySequence<float> arr = ArraySequence<float>(3);
//    arr[0] = 1;
//    arr[1] = 2;
//    arr[2] = 3;
//    arr.Insert(1, 4);
//    ASSERT_EQ (4, arr.Count());
//    EXPECT_EQ (1, arr[0]);
//    EXPECT_EQ (4, arr[1]);
//    EXPECT_EQ (2, arr[2]);
//    EXPECT_EQ (3, arr[3]);
//    EXPECT_EQ (1, arr.First());
//    EXPECT_EQ (3, arr.Last());
//
//    arr.Insert(0, 5);
//    ASSERT_EQ (5, arr.Count());
//    EXPECT_EQ (5, arr[0]);
//    EXPECT_EQ (1, arr[1]);
//    EXPECT_EQ (4, arr[2]);
//    EXPECT_EQ (2, arr[3]);
//    EXPECT_EQ (3, arr[4]);
//    EXPECT_EQ (5, arr.First());
//    EXPECT_EQ (3, arr.Last());
//
//    arr.Insert(arr.Count() - 1, 6);
//    ASSERT_EQ (6, arr.Count());
//    EXPECT_EQ (5, arr[0]);
//    EXPECT_EQ (1, arr[1]);
//    EXPECT_EQ (4, arr[2]);
//    EXPECT_EQ (2, arr[3]);
//    EXPECT_EQ (3, arr[4]);
//    EXPECT_EQ (6, arr[5]);
//    EXPECT_EQ (5, arr.First());
//    EXPECT_EQ (6, arr.Last());
//}

TEST(ArraySequence_float, PopFirst) {
    ArraySequence<float> arr = ArraySequence<float>(3);
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
    EXPECT_ANY_THROW (arr.Get(0));
    EXPECT_ANY_THROW(arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW (arr.RemoveFirst(););
}

TEST(ArraySequence_float, PopLast) {
    ArraySequence<float> arr = ArraySequence<float>(3);
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
    EXPECT_ANY_THROW (arr.Get(0));
    EXPECT_ANY_THROW (arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW(arr.RemoveLast());
}

TEST(ArraySequence_float, RemoveAt) {
    ArraySequence<float> arr = ArraySequence<float>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    ASSERT_ANY_THROW(arr.RemoveAt(-1));
    ASSERT_ANY_THROW(arr.RemoveAt(3));
    arr.RemoveAt(1);
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (3, arr[1]);
    ASSERT_ANY_THROW (arr.Get(2));
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.RemoveAt(0);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (3, arr.First());
    EXPECT_EQ (3, arr.Last());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr.Get(0));
    EXPECT_ANY_THROW (arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW(arr.RemoveLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));

    arr = ArraySequence<float>(2);
    arr[0] = 1;
    arr[1] = 2;

    arr.RemoveAt(1);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (1, arr.First());
    EXPECT_EQ (1, arr.Last());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr.Get(0));
    EXPECT_ANY_THROW (arr.First());
    EXPECT_ANY_THROW (arr.Last());
    EXPECT_ANY_THROW(arr.RemoveLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));
}

TEST(ArraySequence_float, InitFromArr) {
    float a[] = {1, 2, 3, 4, 5};
    EXPECT_ANY_THROW(ArraySequence<float>(a, -1));
    EXPECT_ANY_THROW(ArraySequence<float>(nullptr, 1));
    ArraySequence<float> arr = ArraySequence<float>(a, 5);
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
    EXPECT_ANY_THROW(arr.Get(5));
    ASSERT_EQ (5, arr.Count());
    arr.Set(0, 0);
    EXPECT_EQ (1, a[0]);
    EXPECT_EQ (0, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    arr = ArraySequence<float>(a, 0);
    ASSERT_EQ (0, arr.Count());

    arr = ArraySequence<float>(a);
    ASSERT_EQ (5, arr.Count());

    arr.Add(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr = ArraySequence<float>({1, 2, 3, 4, 5});
    ASSERT_EQ (5, arr.Count());

    arr.Add(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr = ArraySequence<float>{};
    ASSERT_EQ (0, arr.Count());
    arr.Add(6);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (6, arr[0]);
    EXPECT_ANY_THROW(arr.Get(1));
}

TEST(ArraySequence_float, InitFromArraySequence) {
    float a[] = {1, 2, 3, 4, 5, 6};
    ArraySequence<float> arr1 = ArraySequence<float>(a, 5);
    ASSERT_EQ (5, arr1.Count());
    EXPECT_ANY_THROW(arr1.Get(5));
    ArraySequence<float> arr2 = ArraySequence<float>(arr1);
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

    arr1 = ArraySequence<float>();
    arr2 = ArraySequence<float>(arr1);
    ASSERT_EQ (0, arr2.Count());
}

//TEST(ArraySequence_float, Concat) {
//    float a[] = {1, 2, 3, 4, 5};
//    ArraySequence<float> arr1 = ArraySequence<float>(a, 5);
//    ArraySequence<float> arr2 = ArraySequence<float>(arr1);
//    std::unique_ptr<ArraySequence<float>> arr3 = std::unique_ptr<ArraySequence<float>>(arr1.Concat(arr2));
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
//    ArraySequence<float> arr4 = ArraySequence<float>();
//    arr3 = std::unique_ptr<ArraySequence<float>>(arr1.Concat(arr4));
//    ASSERT_EQ (arr1.Count() + arr4.Count(), arr3->Count());
//    EXPECT_EQ (arr1[0], arr3->Get(0));
//    EXPECT_EQ (arr1[1], arr3->Get(1));
//    EXPECT_EQ (arr1[2], arr3->Get(2));
//    EXPECT_EQ (arr1[3], arr3->Get(3));
//    EXPECT_EQ (arr1[4], arr3->Get(4));
//}

TEST(ArraySequence_float, GetSubsequence) {
    float a[] = {1, 2, 3, 4, 5};
    ArraySequence<float> arr1 = ArraySequence<float>(a, 5);
    unique_ptr<ArraySequence<float>>
            arr2 = unique_ptr<ArraySequence<float>>(arr1.GetSubsequence(0, 0));
    ASSERT_EQ(arr2->Count(), 1);
    EXPECT_EQ (arr1[0], 1);
    EXPECT_ANY_THROW(arr2->Get(1));
    EXPECT_ANY_THROW(arr1.GetSubsequence(-1, 0));
    EXPECT_ANY_THROW(arr1.GetSubsequence(1, 0));
    EXPECT_ANY_THROW(arr1.GetSubsequence(1, 5));
    arr2 = unique_ptr<ArraySequence<float>>(arr1.GetSubsequence(0, 4));
    ASSERT_EQ(arr2->Count(), 5);
    EXPECT_EQ (arr1[0], arr2->Get(0));
    EXPECT_EQ (arr1[1], arr2->Get(1));
    EXPECT_EQ (arr1[2], arr2->Get(2));
    EXPECT_EQ (arr1[3], arr2->Get(3));
    EXPECT_EQ (arr1[4], arr2->Get(4));
    arr2 = unique_ptr<ArraySequence<float>>(arr1.GetSubsequence(2, 3));
    ASSERT_EQ(arr2->Count(), 2);
    EXPECT_EQ (arr1[2], arr2->Get(0));
    EXPECT_EQ (arr1[3], arr2->Get(1));
}



TEST(ArraySequence_int, Equals) {
    ArraySequence<int> arr{1, 2, 3};
    ArraySequence<int> arr1{1, 2};
    ArraySequence<int> arr2{1, 2, 3};
    ArraySequence<int> arr3{3, 2};
    EXPECT_TRUE(arr == arr2);
    EXPECT_FALSE(arr == arr1);
    EXPECT_FALSE(arr1 == arr3);
    ArraySequence<int> arr4{};
    ArraySequence<int> arr5{};
    EXPECT_TRUE(arr4 == arr5);
}
