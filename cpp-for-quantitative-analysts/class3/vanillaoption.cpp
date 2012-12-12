#IFNDEF __C3_VANILLA_OPTION_CPP
#DEFINE __C3_VANILLA_OPTION_CPP

#include "vanillaoption.hpp"   // We need to import the declaration header
#include <cmath>   // Useful mathematical functions such as square root, log and exp

// Initialises the member data
void VanillaOption::init() {
    K = 100.0;    // Strike is the same as spot in this example
    r = 0.05;     // Interest rate of 5%
    T = 1.0;      // One year until maturity
    S = 100.0;    // Option is "at the money" as spot equals the strike.
    sigma = 0.2;  // 20% volatility
}

// Copies the member data 
void VanillaOption::copy(const VanillaOption& rhs) {
    K = rhs.getK();
    r = rhs.getr();
    T = rhs.getT();
    S = rhs.getS();
    sigma = rhs.getsigma();
}

// Default constructor
VanillaOption::VanillaOption() { init(); }

// Parameter constructor
VanillaOption::VanillaOption(const double& _K, const double& _r, const double& _T, const double& _S, const double& _sigma) {
    // The following may seem contrived. In fact, a better way to assign these
    // values is via a MEMBER INITIALISATION LIST, which we will discuss in 
    // later lessons. Also notice that we are not checking whether the values
    // make any sense (for instance what is a negative volatility?!), and thus
    // we are just "blindly assigning". A production code would utilise checks
    // to make sure the quantities are valid.
    K = _K;
    r = _r;
    T = _T;
    S = _S;
    sigma = _sigma;
}

// Copy constructor
VanillaOption::VanillaOption(const VanillaOption& rhs) {
    // This implementation of a copy function is not strictly necessary as
    // the compiler is capable of producing the following code itself. A copy 
    // constructor IS necessary when memory is allocated on the HEAP, and not 
    // on the STACK, as these simple types are (similarly for the assignment 
    // operator - it is also able to be generated via the compiler)
    copy(rhs);
}

// Assignment operator
VanillaOption& VanillaOption::operator=(const VanillaOption& rhs) {
    // Now you can see why the copy method (and the init method) is useful, as it
    // allows us to employ the DRY (Do-not Repeat Yourself) paradigm. If we hadn't
    // created the copy method, we would be duplicating code by having the same 
    // copy functionality in both the copy constructor and the assignment operator

    // Assignment operators can be tricky to understand at first glance: 
    // The code below states that if we try to assign an object to itself,
    // then just return the original object, via a mechanism known
    // as POINTER DEREFERENCING. In simple terms, it means follow the pointer ("this") 
    // and get hold of the underlying object. Otherwise, copy the object and then 
    // return a dereferenced pointer to the object, as it has now been copied!
    // This stops the code carrying out unnecessary copying (which can be a performance hit)
    if (this == &rhs) return *this;
    copy(rhs);
    return *this;
}

// Destructor
VanillaOption::~VanillaOption() {
    // Empty, as the compiler does the work of cleaning up the simple types for us
}

// Public access for the strike price, K
double VanillaOption::getK() const {
  return K;
}

// Public access for the interest rate, r
double VanillaOption::getr() const {
  return r;
}

// Public access for the maturity time, T
double VanillaOption::getT() const {
  return T;
}

// Public access for the underlying price, S
double VanillaOption::getK() const {
  return S;
}

// Public access for the volatility of the underlying, sigma
double VanillaOption::getK() const {
  return sigma;
}

// Calculates the call price of the option
// This function is post-marked CONST because it is not modifying any
// underlying member data, such SELECTING it
double VanillaOption::calc_call_price() const {
    // This is the analytical call price NOT a Partial Differential Equation
    // solver OR a Monte Carlo simulator!
    // I will assume you are familiar with this formula, it can be found on any
    // introductory book on options pricing such as Joshi or Wilmott
    double sigma_sqrt_T = sigma * sqrt(T);
    double d_1 = ( log(S/K) + sigma * sigma * 0.5 * T ) / sigma_sqrt_T;
    double d_2 = d_1 - sigma_sqrt_T;
    return (S * exp(-r*T) * N(d_1)) - (K * exp(-r*T) * N(d_2));
}

// Calculate the put price of the option 
double VanillaOption::calc_put_price() const {
    // Similar, but not the same, as the call price
    double sigma_sqrt_T = sigma * sqrt(T);
    double d_1 = ( log(S/K) + sigma * sigma * 0.5 * T ) / sigma_sqrt_T;
    double d_2 = d_1 - sigma_sqrt_T;
    return (K * exp(-r*T) * N(-d_2)) - (S * exp(-r*T) * N(-d_1));
}

#ENDIF
