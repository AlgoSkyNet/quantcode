#include <iostream>
#include <cmath>

// An approximation to the cumulative distribution function
// for the standard normal distribution
// Note: This is a recursive function
double norm_cdf(const double& x) {
    double k = 1.0/(1.0 + 0.2316419*x);
    double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

    if (x >= 0.0) {
        return (1.0 - (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x) * k_sum);
    } else {
        return 1.0 - norm_cdf(-x);
    }
}

// The function "a_1" which forms part of the analytical price
double a_1(const double& S,    // Spot price
           const double& H,    // Min/max of asset price over period
           const double& r,    // Risk free rate
           const double& v,    // Volatility of underlying asset
           const double& T) {  // Time to expiry
  double num = log(S/H) + (r + 0.5*v*v) * T;
  double denom = v * sqrt(T);
  return num/denom;
}

// The function "a_2" which forms part of the analytical price
double a_2(const double& S, 
           const double& H,
           const double& r,
           const double& v,
           const double& T) {
  return a_1(S, H, r, v, T) - v * sqrt(T);
}

// The function "a_3" which forms part of the analytical price
double a_3(const double& S, 
           const double& H,
           const double& r,
           const double& v,
           const double& T) {
  return a_1(S, H, r, v, T) - (2.0*r*sqrt(T)/v);
}

// Pricing a Lookback European Call option
double lookback_call(const double& S,
                     const double& m,  // Minimum price of asset over period
                     const double& r,
                     const double& v,
                     const double& T) {
  double a1 = a_1(S,m,r,v,T);
  double a2 = a_2(S,m,r,v,T);
  double a3 = a_3(S,m,r,v,T);

  double term1 = S * norm_cdf(a1);
  double term2 = m * exp(-r*T) * norm_cdf(a2);
  double mult = S*v*v/(2.0*r);
  double term3 = norm_cdf(-a1) - exp(-r*T) * pow((m/S),((2*r)/(v*v))) * norm_cdf(-a3);
  
  return term1 - term2 - mult * term3;
}

// Pricing a Lookback European Put option
double lookback_put(const double& S,
                    const double& M,  // Maximum price of asset over period
                    const double& r,
                    const double& v,
                    const double& T) {
  double a1 = a_1(S,M,r,v,T);
  double a2 = a_2(S,M,r,v,T);
  double a3 = a_3(S,M,r,v,T);
  
  double term1 = -S * norm_cdf(-a1);
  double term2 = M * exp(-r*T) * norm_cdf(-a2);
  double mult = S*v*v/(2.0*r);
  double term3 = norm_cdf(a1) - exp(-r*T) * pow((M/S),((2*r)/(v*v))) * norm_cdf(a3);

  return term1 + term2 + mult * term3;
}

int main(int argc, char **argv) {
  double S = 100.0;    // Spot price
  double m = 90.0;     // Minimum spot over period 
  double M = 110.0;    // Maximum spot over period
  double r = 0.1;      // Risk-free rate (10%)
  double v = 0.3;      // Volatility of the underlying (30%)
  double T = 1.0;      // One year until expiry

  // Calculate the lookback prices for calls and puts
  double lookback_call_price = lookback_call(S, m, r, v, T);
  double lookback_put_price = lookback_put(S, M, r, v, T);

  // Finally we output the parameters and prices
  std::cout << "Underlying:      " << S << std::endl;
  std::cout << "Min spot:        " << m << std::endl;
  std::cout << "Max spot:        " << M << std::endl;
  std::cout << "Risk-Free Rate:  " << r << std::endl;
  std::cout << "Volatility:      " << v << std::endl;
  std::cout << "Maturity:        " << T << std::endl;

  std::cout << "Lookback Call Price:     " << lookback_call_price << std::endl;
  std::cout << "Lookback Put Price:      " << lookback_put_price << std::endl;

  return 0;
}
