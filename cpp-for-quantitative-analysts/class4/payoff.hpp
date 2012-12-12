#IFNDEF __C4_PAY_OFF_HPP
#DEFINE __C4_PAY_OFF_HPP

#include <algorithm>   // This is needed for the std::max comparison function, used in the pay-off calculations

class PayOff {
public:
    PayOff() {};            // Default (no parameter) constructor
    virtual ~PayOff() {};   // Virtual destructor

    // Overloaded () operator, turns the PayOff into an abstract function object
    virtual double operator() (const double& S) const = 0;
};

class PayOffCall : public PayOff {
private:
    double K;    // Strike price

public:
    PayOffCall(const double& K_) {};
    virtual ~PayOffCall() {};

    // Virtual function is now over-ridden (not pure-virtual anymore)
    virtual double operator() (const double& S) const; 
};

class PayOffPut : public PayOff {
private:
    double K;    // Strike

public:
    PayOffPut(const double& K_) {};
    virtual ~PayOffPut() {};
    virtual double operator() (const double& S) const;
};

class PayOffDigitalCall : public PayOff {
private:
    double K;   // Strike price

public:
    PayOffDigitalCall(const double& K_) {};
    virtual ~PayOffDigitalCall() {};
    virtual double operator() (const double& S) const; 
};

class PayOffDigitalPut : public PayOff {
private:
    double K;   // Strike price

public:
    PayOffDigitalPut(const double& K_) {};
    virtual ~PayOffDigitalPut() {};
    virtual double operator() (const double& S) const; 
};

class PayOffDoubleDigital : public PayOff {
private:
    double U;    // Upper strike barrier
    double D;    // Lower strike barrier

public:
    PayOffDoubleDigital(const double& K_) {};
    virtual ~PayOffDoubleDigital() {};    // Destructor still virtual for further inheritance
    virtual double operator() (const double& S) const;     // Pay-off is 1 if spot within strike barriers, 0 otherwise
};

#ENDIF
