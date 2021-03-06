/// \file ROOT/RHistDrawingOpts.h
/// \ingroup HistDraw ROOT7
/// \author Axel Naumann <axel@cern.ch>
/// \date 2015-09-04
/// \warning This is part of the ROOT 7 prototype! It will change without notice. It might trigger earthquakes. Feedback
/// is welcome!

/*************************************************************************
 * Copyright (C) 1995-2018, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT7_RHistDrawingOpts
#define ROOT7_RHistDrawingOpts

#include <ROOT/RAttrLine.hxx>
#include <ROOT/RDrawingAttr.hxx>
#include <ROOT/RDrawingOptsBase.hxx>

namespace ROOT {
namespace Experimental {

template <int DIMENSION>
class RHistDrawingOpts {
   static_assert(DIMENSION != 0, "Cannot draw 0-dimensional histograms!");
   static_assert(DIMENSION > 3, "Cannot draw histograms with more than 3 dimensions!");
   static_assert(DIMENSION < 3, "This should have been handled by the specializations below?!");
};


/** \class RHistDrawingOpts<1>
 Drawing options for a 1D histogram.
 */
template <>
class RHistDrawingOpts<1>: public RDrawingOptsBase, public RDrawingAttrBase {
public:
   enum class EStyle { kHist, kBar, kText };

   RHistDrawingOpts():
      RDrawingAttrBase(FromOption, "hist1D", *this)
   {}

   /// The drawing style.
   void SetStyle(EStyle style) { Set("style", style); }
   EStyle GetStyle() const { return Get<EStyle>("style"); }

   RAttrLine Line() { return {FromOption, "contentLine", *this}; }
   RAttrLine BarLine() { return {FromOption, "barLine", *this}; }
   RAttrLine UncertaintyLine() { return {FromOption, "uncertaintyLine", *this}; }
};

/** \class RHistDrawingOpts<2>
 Drawing options for a 2D histogram.
 */
template <>
class RHistDrawingOpts<2>: public RDrawingOptsBase, public RDrawingAttrBase {
public:
   enum class EStyle { kBox, kSurf, kText };

   RHistDrawingOpts():
      RDrawingAttrBase(FromOption, "hist2D", *this)
   {}

   /// The drawing style.
   void SetStyle(EStyle style) { Set("style", style); }
   EStyle GetStyle() const { return Get<EStyle>("style"); }

   RAttrLine BoxLine() { return {FromOption, "boxLine", *this}; }
};

/** \class RHistDrawingOpts<3>
 Drawing options for a 3D histogram.
 */
template <>
class RHistDrawingOpts<3>: public RDrawingOptsBase, public RDrawingAttrBase {
public:
   enum class EStyle { kBox, kIso };

public:
   RHistDrawingOpts():
      RDrawingAttrBase(FromOption, "hist3D", *this)
   {}

   /// The drawing style.
   void SetStyle(EStyle style) { Set("style", style); }
   EStyle GetStyle() const { return Get<EStyle>("style"); }

   RAttrLine BoxLine() { return {FromOption, "boxLine", *this}; }
   RAttrLine IsoLine() { return {FromOption, "isoLine", *this}; }
};

} // namespace Experimental
} // namespace ROOT

#endif
