#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>

double gaussian_box_muller() {
  double x = 0.0;
  double y = 0.0;
  double euclid_sq = 0.0;
    
  do {
    x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    euclid_sq = x*x + y*y;
  } while (euclid_sq >= 1.0);

  return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}

double payoff_double_digital(const double& K_L, const double& K_U, const double& x) {
  if (x >= K_L && x <= K_U) {
    return 1.0;
  } else {
    return 0.0;
  }
} 

double monte_carlo_double_digital_price(const int& num_sims, const double& S, const double& K_L, const double& K_U, const double& r, const double& v, const double& T) {
  double S_adjust = S * exp(T*(r-0.5*v*v));
  double S_cur = 0.0;
  double payoff_sum = 0.0;

  for (int i=0; i<num_sims; i++) {
    double gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * exp(sqrt(v*v*T)*gauss_bm);
    payoff_sum += payoff_double_digital(K_L, K_U, S_cur);
  }

  return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

int main(int argc, char **argv) {
  // First we create the parameter list
  int num_sims = 10000000;   // Number of simulated asset paths
  double S = 100.0;  // Option price
  double K_L = 100.0;  // Lower strike price
  double K_U = 120.0;  // Upper strike price
  double r = 0.05;   // Risk-free rate (5%)
  double v = 0.2;    // Volatility of the underlying (20%)
  double T = 1.0;    // One year until expiry

  // Then we calculate the double digital values
  double dd = monte_carlo_double_digital_price(num_sims, S, K_L, K_U, r, v, T);

  // Finally we output the parameters and prices
  std::cout << "Number of Paths: " << num_sims << std::endl;
  std::cout << "Underlying:      " << S << std::endl;
  std::cout << "Lower Strike:    " << K_L << std::endl;
  std::cout << "Upper Strike:    " << K_U << std::endl;
  std::cout << "Risk-Free Rate:  " << r << std::endl;
  std::cout << "Volatility:      " << v << std::endl;
  std::cout << "Maturity:        " << T << std::endl;

  std::cout << "Options Price:   " << dd << std::endl;

  return 0;
}
