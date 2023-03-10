# Symmetry_Convert
Convert an xyz symmetry polynomial to basic ternary symmetry polynomial.

# How to use?
Input in stdin should end with `Ctrl+Z` (If use file, you needn't.)

Input should be `4k` integers, each `4` integers like `l a b c` means <code>lx<sup>a</sup>y<sup>b</sup>z<sup>c</sup></code>.

Like `5 1 0 0 5 0 1 0 5 0 0 1 3 0 0 0` means `5x+5y+5z+3`

Output will be a polynomial of `p,q,r`, which `p` means `x+y+z`, `q` means `xy+yz+zx`, `r` means `xyz`.
