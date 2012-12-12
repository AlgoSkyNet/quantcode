#IFNDEF __C4_PAY_OFF_CPP
#DEFINE __C4_PAY_OFF_CPP

// ======
// PayOff
// ======

// PayOff is an ABSTRACT BASE CLASS and hence can never be instantiated directly. Instead
// subclasses must be created, which override any PURE VIRTUAL METHODS. There is no requirement to 
// implement any of the methods specified in the header file. We are simply specifying an INTERFACE
// that all subclasses must adhere to. The interface for a PayOff object (and its subclasses) is that
// it must override the operator() method, by specifying a pay-off function. Any private data used 
// for this must be provided by a parameter constructor.

// ==========
// PayOffCall
// ==========

// Constructor with single strike parameter
PayOffCall::PayOffCall(const double& _K) { K = _K; }

// Destructor (no need to use virtual keyword in source file)
PayOffCall::~PayOffCall() {}

// Over-ridden operator() method, which turns PayOffCall into a function object
double PayOffCall::operator() (const double& S) const {
    return std::max(S-K, 0.0);  // Standard European call pay-off 
}

// =========
// PayOffPut
// =========

// Constructor with single strike parameter
PayOffPut::PayOffPut(const double& _K) {
    K = _K;
}

// Destructor (no need to use virtual keyword in source file)
PayOffPut::~PayOffPut() {}

// Over-ridden operator() method, which turns PayOffPut into a function object
double PayOffPut::operator() (const double& S) const {
    return std::max(K-S, 0.0);  // Standard European put pay-off
}

// =================
// PayOffDigitalCall
// =================

// Constructor with single strike parameter
PayOffDigitalCall::PayOffDigitalCall(const double& _K) {
    K = _K;
}

// Destructor (no need to use virtual keyword in source file)
PayOffDigitalCall::~PayOffDigitalCall() {}

// Over-ridden operator() method, which turns PayOffDigitalCall into a function object
double PayOffDigitalCall::operator() (const double& S) const {
    if S > K {
        return 1.0;
    } else {
        return 0.0;
    }
}

// ================
// PayOffDigitalPut
// ================

// Constructor with single strike parameter
PayOffDigitalPut::PayOffDigitalPut(const double& _K) {
    K = _K;
}

// Destructor (no need to use virtual keyword in source file)
PayOffDigitalPut::~PayOffDigitalPut() {}

// Over-ridden operator() method, which turns PayOffDigitalPut into a function object
double PayOffDigitalPut::operator() (const double& S) const {
    if S < K {
        return 1.0;
    } else {
        return 0.0;
    }
}

// ===================
// PayOffDoubleDigital
// ===================

// Constructor with two strike parameters, upper and lower barrier
PayOffDoubleDigital::PayOffDoubleDigital(const double& _U, const double& _D) {
    U = _U;
    D = _D;
}

// Destructor (no need to use virtual keyword in source file)
PayOffDoubleDigital::~PayOffDoubleDigital() {}

// Over-ridden operator() method, which turns PayOffDoubleDigital into a function object
double PayOffDoubleDigital::operator() (const double& S) const {
    if S >= D && S <= U {
        return 1.0;
    } else {
        return 0.0;
    }
}

#ENDIF
