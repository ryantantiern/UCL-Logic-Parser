# UCL-Logic-Parser

C

This program works out whether a formula is true in a graph under the given variable assignment. 
It parses first order formulas in a language with no function symbols and one binary predicate (or, and, implies = V, ^, >)
A formula is defined by
                  φ ::= X[ts] | − φ | (φ ◦ φ) | Ez φ | Az φ
                  
