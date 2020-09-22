/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */
#include "deque.h"

/* Constructor for the Deque class */
template <class T>
Deque<T>::Deque(){
    /**
     * @todo Your code here! 
     */
     k1=0;
     k2=0;
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T const& newItem)
{
    /**
     * @todo Your code here! 
     */
     data.push_back(newItem);
     k2++;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The leftmost item of the Deque.
 */
template <class T>
T Deque<T>::popL() {
    /**
     * @todo Your code here! 
     */
         T leftMost = data[k1];

         k1++;
         k2--;

         if (k2<=k1) {
             //resizing
             vector <T> newData;
             for (int i = k1; i < k1 + k2; i++) {
                 newData.push_back(data[i]);
             }
             //do I need to delete something?
             data = newData;
             k1 = 0;
         }
         return leftMost;
     }


/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The rightmost item of the Deque.
 */
template <class T>
T Deque<T>::popR() {
    /**
     * @todo Your code here! 
     */
        int rear = k1 + k2 - 1;
        T rightMost = data[rear];
        data.pop_back();

        k2--;
        if (k2 <= k1) {
            vector <T> newData;
            for (int i = k1; i < k1 + k2; i++) {
                newData.push_back(data[i]);
            }

            //do I need to delete something?
            data = newData;
            k1 = 0;
        }
        return rightMost;
}


/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the left of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    /**
     * @todo Your code here! 
     */

        T left = data[k1];
        return left;
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    /**
     * @todo Your code here! 
    */

        int rear = k1 + k2 - 1;
        T right = data[rear];
        return right;
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const {
    /**
     * @todo Your code here! 
     */
    return k2 == 0;
}

//template <class T>
//int Deque<T>::getk1() {
//    return k1;
//}
//
//
//
//template <class T>
//int Deque<T>::getk2() {
//    return k2;
//}




//k1 -> index of first element
//k2 -> how many element == 0 ? empty?
//

//k1 = 0 k2 = 0
//nothing k1 = -1, k2 = -1
//pushL 6 => k1 = 0, k2 = 0
//pushR 8 => k1 = 0, k2 = 1
//-
//k1 = 0
//k2 = 0