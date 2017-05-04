// @(#)root/mathcore:$Id$
// Author: L. Moneta Tue Aug 4 2015

/**********************************************************************
 *                                                                    *
 * Copyright (c) 2015  LCG ROOT Math Team, CERN/PH-SFT                *
 *                                                                    *
 *                                                                    *
 **********************************************************************/

// random engines based on ROOT 

#ifndef ROOT_Math_MixMaxEngine
#define ROOT_Math_MixMaxEngine

#include <cstdint>
#include <vector>
#include <string>

#include "Math/TRandomEngine.h"


// struct rng_state_st;    /// forward declare generator state

// typedef struct rng_state_st rng_state_t;

// namespace mixmax { 
//    template<int Ndim>
//    class mixmax_engine; 
// }

namespace ROOT {

   namespace Math {
      
      template<int N>
      class MixMaxEngineImpl;

      /**
         MixMaxEngine is a wrapper class for the MIXMAX Random number generator.
         MIXMASX  is a matrix-recursive random number generator introduced by
         G. Savvidy.

         The real implementation of the generator, written in C, is in the mixmax.h and mixmax.cxx files.
         This generator code is available also at hepforge: http://mixmax.hepforge.org
         The MIXMAX code has been created and developed by Konstantin Savvidy and it is 
         released under GNU Lesser General Public License v3.

         This wrapper class provides 3 different variants of MIXMAX according to the template para extra parameter N. 
         The extra parameter, `SkipNumber`, is used to perform additional iterations of the generator before returning the random numbers. For example, when `SkipNumber = 2`, the generator will have two extra iterations that will be discarder. 

         *  MIXMAX with N = 240. This is a new version of  the generator (version 2.0)  described in the 2016 paper (3rd reference), with 
            special number $s=487013230256099140$, $m=2^{51}+1$ and having a period of $10^{4389}$. 
          
         *  MIXMAX with N = 17, from the 2.0 version with $s=0$ and $m=2^{36}+1$. The period of the generator is $10^{294}$. 

         *  MIMAMX with N = 256 from the 1.0 version. The period is (for `SkipNumber=0`) $10^{4682}$. For this generatior we reccomend using a default value of `SkipNumber=2`. 
 

         The References for MIXMAX are 

         *  G.K.Savvidy and N.G.Ter-Arutyunian, *On the Monte Carlo simulation of physical systems,
         J.Comput.Phys. 97, 566 (1991)*;
         Preprint EPI-865-16-86, Yerevan, Jan. 1986

         *  K.Savvidy, *The MIXMAX random number generator*, 
         Comp. Phys. Commun. 196 (2015), pp 161–165
         http://dx.doi.org/10.1016/j.cpc.2015.06.003

         *  K.Savvidy and G.Savvidy, *Spectrum and Entropy of C-systems MIXMAX Random Number Generator*,
         Chaos, Solitons & Fractals, Volume 91, (2016) pp. 33–38
         http://dx.doi.org/10.1016/j.chaos.2016.05.003
    

         @ingroup Random
      */

      template<int N, int SkipNumber>
      class MixMaxEngine : public TRandomEngine {

      public:

         typedef  TRandomEngine BaseType;

         // this should be changed for WINDOWS
#ifndef __LP64__
         typedef uint64_t StateInt_t;
#else
         typedef unsigned long long StateInt_t;
#endif
         typedef uint64_t Result_t;


         MixMaxEngine(uint64_t seed=1);

         virtual ~MixMaxEngine();


         /// Get the size of the generator
         static int Size();

         /// maximum integer that can be generated. For MIXMAX is 2^61-1
         static uint64_t MaxInt();

         /// minimum integer that can be generated. For MIXMAX is 0
         static uint64_t MinInt();

         /// set the generator seed
         void  SetSeed(Result_t seed);

         // generate a random number (virtual interface)
         virtual double Rndm() { return Rndm_impl(); }

         /// generate a double random number (faster interface)
         inline double operator() () { return Rndm_impl(); }

         /// generate an array of random numbers
         void RndmArray (int n, double * array);

         /// generate a 64  bit integer number
         Result_t IntRndm();

         /// get name of the generator
         static std::string Name();

      protected:
         // protected functions used for tesing the generator

         /// get the state of the generator
         void GetState(std::vector<StateInt_t> & state) const;


         ///set the full initial generator state
         void SetState(const std::vector<StateInt_t> & state);

         /// Get the counter (between 0 and Size-1)
         int Counter() const;


      private:

         /// implementation function to generate the random number
         double Rndm_impl();

         //rng_state_t * fRngState;  // mix-max generator state
         //mixmax::mixmax_engine<N> * fRng;  // mixmax internal engine class
         MixMaxEngineImpl<N> * fRng;  // mixmax internal engine class
         
      };

      typedef MixMaxEngine<240,0> MixMaxEngine240;
      typedef MixMaxEngine<256,2> MixMaxEngine256;
      typedef MixMaxEngine<17,0> MixMaxEngine17;
      
      extern template class MixMaxEngine<240,0>;
      extern template class MixMaxEngine<256,0>;
      extern template class MixMaxEngine<256,2>;
      extern template class MixMaxEngine<256,4>;
      extern template class MixMaxEngine<17,0>;
      extern template class MixMaxEngine<17,1>;
      extern template class MixMaxEngine<17,2>;

   } // end namespace Math

} // end namespace ROOT


#include "Math/MixMaxEngine.icc"

#endif /* ROOT_Math_MixMaxEngine */ 
