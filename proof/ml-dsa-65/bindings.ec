require import AllCore List IntDiv QFABV.
from Jasmin require import JModel_x86.
(* require import Array4 Array5 Array6 Array7 Array9 Array24 Array25 Array32 Array256 Array768 Array960. 
require import WArray32 WArray512 WArray960 WArray1536. *)

import BitEncoding BS2Int BitChunking.

(* require import JWord_extra. *)

(* ----------- BEGIN BOOL BINDINGS ---------- *)
op bool2bits (b : bool) : bool list = [b].
op bits2bool (b: bool list) : bool = List.nth false b 0.

op i2b (i : int) = (i %% 2 <> 0).
op b2si (b: bool) = 0.

bind bitstring bool2bits bits2bool b2i b2si i2b bool 1.
realize size_tolist by auto.
realize tolistP by auto.
realize oflistP by rewrite /bool2bits /bits2bool;smt(size_eq1).
realize ofintP by rewrite /bits2bool /int2bs => i; rewrite (nth_mkseq false) //. 
realize touintP by rewrite /bool2bits /= => bv; rewrite bs2int_cons bs2int_nil /=. 
realize tosintP by move => bv => //. 

bind op bool (/\) "and".
realize bvandP by move=> bv1 bv2; rewrite /bool2bits /#.

(* ----------- BEGIN W8 BINDINGS ---------- *)
bind bitstring W8.w2bits W8.bits2w W8.to_uint W8.to_sint W8.of_int W8.t 8.
realize size_tolist by auto.
realize tolistP by auto.
realize oflistP by smt(W8.bits2wK). 
realize ofintP by move => *;rewrite /of_int int2bs_mod.
realize tosintP. move => bv /=;rewrite /to_sint /smod /BVA_Top_JWord_W8_t.msb.
have -> /=: nth false (w2bits bv) (8 - 1) = 2 ^ (8 - 1) <= to_uint bv; last by smt().
rewrite /to_uint. 
rewrite -{2}(cat_take_drop 7 (w2bits bv)).
rewrite bs2int_cat size_take 1:// W8.size_w2bits /=.
rewrite -bs2int_div 1:// /= get_to_uint /=.
rewrite -bs2int_mod 1:// /= /to_uint.
by smt(bs2int_range mem_range W8.size_w2bits pow2_8).
qed.
realize touintP by smt().


(* -------------------------------------------------------------------- *)
bind op [W8.t & bool] W8."_.[_]" "get".

realize bvgetP by done.

(* -------------------------------------------------------------------- *)
bind op W8.t W8.andw "and".

realize bvandP.
proof.
move=> w1 w2; apply/(eq_from_nth witness).
- by rewrite size_map size_zip !size_w2bits.
rewrite size_w2bits => i rg_i; rewrite (nth_map witness) /=.
- by rewrite size_zip !size_w2bits.
rewrite nth_zip_cond /= size_zip !size_w2bits lez_minl 1:// /=.
rewrite 2?iftrue ~-1:/# /=.
rewrite [nth _ (w2bits w1) _](nth_change_dfl false) ?size_w2bits 1:/#.
rewrite [nth _ (w2bits w2) _](nth_change_dfl false) ?size_w2bits 1:/#.
by rewrite !get_w2bits w2bitsE nth_mkseq //#.
qed.



(* ----------- BEGIN W32 BINDINGS ---------- *)

bind bitstring W32.w2bits W32.bits2w W32.to_uint W32.to_sint W32.of_int W32.t 32.
realize size_tolist by auto.
realize tolistP by auto.
realize oflistP by smt(W32.bits2wK). 
realize ofintP by move => *;rewrite /of_int int2bs_mod.
realize tosintP. move => bv /=;rewrite /to_sint /smod /BVA_Top_JWord_W32_t.msb.
have -> /=: nth false (w2bits bv) (32 - 1) = 2 ^ (32 - 1) <= to_uint bv; last by smt().
rewrite /to_uint. 
rewrite -{2}(cat_take_drop 31 (w2bits bv)).
rewrite bs2int_cat size_take 1:// W32.size_w2bits /=.
rewrite -bs2int_div 1:// /= get_to_uint /=.
rewrite -bs2int_mod 1:// /= /to_uint.
by smt(bs2int_range mem_range W32.size_w2bits pow2_32).
qed.
realize touintP by smt().

bind op W32.t W32.( + ) "add".
realize bvaddP by exact W32.to_uintD.


bind op W32.t W32.( * ) "mul".
realize bvmulP by exact W32.to_uintM. 

op W32_sub (a : W32.t, b: W32.t) : W32.t = 
  a - b.

bind op W32.t W32_sub "sub".
realize bvsubP by  rewrite /W32_sub => bv1 bv2; rewrite W32.to_uintD to_uintN /= /#.

bind op W32.t W32.andw "and".
realize bvandP. 
rewrite /andw /map2 => bv1 bv2.
apply (eq_from_nth false);1: rewrite size_map size_zip !size_w2bits /#. 
move => i; rewrite size_w2bits /= => ib.
rewrite initiE 1:/# (nth_map (false,false)) /=;1: rewrite size_zip !size_w2bits /#. 
by rewrite !nth_zip /=;1:smt(W32.size_w2bits).
qed.

bind op W32.t W32.orw "or".
realize bvorP. 
rewrite /orw /map2 => bv1 bv2.
apply (eq_from_nth false);1: rewrite size_map size_zip !size_w2bits /#. 
move => i; rewrite size_w2bits /= => ib.
rewrite initiE 1:/# (nth_map (false,false)) /=;1: rewrite size_zip !size_w2bits /#. 
by rewrite !nth_zip /=;1:smt(W32.size_w2bits).
qed.

