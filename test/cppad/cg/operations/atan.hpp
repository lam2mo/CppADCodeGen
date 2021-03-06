#ifndef CPPAD_CG_TEST_ATAN_INCLUDED
#define CPPAD_CG_TEST_ATAN_INCLUDED
/* --------------------------------------------------------------------------
 *  CppADCodeGen: C++ Algorithmic Differentiation with Source Code Generation:
 *    Copyright (C) 2012 Ciengis
 *
 *  CppADCodeGen is distributed under multiple licenses:
 *
 *   - Eclipse Public License Version 1.0 (EPL1), and
 *   - GNU General Public License Version 3 (GPL3).
 *
 *  EPL1 terms and conditions can be found in the file "epl-v10.txt", while
 *  terms and conditions for the GPL3 can be found in the file "gpl3.txt".
 * ----------------------------------------------------------------------------
 * Author: Joao Leal
 */

#include <assert.h>

template<class T>
CppAD::ADFun<T>* AtanTestOneFunc(const std::vector<CppAD::AD<T> >& u) {
    using CppAD::atan;
    using namespace CppAD;

    assert(u.size() == 1);

    size_t s = 0;

    // some temporary values
    AD<T> x = cos(u[s]);
    AD<T> y = sin(u[s]);
    AD<T> z = y / x; // tan(s)

    // dependent variable vector and indices
    std::vector< AD<T> > Z(1);
    size_t a = 0;

    // dependent variable values
    Z[a] = atan(z); // atan( tan(s) )

    // create f: U -> Z and vectors used for derivative calculations
    return new ADFun<T > (u, Z);
}

template<class T>
CppAD::ADFun<T>* AtanTestTwoFunc(const std::vector<CppAD::AD<T> >& u) {
    using CppAD::atan;
    using CppAD::sin;
    using CppAD::cos;
    using namespace CppAD;

    assert(u.size() == 1);

    // a temporary values
    AD<T> x = sin(u[0]) / cos(u[0]);

    // dependent variable vector 
    std::vector< AD<T> > Z(1);
    Z[0] = atan(x); // atan( tan(u) )

    // create f: U -> Z and vectors used for derivative calculations
    return new ADFun<T > (u, Z);
}

#endif