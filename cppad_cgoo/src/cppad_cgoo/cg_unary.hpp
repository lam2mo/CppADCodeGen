#ifndef CPPAD_CG_UNARY_INCLUDED
#define	CPPAD_CG_UNARY_INCLUDED
/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2012 Ciengis

CppAD is distributed under multiple licenses. This distribution is under
the terms of the
                    Common Public License Version 1.0.

A copy of this license is included in the COPYING file of this distribution.
Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
-------------------------------------------------------------------------- */


namespace CppAD {

    template<class Base>
    inline CG<Base> CG<Base>::operator+() const {
        return CG<Base > (*this); // nothing to do
    }

    template<class Base>
    inline CG<Base> CG<Base>::operator-() const {
        if (isParameter()) {
            return CG<Base > (-getParameterValue());

        } else {
            return CG<Base>(*getCodeHandler(), new SourceCodeFragment<Base>(CGUnMinusOp, this->argument()));
        }
    }

}

#endif