op sll_32 (w1 w2 : W32.t) : W32.t =
 if (32 <= to_uint w2)
 then W32.zero
 else  w1 `<<` (truncateu8 w2).

bind op [W32.t] sll_32 "shl".
realize bvshlP.
rewrite /sll_32 => bv1 bv2.
case : (32 <= to_uint bv2); last first.
+ rewrite /(`<<`) W32.to_uint_shl; 1: by smt(W8.to_uint_cmp).
  rewrite /truncateu8  => bv2bnd />.
  rewrite (pmod_small (to_uint bv2) _); smt(W32.to_uint_cmp).
move => *. 
have -> : to_uint bv2 = (to_uint bv2 - 32) + 32 by ring. 
by rewrite exprD_nneg 1,2:/# /= /#.
qed.

op srl_32 (w1 w2 : W32.t) : W32.t =
  if 32 <= (to_uint w2) then W32.zero else
  w1 `>>` (truncateu8 w2).

bind op [W32.t] srl_32 "shr".
realize bvshrP.
rewrite /srl_32 => bv1 bv2.
case : (32 <= to_uint bv2); last first.
+ rewrite /(`>>`) W32.to_uint_shr; 1: by smt(W8.to_uint_cmp).
  rewrite /truncateu8  => bv2bnd />.
  rewrite (pmod_small (to_uint bv2) _); smt(W32.to_uint_cmp).
move => *. 
have -> : to_uint bv2 = (to_uint bv2 - 32) + 32 by ring. 
rewrite exprD_nneg 1,2:/# /=. 
smt(StdOrder.IntOrder.expr_gt0 W32.to_uint_cmp pow2_32).
qed.

op sra_32 (w1 w2 : W32.t) : W32.t =
 W32.sar w1 (to_uint w2).
(*
  if (32 <= to_uint w2) then W32.zero else w1 `|>>` (truncateu8 w2).
*)
(* 
bind op [W32.t] sra_32 "ashr".
realize bvashrP.
move => bv1 bv2; rewrite W32_sar_div; smt(W32.to_uint_cmp).
qed.
*)

bind op [W32.t & W8.t] W4u8.truncateu8 "truncate".
realize bvtruncateP.
move => mv; rewrite /truncateu8 /W32.w2bits take_mkseq 1:// /= /w2bits.
apply (eq_from_nth witness);1: by smt(size_mkseq).
move => i; rewrite size_mkseq /= /max /= => ib.
rewrite !nth_mkseq 1..2:// /of_int /to_uint /= get_bits2w 1:// 
        nth_mkseq 1:// /= get_to_uint /= /to_uint /=.
have -> /=: (0 <= i && i < 32) by smt().
pose a := bs2int (w2bits mv). 
rewrite {1}(divz_eq a (2^(8-i)*2^i)) !mulrA divzMDl;
   1: by smt(StdOrder.IntOrder.expr_gt0).
rewrite dvdz_modzDl; 1: by
 have ->  : 2^(8-i) = 2^((8-i-1)+1); [ by smt() |
    rewrite exprS 1:/#; smt(dvdz_mull dvdz_mulr)].  
by have -> : (2 ^ (8 - i) * 2 ^ i) = 256; 
  [ rewrite -StdBigop.Bigint.Num.Domain.exprD_nneg 
     1,2:/# /= -!addrA /= | done ].
qed.


(* ----------- BEGIN ARRAY BINDINGS ---------- *)

from CryptoSpecs require import Array256.
bind array Array256."_.[_]" Array256."_.[_<-_]" Array256.to_list Array256.of_list Array256.t 256.
realize tolistP by done.
realize get_setP by smt(Array256.get_setE). 
realize eqP by smt(Array256.tP).
realize get_out by smt(Array256.get_out).


op init_256_32 (f: int -> W32.t) : W32.t Array256.t = Array256.init f.

bind op [W32.t & Array256.t] init_256_32 "ainit".
realize bvainitP.
proof.
rewrite /init_256_32 => f.
rewrite BVA_Top_Array256_Array256_t.tolistP.
apply eq_in_mkseq => i i_bnd;
smt(Array256.initE).
qed.

from JazzEC require import BArray1024.

(* ----------- BEGIN BArray1024 BINDINGS ---------- *)

op BArray1024_w2bits : BArray1024.t -> bool list.
op BArray1024_bits2w : bool list -> BArray1024.t.
op BArray1024_to_uint : BArray1024.t -> int.
op BArray1024_to_sint : BArray1024.t -> int.
op BArray1024_of_int : int -> BArray1024.t.

bind bitstring BArray1024_w2bits BArray1024_bits2w BArray1024_to_uint BArray1024_to_sint BArray1024_of_int BArray1024.t 8192.
realize size_tolist by admit.
realize tolistP by admit.
realize oflistP by admit. 
realize ofintP by admit.
realize tosintP by admit.
realize touintP by admit.

bind op [BArray1024.t & W32.t] BArray1024.get32d "extract".
realize bvextractP by admit.


(* 
bind array BArray1024.get8 BArray1024.set8 BArray1024.to_list BArray1024.of_list BArray1024.t 1024.
realize tolistP by done.
realize get_setP by smt(Array256.get_setE). 
realize eqP by smt(Array256.tP).
realize get_out by smt(Array256.get_out).

bind op [W8.t & BArray1024] init_256_32 "ainit".
realize bvainitP.
proof.
rewrite /init_256_32 => f.
rewrite BVA_Top_Array256_Array256_t.tolistP.
apply eq_in_mkseq => i i_bnd;
smt(Array256.initE).
qed.

*)
