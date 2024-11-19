#ifndef ISORTER_H
#define ISORTER_H

#include "sequence.h"

template <typename T>
class ISorter {
public:
    virtual Sequence<T>* Sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) = 0;
    virtual ~ISorter() = default;
};

#endif