#ifndef CPPAD_CG_LANG_LATEX_CUSTOM_VAR_NAME_GEN_INCLUDED
#define CPPAD_CG_LANG_LATEX_CUSTOM_VAR_NAME_GEN_INCLUDED
/* --------------------------------------------------------------------------
 *  CppADCodeGen: C++ Algorithmic Differentiation with Source Code Generation:
 *    Copyright (C) 2014 Ciengis
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

namespace CppAD {
namespace cg {

/**
 * Creates variables names for the source code using a list of provided
 * custom names.
 * 
 * @author Joao Leal
 */
template<class Base>
class LangLatexCustomVariableNameGenerator : public LangLatexDefaultVariableNameGenerator<Base> {
protected:
    // the custom names for the dependent variables
    const std::vector<std::string> depNames_;
    // the custom names for the independent variables
    const std::vector<std::string> indepNames_;
public:

    LangLatexCustomVariableNameGenerator(const std::vector<std::string>& depNames,
                                         const std::vector<std::string>& indepNames,
                                         const std::string& depName = "y",
                                         const std::string& indepName = "x",
                                         const std::string& tmpName = "v",
                                         const std::string& tmpArrayName = "\\mathbf{a}",
                                         const std::string& tmpSparseArrayName = "\\mathbf{s}") :
        LangLatexDefaultVariableNameGenerator<Base>(depName, indepName, tmpName, tmpArrayName, tmpSparseArrayName),
        depNames_(depNames),
        indepNames_(indepNames) {
    }

    virtual std::string generateDependent(size_t index) override {
        if (index < depNames_.size() && !depNames_[index].empty()) {
            return depNames_[index];
        } else {
            return LangLatexDefaultVariableNameGenerator<Base>::generateDependent(index);
        }
    }

    virtual std::string generateIndependent(const OperationNode<Base>& independent) override {
        size_t index = independent.getVariableID() - 1;
        if (index < indepNames_.size() && !indepNames_[index].empty()) {
            return indepNames_[index];
        } else {
            return LangLatexDefaultVariableNameGenerator<Base>::generateIndependent(independent);
        }
    }

    virtual bool isConsecutiveInIndepArray(const OperationNode<Base>& indepFirst,
                                           const OperationNode<Base>& indepSecond) override {
        size_t index1 = indepFirst.getVariableID() - 1;
        size_t index2 = indepSecond.getVariableID() - 1;

        if ((index1 > indepNames_.size() || indepNames_[index1].empty()) &&
                (index2 > indepNames_.size() || indepNames_[index2].empty())) {
            return index1 + 1 == index2;
        } else {
            return false; // individual names used (not elements of arrays)
        }
    }

    virtual bool isInSameIndependentArray(const OperationNode<Base>& indep1,
                                          const OperationNode<Base>& indep2) override {
        size_t index1 = indep1.getVariableID() - 1;
        size_t index2 = indep2.getVariableID() - 1;

        return (index1 > indepNames_.size() || indepNames_[index1].empty()) &&
                (index2 > indepNames_.size() || indepNames_[index2].empty());
    }

    inline virtual ~LangLatexCustomVariableNameGenerator() {
    }

};

} // END cg namespace
} // END CppAD namespace

#endif