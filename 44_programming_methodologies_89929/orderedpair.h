#include <iostream>
    /* precondition for setFirst and setSecond: the values of first and second cannot be equal, except when they are both equal to DEFAULT_VALUE. */
    namespace cs_pairs 
    { 
        template <class T>
        class OrderedPair 
        {
            public:

                static const T DEFAULT_VALUE;

                OrderedPair(T newFirst = DEFAULT_VALUE, T newSecond = DEFAULT_VALUE);
                void setFirst(T newFirst);
                void setSecond(T newSecond);
                T getFirst() const;
                T getSecond() const;
                OrderedPair operator+(const OrderedPair& right) const;
                bool operator<(const OrderedPair& right) const;
                void print() const;


                /* precondition for setFirst and setSecond: the values of first and second cannot be equal, 
                except when they are both equal to DEFAULT_VALUE. */
                class DuplicateMemberError { };


            private:
                T first;
                T second;
        };
    
        template <class T>
        const T OrderedPair<T>::DEFAULT_VALUE = T();
    };
    // Leave the following const declaration commented out when you are testing the non-templated
    // version. Uncomment it when you begin converting to a templated version. // The templated version will require a template prefix as well as some minor edits to the code
    // const int OrderedPair::DEFAULT_VALUE = int();