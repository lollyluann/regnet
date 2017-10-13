#include<RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

using namespace Rcpp;
using namespace arma;

double Soft(double z, double lambda);
arma::vec Network(arma::mat& x, arma::vec& y, double lam1, double lam2, arma::vec b, double r, arma::mat& a, int n, int p);
arma::vec RunNet(arma::mat& x, arma::vec& y, double lam1, double lam2, arma::vec b, double r, arma::mat& a, int n, int p);


// [[Rcpp::export]]
arma::vec RunNet(arma::mat& x, arma::vec& y, double lam1, double lam2, arma::vec b, double r, arma::mat& a, int n, int p)
{
  int count = 0;
  arma::vec bnew;
  while(count < 20){
    bnew = Network(x, y, lam1, lam2, b, r, a, n, p);
    double dif = arma::accu(arma::abs(b - bnew))/n;
    if(dif < 0.001) break;
    else{
      b = bnew;
      count++;
    }
  }
  return(bnew);
}


arma::vec Network(arma::mat& x, arma::vec& y, double lam1, double lam2, arma::vec b, double r, arma::mat& a, int n, int p)
{
  arma::vec y0 = x * b;
  arma::vec pi = 1/(1+exp(-y0)), t = (y -pi)*4;
  for(int k = 0; k < (p+1); k++){
    double bold = b(k);
    double l = arma::accu(x.col(k) % t)/n + b(k);
    int _p = p - 1;
    if(k == 0) b(k) = l;
    else{
      int m = k;
      if(k > _p) m = _p;
      double z = l*0.25 + lam2 * arma::as_scalar(a.row(k-1).subvec(m, _p) * b.subvec(m+1, p));
      double u = 0.25 + lam2 * arma::accu(abs(a.row(k-1).subvec(m, _p)));
      if(std::abs(z) > (r*lam1*u)){
        b(k) = z/u;
      }
      else{
        b(k) = Soft(z, lam1)/(u - 1/r);
      }
    }
    t -= x.col(k) * (b(k) - bold);
  }
  return(b);
}

double Soft(double z, double lambda){
  if(z > lambda) return(z - lambda);
  else if(z < -lambda) return(z + lambda);
  else return(0);
}

