require import AllCore IntDiv CoreMap List Distr.


from Jasmin require import JModel_x86.

from JazzEC require import BArray1024.
import JWord.

lemma ge0_to_uint (w : W64.t) :
    0<= to_uint w by smt(W64.to_uint_cmp).

hint exact : ge0_to_uint.

from CryptoSpecs require import GFq.
import Zq.

op addwl(_as _bs : W32.t list) : W32.t list = map2 (W32.(+)) _as _bs.
op addcl(_as _bs : coeff list) : coeff list = map2 (Zq.(+)) _as _bs.

op ub32(b : int, w : W32.t) = to_uint w < b.
op sb32(b : int, w : W32.t) = -b <= to_sint w < b.

op ulift(_as : W32.t list) = map (incoeff \o W32.to_uint) _as.
op slift(_as : W32.t list) = map (incoeff \o to_sint) _as.

lemma uadd_lift _ba _bb _as _bs :
   _ba + _bb < W32.modulus =>
   all (ub32 _ba) _as =>
   all (ub32 _bb) _bs =>
     ulift (addwl _as _bs) = addcl (ulift _as) (ulift _bs) /\
     all (ub32 (_ba + _bb)) (addwl _as _bs).
admitted.

lemma sadd_lift _ba _bb _as _bs :
   _ba + _bb <= W32.modulus %/2 =>
   all (sb32 _ba) _as =>
   all (sb32 _bb) _bs =>
     slift (addwl _as _bs) = addcl (slift _as) (slift _bs) /\
     all (sb32 (_ba + _bb)) (addwl _as _bs).
admitted.

from JazzEC require import Ml_dsa_65_amd64.

op to_list32(_a : BArray1024.t) : W32.t list.

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




lemma polynomial_add_corr_ref_x86 (_a _b : BArray1024.t) :
   hoare [ Poly.polynomial__add :
     lhs = _a /\ rhs = _b ==>
        to_list32 res = addwl (to_list32 _a) (to_list32 _b)
         ].
proof.
proc. 
unroll for ^while.
(* use bdep here*)



conseq (polynomial_add_x86_ref_eq)
     (polynomial_add_corr _a _b) => /=.
+ move => &1 />.
  by exists ((lhs, rhs){1}).

by auto.  
qed.














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
