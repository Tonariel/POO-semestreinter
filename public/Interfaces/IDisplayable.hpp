#ifndef IDISPLAYABLE_HPP
#define IDISPLAYABLE_HPP

class IDisplayable {
public:
    virtual ~IDisplayable() = default;

    virtual void GetInfo() const = 0;
};

#endif
