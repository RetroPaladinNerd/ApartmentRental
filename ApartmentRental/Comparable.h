#ifndef COMPARABLE_H
#define COMPARABLE_H

class Comparable {
public:
    virtual ~Comparable() = default;

    virtual void compareApartmentsFromDB(int apartmentId1, int apartmentId2) const = 0;
};

#endif // COMPARABLE_H
