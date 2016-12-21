// This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/ or send a letter to
// Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.


#ifndef MODELINCLUDEGUARD
#define MODELINCLUDEGUARD


#include <iostream>
#include <vector>
#include <math.h>
#include "mrgsolv.h"

typedef double local_double;
typedef int local_int;
typedef bool local_bool;

// A box of data that gets passed to $MAIN and $TABLE
struct databox {
  const dvec ETA;
  const dvec EPS;
  const unsigned int newind;
  const double time;
  const int evid;
  bool SYSTEMOFF;
  dvec mtime;
  const double id;
  const double amt;
  const short int cmt;
  bool CFONSTOP;
  void* envir;
};



// pred_P definitions for $PKMODEL
// Note that V/VC/V2 are synonymous when using the pred_P construct
// Also, V3/V3 are synonyms as well
#define pred_CL _pred_[0]
#define pred_V  _pred_[1]
#define pred_VC _pred_[1]
#define pred_V2 _pred_[1]
#define pred_KA _pred_[2]
#define pred_Q  _pred_[3]
#define pred_V3 _pred_[4]
#define pred_VP _pred_[4]

// advan/trans combinations
// These definitions are added by mrgsolve at the end of $MAIN
// when $PKMODEL is called; trans 2/4 are default; when 11 is picked ... tack on a `i` at the end
#define __ADVAN1_TRANS2__  pred_CL = CL;  pred_V  = V;
#define __ADVAN2_TRANS2__  pred_CL = CL;  pred_V  = V;   pred_KA = KA;
#define __ADVAN3_TRANS4__  pred_CL = CL;  pred_V2 = V1;  pred_Q =  Q;  pred_V3 = V2;
#define __ADVAN4_TRANS4__  pred_CL = CL;  pred_V2 = V2;  pred_Q =  Q;  pred_V3 = V3; pred_KA = KA;
#define __ADVAN1_TRANS11__ pred_CL = CLi; pred_V  = Vi;
#define __ADVAN2_TRANS11__ pred_CL = CLi; pred_V  = Vi;  pred_KA = KAi;
#define __ADVAN3_TRANS11__ pred_CL = CLi; pred_V2 = V1i; pred_Q =  Qi;  pred_V3 = V2i;
#define __ADVAN4_TRANS11__ pred_CL = CLi; pred_V2 = V2i; pred_Q =  Qi;  pred_V3 = V3i; pred_KA = KAi;

// Don't need this?
#define __BEGIN_pred__ extern "C" {void __ODEFUN___(MRGSOLVE_PRED_SIGNATURE) {

// $MAIN, $ODE, and $TABLE get translated into these functions
// We need ODEFUN___ and INITFUN___ and TABLECODE___ defined in the
// .cpp.cpp model file
#define __BEGIN_config__ extern "C" {void __CONFIGFUN___(MRGSOLVE_CONFIG_SIGNATURE) {
#define __END_config__ __DONE__
#define __BEGIN_ode__ extern "C" {void __ODEFUN___(MRGSOLVE_ODE_SIGNATURE) {
#define __END_ode__ __DONE__
#define __BEGIN_main__ extern "C" {void __INITFUN___(MRGSOLVE_INIT_SIGNATURE) {
#define __END_main__ __DONE__
#define __BEGIN_table__ extern "C" {void __TABLECODE___(MRGSOLVE_TABLE_SIGNATURE) {
#define __END_table__ __DONE__
#define __DONE__ }}


// New individual flag
#define NEWIND self.newind
// The data set time
#define TIME self.time
// The ode solver time
#define SOLVERTIME _ODETIME_[0]
// Event ID
#define EVID self.evid
// Data set individual
#define ID self.id


// These are the fundamental macros for
// bioavailability, infusion rate, infusion duration
// and dose lag time.  Keep these here, but
// the model spec should prefer F_CMT, R_CMT, D_CMT, ALAG_CMT
#define _F(a)    _F_[a-1]
#define _R(a)    _R_[a-1]
#define _D(a)    _D_[a-1]
#define _ALAG(a) _ALAG_[a-1]

// These are the fundamental macros for
// random effects.  These might get used,
// but users are allowed to insert labels to
// avoid directly accessing the macros.
#define ETA(a) self.ETA.at(a-1)
#define EPS(a) self.EPS.at(a-1)
#define _xETA(a) self.ETA[a-1]
#define _xEPS(a) self.EPS[a-1]

// Number of equations
#define _NEQ (_A_0_.size())

// Macros related to stopping the advance of the system
// once a condition is met
#define SYSTEMSTOPADVANCING() (self.SYSTEMOFF=true);
#define STOPADVANCING() SYSTEMSTOPADVANCING()  // Not sure why this is here
#define CFONSTOP() (self.CFONSTOP = true); // Carry forward on stop
#define SYSTEMNOTADVANCING (self.SYSTEMOFF)
#define SOLVINGPROBLEM (self.solving)
#define _SETINIT if(self.newind <=1) // Convenience

// Macro to insert dxdt_CMT = 0; for all compartments
#define DXDTZERO() for(int _i_ = 0; _i_ < _nEQ; ++_i_) _DADT_[_i_] = 0;

// Some functions for reporting values during a
// simulation run
template <class type> void report(type a) {
  std::cout << "from report " << a << std::endl;
}
template <class type1, class type2> void report(type1 a, type2 b) {
  std::cout << a << " " << b << std::endl;
}

#endif