require import AllCore IntDiv CoreMap List Distr.


from Jasmin require import JModel_x86.

from JazzEC require import BArray1024.
import JWord.

lemma ge0_to_uint (w : W64.t) :
    0<= to_uint w by smt(W64.to_uint_cmp).

hint exact : ge0_to_uint.

module Poly = {
proc polynomial__add(lhs : BArray1024.t, rhs : BArray1024.t) : BArray1024.t = {
    var i : int;
    var lhs_coefficient : W32.t;
    var rhs_coefficient : W32.t;
    var sum : BArray1024.t;
    sum <- witness;
    i <- 0;
    while (i < 256){
      lhs_coefficient <- get32d lhs (4 * i);
      rhs_coefficient <- get32d rhs (4 * i);
      lhs_coefficient <- lhs_coefficient + rhs_coefficient;
      sum <- set32d sum (4 * i) lhs_coefficient;
      i <- i + 1;
    }
    return sum;
  }
}.

lemma polynomial_add_corr (_a _b : BArray1024.t) :
   hoare [ Poly.polynomial__add :
     lhs = _a /\ rhs = _b ==>
        forall k, 0 <= k < 256 =>
           get32 res k = get32 _a k + get32 _b k
         ].
proc => /=.
while ( #pre /\
    0 <= i <= 256 /\
    forall k, 0 <=k < i =>
      get32d sum (4 * k) = get32d _a (4 * k) + get32d _b (4 * k));
by auto => />;smt(get_set32E).
qed.

from JazzEC require import Ml_dsa_65_amd64.


lemma polynomial_add_x86_ref_eq :
  equiv [ Ml_dsa_65_amd64.M.polynomial__add ~
          Poly.polynomial__add  :
     ={lhs,rhs} ==> ={res} ].
proc => /=. 
while (#pre /\ to_uint i{1} = i{2} /\ 0 <= i{2} <=256 /\
     (forall k, 0<=k<i{2} =>
       get32 sum{1} k = get32 sum{2} k) ).
+ auto => /> &1 &2 ???; 
  rewrite !ultE !to_uintD_small /=; 1:smt().
  by smt(get_set32E).

auto => /> &1; split; 1:smt().
move => ? sl sr;  rewrite !ultE /= => il ???  H. 
apply BArray1024.ext_eq => x ?.
by smt(ext_eq32).
qed.

lemma polynomial_add_corr_ref_x86 (_a _b : BArray1024.t) :
   hoare [ Ml_dsa_65_amd64.M.polynomial__add :
     lhs = _a /\ rhs = _b ==>
        forall k, 0 <= k < 256 =>
           get32 res k = get32 _a k + get32 _b k
         ].
proof.
conseq (polynomial_add_x86_ref_eq)
     (polynomial_add_corr _a _b) => /=.
+ move => &1 />.
  by exists ((lhs, rhs){1}).

by auto.  
qed.



from Jasmin require import JModel_m4.

from JazzEC require import Ml_dsa_65_arm_m4.

lemma polynomial_add_arm_eq :
  equiv [ Ml_dsa_65_arm_m4.M(Syscall).__poly_add_inplace ~
          Poly.polynomial__add  :
     a{1} = lhs{2} /\ b{1} = rhs{2}  ==> ={res} ].
proc => /=. 
admitted.

from Jasmin require import JModel_riscv.

from JazzEC require import Ml_dsa_65_riscv.


lemma polynomial_add_arm_risc_eq :
  equiv [ Ml_dsa_65_arm_m4.M(Syscall).__poly_add_inplace ~
          Ml_dsa_65_riscv.M(Syscall).__poly_add_inplace  :
    ={a,b}  ==> ={res} ].
proc => /=. 
by sim.
qed.
