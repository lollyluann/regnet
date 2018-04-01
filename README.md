
<!-- README.md is generated from README.Rmd. Please edit that file -->
regnet
======

[![Travis-CI Build Status](https://travis-ci.org/jrhub/regnet.svg?branch=master)](https://travis-ci.org/jrhub/regnet)

[![CRAN](https://www.r-pkg.org/badges/version/regnet)](https://cran.r-project.org/package=regnet)

Network-based regularization has achieved success in variable selection for high-dimensional biological data due to its ability to incorporate correlations between genomic features. This package provides procedures for fitting network-based regularization, minimax concave penalty (MCP) and lasso penalty for generalized linear models. This current version, regnet0.3.0, focuses on binary and survival outcomes. Functions for continuous and other regularization methods will be included in the forthcoming upgraded versions.

How to install
--------------

-   To install from github, run these two lines of code in R

        install.packages("devtools")
        devtools::install_github("jrhub/regnet")

-   Released versions of regnet are available on R CRAN [(link)](https://cran.r-project.org/package=regnet), and can be installed within R via

        install.packages("regnet")

Examples
--------

### Survival response

#### Example.1 (Robust Network)

    data(SurvExample)
    X = rgn.surv$X
    Y = rgn.surv$Y
    clv = c(1:5) # variable 1 to 5 are clinical variables, we choose not to penalize them here.
    out = cv.regnet(X, Y, response="survival", penalty="network", clv=clv, robust=TRUE, verbo = TRUE)
    out$lambda

    b = regnet(X, Y, "survival", "network", out$lambda[1,1], out$lambda[1,2], clv=clv, robust=TRUE)  
    index = which(rgn.surv$beta != 0)  
    pos = which(b != 0)  
    tp = length(intersect(index, pos))  
    fp = length(pos) - tp  
    list(tp=tp, fp=fp)  

### Binary response

#### Example.2 (Network Logistic)

    data(LogisticExample)
    X = rgn.logi$X
    Y = rgn.logi$Y
    out = cv.regnet(X, Y, response="binary", penalty="network", folds=5, r = 4.5)  
    out$lambda  
    b = regnet(X, Y, "binary", "network", out$lambda[1,1], out$lambda[1,2], r = 4.5)
    index = which(rgn.logi$beta != 0)  
    pos = which(b != 0)  
    tp = length(intersect(index, pos))  
    fp = length(pos) - tp  
    list(tp=tp, fp=fp)  

News
----

### regnet 0.2.0 \[2017-10-14\]

Provides c++ implementation for coordinate descent algorithms. This update significantly increases the speed of cross-validation functions in this package.

Methods
-------

This package provides implementation for methods proposed in

-   Ren, J., He, T., Li, Y., Liu, S., Du, Y., Jiang, Y., Wu, C. (2017). Network-based regularization for high dimensional SNP data in the case-control study of Type 2 diabetes. [BMC Genetics, 18(1):44](https://doi.org/10.1186/s12863-017-0495-5)
